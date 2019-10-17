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
 * @file Parser.hpp
 * Command line processing utility class.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <regex>
#include <cstring>

namespace Util {

	class Parser {
	public:
		/**
		 * Add the command line argument into the provided map.
		 * Expected arguments are --with-x=[0-9]+ and either 
		 * --coefs=[0-9]+(,[0-9]+, …) or 
		 * --equation=Cn*X^N(+Cn-1*X^N-1+…).
		 * @param map Map to fill.
		 * @param args Command lines arguments.
		 * @throw invalid_argument when the value of coefs 
		 * or with-x is not properly formatted.
		 * @return (1) true if all fields are set as expected or
		 * (2) false if --with-x is not set and both --coefs and
		 * --equation are either set or unset.
		 */
		static bool setArgs(std::unordered_map<std::string, std::string> &map, char **args);
		/**
		 * Display one information if present in arguments.
		 * Displays the informations of the first --halp or --info token present
		 * in args then immediatly returns.
		 * @return (1) true if some information have been displayed or
		 * (2) false if no valid token was found.
		 */
		static bool displayInfo(std::unordered_map<std::string, std::string> &map, char **args);
		/**
		 * Convert a string of the form [0-9]+(,[0-9]+,…) to a queue of int.
		 * @throws invalid_argument if the list does not match the above regex.
		 * @return A queue with all numbers in order.
		 */
		static std::queue<int> listToQueue(std::string strList);
	};
}
