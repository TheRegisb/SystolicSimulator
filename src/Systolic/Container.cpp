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

Systolic::Container::Container(const std::initializer_list<const int> entries)
{
	for (int entry : entries) {
		inputs.push(entry);
	}
}

void Systolic::Container::addCell(std::unique_ptr<Systolic::Cell::ICell> cell)
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

void Systolic::Container::step()
{
	if (cells.size() == 0) {
		std::cerr << "Warn: Cannot compute container step: No cells available." << std::endl;
		return;
	}

	// Compute the current value of each cells.
	for (auto &&ptr : cells) {
		std::tuple<int, std::optional<int>> res = ptr->compute();
	}
	
	// Feeds the first cell with a value from the inputs queue.
	if (!inputs.empty()) {
		cells.at(0)->feed(inputs.front());
		inputs.pop();
	} else {
		cells.at(0)->feed({}); // Feeds empty value.
	}

	// Feed all other cells with the partials of the previous cell.
	for(std::size_t i = 1; i < cells.size(); i++) {
		cells.at(i)->feed(std::get<1>(cells.at(i - 1)->getPartial()));
	}

	// Add the last cell partial (final result) to the output queue if available.
	std::optional<int> lastCellOutput = std::get<1>(cells.back()->getPartial());

	if (lastCellOutput.has_value()) {
		outputs.push(lastCellOutput.value());
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
	while (outputs.size() != ioSize) { // TODO consider do while
		step();
	};
	step();
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
