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
 * @file CellArrayBuilder.hpp
 * Builder of vector<unique_ptr<ICell>>.
 */

#pragma once

#include "Systolic/Cell/Types.hpp"

#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>

namespace Systolic {

	/**
	 * Systolic array builder.
	 * Used to create array of cells in order.
	 */
	class CellArrayBuilder : public std::enable_shared_from_this<CellArrayBuilder> {
	public:
		/**
		 * Get a new instance of builder.
		 */
		static std::shared_ptr<CellArrayBuilder> getNew();
		/**
		 * Add a predefined cell to the array.
		 * @param cellType Type enum of the cell to add.
		 * @param term The optional term to bind to that cell (please refer to the implementation
		 * of the cells for more details).
		 * @return The instance of the builder.
		 * @throws std::invalid_argument On custom type cell insertion (use overloaded method instead).
		 */
		std::shared_ptr<CellArrayBuilder> add(const Systolic::Cell::Types cellType, const int term = 0);
		/**
		 * Add a custom cell to the array.
		 * @param cellType Type enum of the cell to add.
		 * @param customFunc The custom function, taking a const int and returning a const int, to
		 * be executed by the cell.
		 * @return The instance of the builder.
		 * @throws std::invalid_argument On predefined type cell insertion (use base method instead).
		 */
		std::shared_ptr<CellArrayBuilder> add(const Systolic::Cell::Types cellType,
				      const std::function<int(const int)> customFunc);
		/**
		 * Add an deduced number of PolynomialCells.
		 * Add as many PolynomialCell as needed for the given list, with their coefficients in
		 * order of the list.
		 * @param coefs The list of coefficients for each future polynomial cell.
		 * @return The instance of the builder.
		 */
		std::shared_ptr<CellArrayBuilder> fromPolynomialCoefs(const std::initializer_list<int> coefs);
		/**
		 * Unimplemented.
		 * @throw runtime_error Systematically.
		 * @return The instance of the builder.
		 */
		std::shared_ptr<CellArrayBuilder> fromPolynomialEquation(const char *equation);
		/**
		 * Generate the systolic array from previous addition.
		 * @return A vector of unique_ptr of the previously added cells.
		 */
		std::vector<std::unique_ptr<Systolic::Cell::ICell>> build();
	private:
		static void *operator new(size_t) = delete;
		static void *operator new[](size_t) = delete;
		static void operator delete(void *) = delete;
		static void operator delete[](void *) = delete;
		std::unique_ptr<Systolic::Cell::ICell> getInstanceFromEnum(const Systolic::Cell::Types type,
									   const int term);
		std::vector<std::unique_ptr<Systolic::Cell::ICell>> cellArray;
	};
}
