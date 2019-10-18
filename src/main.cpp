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
	/* Creating command line argument handler. */
	std::unordered_map<std::string, std::string> args;

	args["--help"] = "Usage: systolic OPTIONS\r\n"
		"OPTIONS:\r\n"
		"  --with-x=[0-9]+(,[0-9]+, …)\r\n"
		"  [--coefs=[0-9]+(,[0-9]+, …) | --equation=Cn*X^N(+Cn-1*X^N-1+…)\r\n"
		"  --verbose=[true|false] (false by default)\r\n"
		"  --about\r\n"
		"  --help";
	args["--about"] = "Systolic Simulator, made by Régis Berthelot, under the Apache 2.0 lisence.";
	args["--coefs"] = "";
	args["--equation"] = "";
	args["--with-x"] = "";
	args["--verbose"] = "false";

	/* Display info. Exit program if --help or --about was used. */
	if (Util::Parser::displayInfo(args, av)) {
		return EXIT_SUCCESS;
	}

	/* Bad arguments were given. Reason printed by the setArgs function. */
	if (!Util::Parser::setArgs(args, av)) { // Bad arguments were given.
		return EXIT_FAILURE;
	}

	/* Declaring the container and settings its input to be the one given by the --with-x option. */
	Systolic::Container sc3(Util::Parser::listToQueue(args["--with-x"]));

	/* Using the builder to generate the polynomial cells from either the --coefs or --equation option. */
	if (!args["--coefs"].empty()) {
		sc3.setCells(Systolic::CellArrayBuilder::getNew()
			     ->fromPolynomialCoefs(Util::Parser::listToQueue(args["--coefs"])));
	} else {
		sc3.setCells(Systolic::CellArrayBuilder::getNew()
			     ->fromPolynomialEquation(args["--equation"]));
	}

	/* Running the systolic array until completion (output is filled and all cells are empty). */
	sc3.compute();

	/* Displaying either only the result or the full graphic log depending on the --verbose option. */
	if (args["--verbose"] == "true") {
		std::cout << sc3.getLog() << std::endl;
	} else {
		sc3.dumpOutputs();
	}
	return EXIT_SUCCESS;
}
