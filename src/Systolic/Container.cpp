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

#include "Systolic/Container/Container.hpp"

Systolic::Container::Container(int entries, ...): cell(nullptr), cell2(nullptr)
{
	va_list args;

	va_start(args, entries);
	while (entries--) {
		inputs.push(va_arg(args, int));
	}
}

Systolic::Container::~Container()
{
	if (cell != nullptr) {
		delete cell;
	}
	if (cell2 != nullptr) {
		delete cell2;
	}
}

void Systolic::Container::addCell(Systolic::Cell::ICell *cell)
{
	// TODO push to vector
	static int count = 0;

	if (count++ == 3) {
		throw std::runtime_error("Cannot have more than two cells");
	}
	if (count == 1) {
		this->cell = cell;
	} else {
		this->cell2 = cell;
	}
}

void Systolic::Container::step()
{
	if (cell == nullptr || cell2 == nullptr) {
		throw std::runtime_error("One or more cell are not set up properly");
	}
	auto result = cell->compute();
	auto result2 = cell2->compute();
	if (inputs.empty()) {
		cell->feed({});
	} else {
		std::cout << "Input: " << inputs.front() << std::endl;
		cell->feed(inputs.front());
		inputs.pop();
	}
	cell2->feed(std::get<1>(cell->getPartial()));
	std::cout << "Cell 1 " << std::get<0>(result) << " -- " << std::get<1>(result).value_or(0) << std::endl;
	std::cout << "Cell 2 " << std::get<0>(result2) << " -- " << std::get<1>(result2).value_or(0) << std::endl << std::endl;
	if (std::get<1>(cell2->getPartial()).has_value()) {
		outputs.push(std::get<1>(cell2->getPartial()).value());
	}
}

void Systolic::Container::compute()
{
	std::size_t ioSize = inputs.size();

	while (outputs.size() != ioSize) { // TODO consider do while
		step();
	};
	step();
}

void Systolic::Container::dumpOutputs()
{
	std::queue<int> copy = outputs;

	while (!copy.empty()) {
		std::cout << copy.front() << std::endl;
		copy.pop();
	}
}
