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

int main(void)
{
	/* Example for 2x³ - 6x² + 2x - 1 */
	Systolic::Container sc3({3, 4, 5, 6, 7});

	sc3.setCells(Systolic::CellArrayBuilder::getNew()
		    ->add(Systolic::Cell::Types::Polynomial, 2)
		    ->add(Systolic::Cell::Types::Polynomial, -6)
		    ->add(Systolic::Cell::Types::Polynomial, 2)
		    ->add(Systolic::Cell::Types::Polynomial, -1));
	sc3.compute();
	std::cout << sc3.getLog() << std::endl;
	return EXIT_SUCCESS;
}
