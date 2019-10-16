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
 * @file ICell.hpp
 * Defines the generic cell interface.
 */

#pragma once

#include <tuple>
#include <optional>

namespace Systolic {
	namespace Cell {

		/**
		 * Pure virtual class for Cell class implementation.
		 * Interface defining the mandatory function to
		 * implement in order to be used by cell containers.
		 */
		class ICell {
		public:
			/**
			 * Perform the computation.
			 * Does an implementation-dependant computation based on its
			 * internal stored value.
			 * Replaces its internal stored value by the computed result.
			 * @return A tuple with
			 * at 0 the new computed value
			 * and at 1 the initial value from the input queue.
			 * May be empty on empty feeding.
			 */
			virtual std::tuple<std::optional<int>, std::optional<int>> compute() = 0;
			/**
			 * Give a new value to the cell for later computation.
			 * Stores a new value in the cell, to be used during computation.
			 * Does not replace the existing partial result.
			 * @param input An optional integer.
			 * @see compute
			 */
			virtual void feed(const std::tuple<std::optional<int>, std::optional<int>> input) = 0;
			/**
			 * Get the current computed value of the cell.
			 * Gets the last computed value of this cell.
			 * @return A tuple with
			 * at 0 the last computed value
			 * and at 1 the initial value from the input queue.
			 * @see compute
			 */
			virtual std::tuple<std::optional<int>, std::optional<int>> getPartial() const = 0;
			/**
			 * Get the inputs for the next computation.
			 * Get the last values fed to the cells.
			 * @return The last values fed to the cells,
			 * with at (0) the current sum
			 * and at (1) the original input.
			 ù @see feed
			 */
			virtual std::tuple<std::optional<int>, std::optional<int>> getInputs() const = 0;
			/**
			 * Get a generic description of the cell.
			 * @return An implementation-dependant string.
			 */
			virtual std::string getCellDescription() const = 0;
			/**
			 * Default deconstructor.
			 */
			virtual ~ICell() {};
		};
	}
}
