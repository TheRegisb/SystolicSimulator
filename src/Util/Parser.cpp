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
 * @file Parser.cpp
 * Implementation of Parser.
 */

#include "Util/Parser.hpp"

bool Util::Parser::setArgs(std::unordered_map<std::string, std::string> &map, char **args)
{
	std::regex intListRegex("^-?[0-9]+((,-?[0-9]+)?)+$"); // Matches list of (possibly negative) integers separated by comme.
	
	for (unsigned int i = 1; args[i] != nullptr; i++) {
		std::string arg = args[i];
		std::string token = arg.substr(0, arg.find('='));
		std::string value = arg.substr(arg.find('=') + 1, arg.size());

		std::cout << "toke,: " << token << " : " << "value: " << value << std::endl;
		if (map.find(token) == map.end()) {
			std::cerr << "Error: Unknown option: " << token << std::endl;
			return false;
		} else if (token != value) { // token == value when the option is standalone, like --help.
			if ((token == "--coefs" || token == "--with-x")
			    && !std::regex_match(value, intListRegex)) {
				throw std::invalid_argument(std::string("Value of ") + token + " is not a valid list of interger.");
			} // TODO equation regex
			map[token] = value;
		}
	}
	if (map["--coefs"].empty() && map["--equation"].empty()) {
		std::cerr << "Error: Missing --coefs or --equation options." << std::endl;
		return false;
	}
	if (map["--with-x"].empty()) {
		std::cerr << "Error: Missing --with-x option." << std::endl;
		return false;
	}
	if (!map["--coefs"].empty() && !map["--equation"].empty()) {
		std::cerr << "Error: Cannot use both --coefs and --equation options at the same time." << std::endl;
		return false;
	}
	return true;
}

bool Util::Parser::displayInfo(std::unordered_map<std::string, std::string> &map, char **args)
{
	if (args == nullptr) {
		throw std::invalid_argument("args is null.");
	}
	for (unsigned int i = 0; args[i] != nullptr; i++) {
		if (std::strcmp(args[i], "--help") == 0
		    || std::strcmp(args[i], "--about") == 0) {
			std::cout << map[args[i]] << std::endl;
			return true;
		}
	}
	return false;
}

std::queue<int> Util::Parser::listToQueue(std::string strList)
{
	std::size_t pos = 0;
	std::queue<int> res;

	while ((pos = strList.find(',')) != std::string::npos) {
		res.push(std::atoi(strList.substr(0, pos).c_str()));
		strList.erase(0, pos + 1);
	}
	res.push(std::atoi(strList.c_str()));
	return res;
}
