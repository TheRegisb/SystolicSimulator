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
 * @file Systolic.hpp
 * Convenience header, and also the Doxygen main page.
 */

#pragma once

#include "Systolic/Cell/Types.hpp"
#include "Systolic/Container/Container.hpp"
#include "Systolic/Container/CellArrayBuilder.hpp"

/*! \mainpage Systolic Simulator
 * \section Presentation
 * Simulation of the flow of systolic algorithms; where computational
 * unit called "cell" are working on parallel, computing the result
 * given by the last cell before feeding the result into the next one.
 *
 * \section Usage
 * The geneal usage of the Systolic Simulator is to decalare a new container of type `Systolic::Container` and to generate a predefined amount of cells, whose type and value are configurable by the user.
 *
 * To simplify the creation of cells, the use of the `Systolic::CellArrayBuilder` can be used in conjonction with the `Systolic::Container::setCells` function to generate the instances of the cells from theit types and value.
 * Special utilities are available for polynomial equations.
 *
 * The Container can then be used to solves the equation either step by step, using the `Systolic::Container::step` function or until completion using the `Systolic::Container::compute` function.
 *
 * Results and logs of the computations, partial or completed, can be queried using respectively `Systolic::Container::dumpOutputs`, `Systolic::Container::getCurrentStateLog` or `Systolic::Container::getLog`.
 *
 * <hr>
 * \section Credits
 * BERTHELOT Régis, 2019.
 */
