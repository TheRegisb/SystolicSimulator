// Copyright 2019 Régis Berthelot

// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

/**
 * @file Container.cpp
 * Implementation of Container.
 */

#include "Systolic/Container/Container.hpp"

Systolic::Container::Container(const int entries, ...)
{
	va_list args;

	va_start(args, entries);
	for (int i = 0; i != entries; i++) {
		inputs.push(va_arg(args, int));
	}
}

Systolic::Container::Container(const std::queue<int> entries)
{
	inputs = entries;
}

Systolic::Container::Container(const std::initializer_list<const int> entries)
{
	for (int entry : entries) {
		inputs.push(entry);
	}
}

void Systolic::Container::addCell(std::unique_ptr<Systolic::Cell::ICell> cell) // Deprecated
{
	if (cell == nullptr) {
		std::cerr << "Warn: Trying to add NULL cell; addCell call ignored." << std::endl;
		return;
	}
	if(std::find(cells.begin(), cells.end(), cell) != cells.end()) { // Trying to add the same cell more than once.
		std::cerr << "Warn: Cell duplication detected; addCell call ignored." << std::endl;
		return;
	}
	cells.push_back(std::move(cell));
}

void Systolic::Container::setCells(std::vector<std::unique_ptr<Systolic::Cell::ICell>> cells)
{
	this->cells = std::move(cells);
}

void Systolic::Container::setCells(std::shared_ptr<Systolic::CellArrayBuilder> builder)
{
	if (builder == nullptr) {
		throw std::invalid_argument("Builder is NULL.");
	}
	this->cells = builder->build();
}

void Systolic::Container::step()
{
	if (cells.size() == 0) {
		std::cerr << "Warn: Cannot compute container step: No cells available." << std::endl;
		return;
	}

	// Feeds the first cell with a value from the inputs queue.
	if (!inputs.empty()) {
		cells.at(0)->feed(std::make_tuple(std::nullopt, inputs.front()));
		inputs.pop();
	} else {
		cells.at(0)->feed(std::make_tuple(std::nullopt, std::nullopt)); // Feeds empty value.
	}

	// Feed all other cells with the partials (results) of the previous cell.
	for(std::size_t i = 1; i < cells.size(); i++) {
		cells.at(i)->feed(cells.at(i - 1)->getPartial());
	}

	// Compute the current value of each cells.
	std::queue<std::future<std::tuple<std::optional<int>, std::optional<int>>>> futures;

	for (std::size_t i = 0; i != cells.size(); i++) {
		/* 
		 * Each computation is started in its own thread.
		 * std::async returns a std::future to access the thread's return
		 * value (or exception).
		 * This way, larger computation can be started without preventing the
		 * start of other computations.
		 */
		futures.push(std::async(std::launch::async, [this, j = i]{ return cells.at(j)->compute(); }));
	}

	// Add the last cell partial (final result) to the output queue if available.
	std::optional<int> lastCellOutput = std::get<0>(futures.back().get());

	if (lastCellOutput.has_value()) {
		outputs.push(lastCellOutput.value());
	}

	// Wait for each computation to be completed.
	while (futures.size() != 1) { // Last handle have been used by lastCellOutput.
		futures.front().wait();
		futures.pop();
	}
}

void Systolic::Container::compute()
{
	std::size_t ioSize = inputs.size();

	if (cells.size() == 0) {
		std::cerr << "Err: Cannot compute container: No cells available." << std::endl;
		return;
	}
	if (ioSize == 0) {
		std::cerr << "Err: No inputs available." << std::endl;
		return;
	}
	do {
		logs.push_back(makeLogEntry());
		step();
	} while (outputs.size() != ioSize);
	logs.push_back(makeLogEntry());
}

void Systolic::Container::dumpOutputs() const
{
	std::queue<int> copy = outputs;

	while (!copy.empty()) {
		std::cout << copy.front() << std::endl;
		copy.pop();
	}
}

std::queue<int> Systolic::Container::getOutputs() const
{
	return outputs;
}

std::string Systolic::Container::getCurrentStateLog() const
{
	return logs.back();
}

std::string Systolic::Container::getLog() const
{
	std::stringstream ss;

	for (std::string entry : logs) {
		ss << entry << std::endl;
	}
	return ss.str();
}

std::string Systolic::Container::makeLogEntry() const
{
	std::stringstream ss;

	/* Step header. */
	ss << "###################"
	   << std::endl
	   << "# Step No. "
	   << std::setw(6) << std::right << logs.size() << " #"
	   << std::endl
	   << "###################"
	   << std::endl;

	/* Displaying remaning values waiting in the input queue. */
	ss << "inputs: ";
	for (std::queue<int> iCopy = inputs; iCopy.size() > 0; iCopy.pop()) {
		ss << iCopy.front() << (iCopy.size() != 1 ? ", " : "");
	}
	ss << std::endl << std::endl;
	
	/* Displaying the inputs of the cells on the left side and its partials on the right. */
	for (std::size_t i = 0; i != cells.size(); i++) {
		/* First line (sums). */
		ss << std::setw(8) << optionalToString(std::get<0>(cells.at(i)->getInputs()))
		   << " -- |" << std::setw(19) << std::setfill('-') << "| -- " << std::setfill(' ')
		   << optionalToString(std::get<0>(cells.at(i)->getPartial()))
		   << std::endl
		/* Middle line (cell description) */	
		   << std::setw(14) << "| "
		   << std::setw(12) << std::left << cells.at(i)->getCellDescription() << std::right
		   << " | "
		   << std::endl
		/* Bottom line (inputs). */
		   << std::setw(8) << optionalToString(std::get<1>(cells.at(i)->getInputs()))
		   << " -- |" << std::setw(19) << std::setfill('-') << "| -- " << std::setfill(' ')
		   << optionalToString(std::get<1>(cells.at(i)->getPartial()))
		   << std::endl << std::endl;
	}
	ss << "outputs: ";
	
	/* Displaying the values stored in the outputs queue. */
	for (std::queue<int> oCopy = outputs; oCopy.size() > 0; oCopy.pop()) {
		ss << oCopy.front() << (oCopy.size() != 1 ? ", " : "");
	}
	ss << std::endl;
	
	return ss.str();
}

std::string Systolic::Container::optionalToString(std::optional<int> value) const
{
	if (value.has_value()) {
		return std::to_string(value.value());
	} else {
		return "{}";
	}
}
