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

#include "Systolic/Systolic.hpp"

int main()
{
	/* Example for X² - 4x + 7 (== -4X + X² + 7) */
	Systolic::Container sc({1, 2, 3, 4});

	sc.setCells(Systolic::CellArrayBuilder::getNew()
		    ->add(Systolic::Cell::Types::Multiplication, -4)
		    ->add(Systolic::Cell::Types::Square)
		    ->add(Systolic::Cell::Types::Addition, 7));
	sc.compute();
	sc.dumpOutputs();
	
	/* Example for x³/4 + 3x2/4 − 3x/2 − 2 NOTE: integral truncature DOES impact negatively the result */
	Systolic::Container sc2(4, 1, 2, 3, 4); // C-Style va-arg.
	sc2.setCells(Systolic::CellArrayBuilder::getNew()
		     ->add(Systolic::Cell::Types::Custom, [] (const int x) { return (x * x * x) / 4; })
		     ->add(Systolic::Cell::Types::Custom, [] (const int x) { return 3 * (x * x) / 4; })
		     ->add(Systolic::Cell::Types::Custom, [] (const int x) { return -3 * x / 4; })
		     ->add(Systolic::Cell::Types::Addition, -2)
		     ->build()); // Explicit call to build can be ommited.
	sc2.compute();
	sc2.dumpOutputs();

	return EXIT_SUCCESS;
}
