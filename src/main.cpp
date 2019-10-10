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
#include "Systolic/Cell/SquareCell.hpp"
#include "Systolic/Cell/MultiplicativeCell.hpp"
#include "Systolic/Cell/AdditiveCell.hpp"
#include "Systolic/Cell/DivisionCell.hpp"

#include <iostream>
#include <memory>
#include <tuple>

int main()
{
	Systolic::Container sc({1, 2, 3, 4});

	/*
	 * TODO cells builder like:
	 * sc.setCells(new CellArrayBuilder().add(Systolic::Type::SquareCell)
	 *                                   .add(Systolic::Type::SquareCell)
	 *                                   .build());
	 */
	/* Example for X² - 4x + 7 (== -4X + X² + 7) */
	sc.addCell(std::make_unique<Systolic::Cell::MultiplicativeCell>(-4));
	sc.addCell(std::make_unique<Systolic::Cell::SquareCell>());
	sc.addCell(std::make_unique<Systolic::Cell::AdditiveCell>(7));
	sc.compute();
	sc.dumpOutputs();
	return EXIT_SUCCESS;
}
