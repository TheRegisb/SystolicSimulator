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
 * @file MultiplicativeCell.hpp
 * Cell dedicated to multiplication.
 */

#pragma once

#include "Systolic/Cell/ICell.hpp"

namespace Systolic {
	namespace Cell {

		/**
		 * Implementation of an ICell for multiplicative operation.
		 * Cell that performs X*Y computation, where Y is a constant
		 * integer defined at cell creation.
		 */
		class MultiplicativeCell : public ICell {
		public:
			/**
			 * Default constructor.
			 * Defines what the constant factor for the computation
			 * of this cell.
			 */
			MultiplicativeCell(const int factor);

			/**
			 * Perform the computation.
			 * Does an X*Y computation where X is its internal
			 * stored value and Y is the constant defined at
			 * the cell creation.
			 * Replaces its internal stored value by the computed result.
			 * @return A tuple with
			 * at 0 the new computed value
			 * and at 1 the initial value from the input queue.
			 * May be empty on empty feeding.
			 */
			std::tuple<std::optional<int>, std::optional<int>> compute() override;
			void feed(const std::tuple<std::optional<int>, std::optional<int>> input) override;
			std::tuple<std::optional<int>, std::optional<int>> getPartial() const override;

		private:
			const int factor; /** Factor of the multiplication. */
			std::optional<int> input; /** Value to be used for the next comutation. */
			std::optional<int> sum; /** Sum of all values that were computed by this cell. */
			std::tuple<std::optional<int>, std::optional<int>> partial;
		};
	}
}
