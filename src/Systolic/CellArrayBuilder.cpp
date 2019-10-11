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
 * @file CellArrayBuilder.cpp
 * Implementation of CellArrayBuilder.
 */

#include "Systolic/Container/CellArrayBuilder.hpp"

std::shared_ptr<Systolic::CellArrayBuilder> Systolic::CellArrayBuilder::getNew()
{
	return std::make_shared<Systolic::CellArrayBuilder>();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::add(const Systolic::Cell::Types cellType,
				const int term)
{
	if (cellType == Systolic::Cell::Types::Custom) {
		throw std::invalid_argument("Cannot declare a custom cell with a single integer term.");
	}
	cellArray.push_back(std::move(getInstanceFromEnum(cellType, term)));
	return shared_from_this();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::add(const Systolic::Cell::Types cellType,
				const std::function<int(const int)> customFunc)
{
	if (cellType != Systolic::Cell::Types::Custom) {
		throw std::invalid_argument("Cannot use a custom function on a predefined cell.");
	}
	cellArray.push_back(std::make_unique<Systolic::Cell::CustomCell>(customFunc));
	return shared_from_this();
}

std::vector<std::unique_ptr<Systolic::Cell::ICell>> Systolic::CellArrayBuilder::build()
{
	return std::move(cellArray);
}

std::unique_ptr<Systolic::Cell::ICell>
Systolic::CellArrayBuilder::getInstanceFromEnum(const Systolic::Cell::Types type, const int term)
{
	using namespace Systolic::Cell;
	
	switch(type) {
	case Types::Addition:
		return std::make_unique<AdditiveCell>(term);
	case Types::Multiplication:
		return std::make_unique<MultiplicativeCell>(term);
	case Types::Division:
		return std::make_unique<DivisionCell>(term);
	case Types::Square:
		return std::make_unique<SquareCell>();
	case Types::Power:
		return std::make_unique<PowerCell>(term);
	default:
		return nullptr;
	}
}
