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
 * @file Types.hpp
 * Enum refering to the type of cells.
 */

#pragma once

#include "Systolic/Cell/ICell.hpp"
#include "Systolic/Cell/AdditiveCell.hpp"
#include "Systolic/Cell/MultiplicativeCell.hpp"
#include "Systolic/Cell/DivisionCell.hpp"
#include "Systolic/Cell/SquareCell.hpp"
#include "Systolic/Cell/PowerCell.hpp"
#include "Systolic/Cell/CustomCell.hpp"

namespace Systolic {
	namespace Cell {

		/**
		 * 1:1 descriptor of all other exiting cells.
		 */
		enum class Types {
			Addition, /** Reference to AdditiveCell. */
			Multiplication, /** Reference to MultiplicativeCell. */
			Division, /** Reference to DivisionCell. */
			Square, /** Reference to SquareCell. */
			Power, /** Reference to PowerCell. */
			Custom /** Reference to CustomCell. */
		};
	}
}
