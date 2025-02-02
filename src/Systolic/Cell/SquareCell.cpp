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
 * @file SquareCell.cpp
 * Implementation of SquareCell.
 */

#include "Systolic/Cell/SquareCell.hpp"

Systolic::Cell::SquareCell::SquareCell()
	: input{}, sum{}, partial(std::nullopt, std::nullopt)
{
}

std::tuple<std::optional<int>, std::optional<int>> Systolic::Cell::SquareCell::compute()
{
	if (input.has_value()) {
		partial = std::make_tuple(sum.value_or(0) + (input.value() * input.value()), input.value());
	} else {
		partial = std::make_tuple(std::nullopt, std::nullopt);
	}
	return partial;
}

void Systolic::Cell::SquareCell::feed(const std::tuple<std::optional<int>, std::optional<int>> input)
{
	this->input = std::get<1>(input);
	this->sum = std::get<0>(input);
}

std::tuple<std::optional<int>, std::optional<int>> Systolic::Cell::SquareCell::getPartial() const
{
	return partial;
}

std::tuple<std::optional<int>, std::optional<int>> Systolic::Cell::SquareCell::getInputs() const
{
	return std::make_tuple(sum, input);
}

std::string Systolic::Cell::SquareCell::getCellDescription() const
{
	return "+ X^2";
}
