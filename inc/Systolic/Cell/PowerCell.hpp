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
 * @file PowerCell.hpp
 * Cell dedicated to square (X^2) operation.
 */

#pragma once

#include "Systolic/Cell/ICell.hpp"
#include <cmath>

namespace Systolic {
	namespace Cell {

		/**
		 * Implementation of an ICell for square operation.
		 * Cell that performs X^Y computation.
		 */
		class PowerCell : public ICell {
		public:
			/**
			 * Default constructor.
			 */
			PowerCell(const int coef);

			/**
			 * Perform the computation.
			 * Does an power-of-X computation based on its
			 * internal stored value.
			 * Replaces its internal stored value by the computed result.
			 * @return A tuple with
			 * at 0 the new computed value
			 * and at 1 the initial value from the input queue.
			 * May be empty on empty feeding.
			 */
			std::tuple<std::optional<int>, std::optional<int>> compute() override;
			void feed(const std::tuple<std::optional<int>, std::optional<int>> input) override;
			std::tuple<std::optional<int>, std::optional<int>> getPartial() const override;
			std::tuple<std::optional<int>, std::optional<int>> getInputs() const override;
			std::string getCellDescription() const override;

		private:
			const int coef; /** Coefficient of the power-by operation. */
			std::optional<int> input; /** Value to be used for the next computation. */
			std::optional<int> sum; /** Sum of all values that were computed by this cell. */
			std::tuple<std::optional<int>, std::optional<int>> partial; /** Last computed value, as (sum, input). */
		};
	}
}
