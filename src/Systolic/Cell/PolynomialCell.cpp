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
 * @file PolynomialCell.cpp
 * Implementation of PolynomialCell.
 */

#include "Systolic/Cell/PolynomialCell.hpp"

Systolic::Cell::PolynomialCell::PolynomialCell(const int coef)
	: coef(coef), input{}, sum{}, partial(std::nullopt, std::nullopt)
{
}

std::tuple<std::optional<int>, std::optional<int>> Systolic::Cell::PolynomialCell::compute()
{
	if (input.has_value()) {
		partial = std::make_tuple(sum.value_or(0) * input.value() + coef, input.value());
	} else {
		partial = std::make_tuple(std::nullopt, std::nullopt);
	}
	return partial;
}

void Systolic::Cell::PolynomialCell::feed(const std::tuple<std::optional<int>, std::optional<int>> input)
{
	this->input = std::get<1>(input);
	this->sum = std::get<0>(input);
}

std::tuple<std::optional<int>, std::optional<int>> Systolic::Cell::PolynomialCell::getPartial() const
{
	return partial;
}

std::tuple<std::optional<int>, std::optional<int>> Systolic::Cell::PolynomialCell::getInputs() const
{
	return std::make_tuple(sum, input);
}

std::string Systolic::Cell::PolynomialCell::getCellDescription() const
{
	return ("* X + " + std::to_string(coef));
}
