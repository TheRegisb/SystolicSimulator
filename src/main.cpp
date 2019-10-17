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
#include "Util/Parser.hpp"
#include <unordered_map>

int main(int ac, char **av)
{
	(void) ac;
	std::unordered_map<std::string, std::string> args;

	args["--help"] = "Usage: systolic OPTIONS\r\n"
		"OPTIONS:\r\n"
		"  --with-x=[0-9]+(,[0-9]+, …)\r\n"
		"  [--coefs=[0-9]+(,[0-9]+, …) | --equation=Cn*X^N(+Cn-1*X^N-1+…)\r\n"
		"  --verbose=[true|false] (false by default)\r\n"
		"  --about\r\n"
		"  --help";
	args["--about"] = "Systolic Simulator, made by Régis Berthelot, under the MIT lisence.";
	args["--coefs"] = "";
	args["--equation"] = "";
	args["--with-x"] = "";
	args["--verbose"] = "false";

	if (Util::Parser::displayInfo(args, av)) { // --info or --about were found.
		return EXIT_SUCCESS;
	}
	if (!Util::Parser::setArgs(args, av)) { // Bad arguments were given.
		return EXIT_FAILURE;
	}

	/* Example for 2x³ - 6x² + 2x - 1 */
	/* With X = 3, 4, 5, 6, 7 */
	Systolic::Container sc3({3, 4, 5, 6, 7}); // TODO Pass --with-x as queue

	sc3.setCells(Systolic::CellArrayBuilder::getNew()->fromPolynomialCoefs({2, -6, 2, -1})); // TODO Pass --coefs as queue
	sc3.compute();
	if (args["--verbose"] == "true") {
		std::cout << sc3.getLog() << std::endl;
	} else {
		sc3.dumpOutputs();
	}
	return EXIT_SUCCESS;
}
