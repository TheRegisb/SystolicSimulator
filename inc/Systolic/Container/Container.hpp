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

#pragma once

#include "Systolic/Cell/ICell.hpp"

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdarg>

namespace Systolic {

	class Container {
	public:
		Container(int entries, ...);
		// TODO extra construct taking vector<int> and queue<int>
		~Container();

		void addCell(std::unique_ptr<Systolic::Cell::ICell> cell); // TODO Consider builder<
		void step();
		void compute();
		void dumpOutputs(); // TODO const function
		std::queue<int> getOutputs(); // TODO const function
	private:
		std::vector<std::unique_ptr<Systolic::Cell::ICell>> cells;
		std::queue<int> inputs;
		std::queue<int> outputs;
	};
}
