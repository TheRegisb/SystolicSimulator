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
 * @file SquareCell.hpp
 * Cell dedicated to square (X^2) operation.
 */

#pragma once

#include "Systolic/Cell/ICell.hpp"
#include <tuple>
#include <optional>

namespace Systolic {
	namespace Cell {

		/**
		 * Implementation of an ICell for square operation.
		 * Cell that performs X^2 computation.
		 */
		class SquareCell : public ICell {
		public:
			/**
			 * Default constructor.
			 */
			SquareCell();

			/**
			 * Perform the computation.
			 * Does an power-of-two computation based on its
			 * internal stored value.
			 * Replaces its internal stored value by the computed result.
			 * @return A tuple with
			 * at 0 the sum of all values that passed down that cell
			 * and at 1 the computed value (may be empty on empty value
			 * computation).
			 */
			std::tuple<int, std::optional<int>> compute() override;
			void feed(const std::optional<int> input) override;
			std::tuple<int, std::optional<int>> getPartial() const override;

		private:
			std::optional<int> input; /** Value to be used for the next computation. */
			std::optional<int> current; /** Result of the last computation. */
			int sum; /** Sum of all value that were computed by this cell. */
		};
	}
}
