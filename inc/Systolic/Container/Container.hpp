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
 * @file Container.hpp
 * Default cell container and runner.
 */

#pragma once

#include "Systolic/Cell/ICell.hpp"

#include <iostream>
#include <memory>
#include <algorithm>
#include <initializer_list>
#include <vector>
#include <queue>
#include <cstdarg>

namespace Systolic {

	/**
	 * Cell container and runner.
	 * Container made to received a user-defined collection
	 * of cell and to run that collection in a systolic
	 * manner over a given input list.
	 */
	class Container {
	public:
		/**
		 * Default constructor.
		 * @param entries List of the number to process as a
		 * bracket-enclosed list (e.g. {0, 1, 2, 3}).
		 */
		Container(const std::initializer_list<const int> entries);
		/**
		 * C-Style constructor.
		 * Tells how many inputs there is and what is their respective
		 * value. Using a greater index than the actual number of
		 * entries result in undefined behaviour.
		 * @param entries Number of entries to process from the list.
		 * @param ... Variable number of input.
		 */
		Container(const int entries, ...);

		/**
		 * Add a new cell.
		 * Add a new cell at the end of the operation chain.
		 * Call is ignored if the cell is a null value.
		 * Call is also ignored if the cell is already present in the
		 * operation chain.
		 * @param cell An instance of an ICell derivative.
		 */
		void addCell(std::unique_ptr<Systolic::Cell::ICell> cell); // TODO Consider builder
		/**
		 * Single tick on the operation chain.
		 * Provoke each registered cell to compute their current
		 * value and aquire their next input.
		 * Call is ignored if not cell are registered.
		 * @see Systolic::ICell::compute
		 * @see Systolic::ICell::feed
		 */
		void step();
		/**
		 * Operate the chain until completion.
		 * Make the operation chain work until every inputs
		 * have been send to the outputs queue.
		 * Call is ignored if no cell are registered.
		 * Call is also ignore if no inputs are registered.
		 * @see step
		 */
		void compute();
		/**
		 * Display the current content of the output queue.
		 * Displays all values contained within the output queue
		 * on the standard output, in a First In, First Out
		 * manner.
		 */
		void dumpOutputs() const;
		/**
		 * Get a copy of the current output queue.
		 */
		std::queue<int> getOutputs() const;
	private:
		std::vector<std::unique_ptr<Systolic::Cell::ICell>> cells;
		std::queue<int> inputs;
		std::queue<int> outputs;
		// TODO log debug/execution info in a stringstream
	};
}
