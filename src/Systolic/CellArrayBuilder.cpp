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
 * @file CellArrayBuilder.cpp
 * Implementation of CellArrayBuilder.
 */

#include "Systolic/Container/CellArrayBuilder.hpp"

std::shared_ptr<Systolic::CellArrayBuilder> Systolic::CellArrayBuilder::getNew()
{
	return std::make_shared<Systolic::CellArrayBuilder>();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::add(const Systolic::Cell::Types cellType,
				const int term)
{
	if (cellType == Systolic::Cell::Types::Custom) {
		throw std::invalid_argument("Cannot declare a custom cell with a single integer term.");
	}
	cellArray.push_back(std::move(getInstanceFromEnum(cellType, term)));
	return shared_from_this();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::add(const Systolic::Cell::Types cellType,
				const std::function<int(const int)> customFunc)
{
	if (cellType != Systolic::Cell::Types::Custom) {
		throw std::invalid_argument("Cannot use a custom function on a predefined cell.");
	}
	cellArray.push_back(std::make_unique<Systolic::Cell::CustomCell>(customFunc));
	return shared_from_this();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::fromPolynomialCoefs(const std::initializer_list<int> coefs)
{
	for (int coef : coefs) {
		cellArray.push_back(getInstanceFromEnum(Systolic::Cell::Types::Polynomial, coef));
	}
	return shared_from_this();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::fromPolynomialCoefs(const std::queue<int> coefs)
{
	std::queue<int> ccoefs = coefs;

	while (!ccoefs.empty()) {
		cellArray.push_back(getInstanceFromEnum(Systolic::Cell::Types::Polynomial, ccoefs.front()));
		ccoefs.pop();
	}
	return shared_from_this();
}

std::shared_ptr<Systolic::CellArrayBuilder>
Systolic::CellArrayBuilder::fromPolynomialEquation(std::string equation)
{
	std::vector<std::pair<int, int>> res = getCoefsPair(reformat(equation));

	fillMissingCoefs(res);
	for (std::pair<int, int> pr : res) {
		add(Systolic::Cell::Types::Polynomial, std::get<0>(pr));
	}
	return shared_from_this();
}

std::vector<std::unique_ptr<Systolic::Cell::ICell>> Systolic::CellArrayBuilder::build()
{
	return std::move(cellArray);
}

/* Privates functions. */

std::unique_ptr<Systolic::Cell::ICell>
Systolic::CellArrayBuilder::getInstanceFromEnum(const Systolic::Cell::Types type, const int term)
{
	using namespace Systolic::Cell;
	
	switch(type) {
	case Types::Addition:
		return std::make_unique<AdditiveCell>(term);
	case Types::Multiplication:
		return std::make_unique<MultiplicativeCell>(term);
	case Types::Division:
		return std::make_unique<DivisionCell>(term);
	case Types::Square:
		return std::make_unique<SquareCell>();
	case Types::Power:
		return std::make_unique<PowerCell>(term);
	case Types::Polynomial:
		return std::make_unique<PolynomialCell>(term);
	default:
		throw std::runtime_error("Use of an unimplemented cell.");
	}
}

std::vector<std::string> Systolic::CellArrayBuilder::splitOnRegex(const std::string stringToSplit,
								  const std::string regexPattern) const
{
	std::vector<std::string> res;
	std::regex re(regexPattern);
	std::regex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), re, -1);

	for (std::sregex_token_iterator end; iter != end; ++iter) {
		res.push_back(iter->str());
	}
	return res;
}

inline std::string Systolic::CellArrayBuilder::reformat(const std::string &equation) const
{
	std::string e2 = equation;

	std::replace(e2.begin(), e2.end(), 'X', 'x');
	e2 = std::regex_replace(e2, std::regex("-"), "+-"); // Appends a + signe to every - sign.
	e2 = std::regex_replace(e2, std::regex("\\++"), "+"); // Removes duplicate + signs.
	return e2;
}

inline std::vector<std::pair<int, int>>
Systolic::CellArrayBuilder::getCoefsPair(const std::string equation) const
{
	std::vector<std::string> members = splitOnRegex(equation, "\\+");
	std::vector<std::pair<int, int>> res;

	for (std::string member : members) { // Split equation on + sign (i.e 2x+3 = {2x, 3})
		if (member.empty()) {
			continue;
		}
		if (member.find("x") == std::string::npos) {
			res.push_back(std::make_pair(std::atoi(member.c_str()), 0));
			continue;
		}
		std::vector<std::string> sub = splitOnRegex(member, "x");
		for (std::string &s : sub) {
			s.erase(std::remove_if(s.begin(), s.end(), // Removes character that are neither number or minus sign.
					       [](char c) { return !(c == '-' || std::isdigit(c)); } ),
				s.end());
			if (s == "-") {
				s = "-1";
			}
		}
		res.push_back(std::make_pair((sub[0].empty() ? 1 : std::atoi(sub[0].c_str())), // Ceate a pair of the form {Coefficient, N}
					     (sub.size() == 2 ? std::atoi(sub[1].c_str()) : 1)));
	}
	return res;
}

inline void Systolic::CellArrayBuilder::fillMissingCoefs(std::vector<std::pair<int, int>> &coefs) const
{
	/* Sorting pairs by their N value (the 2nd member of the pair). */
	std::sort(coefs.begin(), coefs.end(),
		  [] (const std::pair<int, int> &a, const std::pair<int, int> &b) {
			  return std::get<1>(a) > std::get<1>(b);
		  });
	/* Adding a coef pair {0, Ni} as to have a continuous series from N to 0. */
	for (std::size_t i = 0; i != coefs.size() && std::get<1>(coefs[i]) != 1; i++) {
		if (std::get<1>(coefs[i]) - 1 != std::get<1>(coefs[i + 1])) {
			coefs.push_back(std::make_pair(0, std::get<1>(coefs[i]) - 1));
			std::sort(coefs.begin(), coefs.end(),
				  [] (const std::pair<int, int> &a, const std::pair<int, int> &b) {
					  return std::get<1>(a) > std::get<1>(b);
				  });
			i = i - 1; // Recheck at the current index.
		}
	}
}
