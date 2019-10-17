# Copyright 2019 Régis Berthelot

# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at

#   http:#www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.


# Set minimum version of CMake
cmake_minimum_required(VERSION 3.1)

# Set x64 target for Windows builds.
if (WIN32)
  set(CMAKE_GENERATOR_PLATFORM "x64")
endif()

# Project is systolic
project(systolic C CXX)
set (systolic_VERSION_MAJOR 0)
set (systolic_VERSION_MINOR 1)

# Set warning flags
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread -g3")
endif()


# Required includes
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Files to compile
set(SOURCES src/main.cpp
  src/Util/Parser.cpp
  src/Systolic/Cell/SquareCell.cpp
  src/Systolic/Cell/MultiplicativeCell.cpp
  src/Systolic/Cell/AdditiveCell.cpp
  src/Systolic/Cell/DivisionCell.cpp
  src/Systolic/Cell/PowerCell.cpp
  src/Systolic/Cell/PolynomialCell.cpp
  src/Systolic/Cell/CustomCell.cpp
  src/Systolic/CellArrayBuilder.cpp
  src/Systolic/Container.cpp)

add_executable (systolic ${SOURCES})
target_link_libraries(systolic ${CMAKE_THREAD_LIB_INIT})

# Required C++17 support
set_property(TARGET systolic PROPERTY CXX_STANDARD 17)
