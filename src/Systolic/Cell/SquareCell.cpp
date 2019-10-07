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

#include "Systolic/Cell/SquareCell.hpp"

Systolic::Cell::SquareCell::SquareCell(): current{}, sum(0)
{
}

std::tuple<int, std::optional<int>> Systolic::Cell::SquareCell::compute()
{
	if (input.has_value()) {
		current = input.value() * input.value();
		sum += current.value_or(0);
	} else {
		current = {};
	}
	return getPartial();
}

void Systolic::Cell::SquareCell::feed(std::optional<int> input)
{
	this->input = input;
}

std::tuple<int, std::optional<int>> Systolic::Cell::SquareCell::getPartial()
{
	return std::make_tuple(sum, current);
}

bool Systolic::Cell::SquareCell::isEmpty()
{
	return empty;
}
