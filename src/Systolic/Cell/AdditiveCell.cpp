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
 * @file AdditiveCell.cpp
 * Implementation of AdditiveCell.
 */

#include "Systolic/Cell/AdditiveCell.hpp"

Systolic::Cell::AdditiveCell::AdditiveCell(const int term)
	: current{}, sum(0), term(term)
{
}

std::tuple<int, std::optional<int>> Systolic::Cell::AdditiveCell::compute()
{
	if (input.has_value()) {
		current = input.value() + term;
		sum += current.value_or(0);
	} else {
		current = {}; // Set the value to strictly empty.
	}
	return getPartial();
}

void Systolic::Cell::AdditiveCell::feed(const std::optional<int> input)
{
	this->input = input;
}

std::tuple<int, std::optional<int>> Systolic::Cell::AdditiveCell::getPartial() const
{
	return std::make_tuple(sum, current);
}