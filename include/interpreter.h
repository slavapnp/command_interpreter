/*
 * interpreter.cpp
 *
 *  Created on: Dec 17, 2020
 *      Author: pnp
 */
#ifndef INTERPRETER_CPP_
#define INTERPRETER_CPP_

#include <string_view>
#include <array>
#include <vector>
#include <functional>
#include "helper.h"

using namespace std;

namespace bvv
{

struct command_t
{
	string_view command;
	function<void(string_view)> handler;
};

class interpreter
{
public:
	template<typename... args>
	void add_command(string_view command, void (phandler)(args...))
	{
		const function<void(args...)> fn(phandler);
		if constexpr (sizeof...(args) == 0)
			commands.push_back(command_t{command, [=](string_view){call_fn0(fn);}});
		else if constexpr (sizeof...(args) == 1)
			commands.push_back(command_t{command, [=](string_view sv){call_fn1(fn, sv);}});
		else if constexpr (sizeof...(args) == 2)
			commands.push_back(command_t{command, [=](string_view sv){call_fn2(fn, sv);}});
		else if constexpr (sizeof...(args) == 3)
			commands.push_back(command_t{command, [=](string_view sv){call_fn3(fn, sv);}});
		else
			throw length_error("too many arguments, not supported");
	}

	void interpret(string_view line);
private:
	command_t find_command(string_view cmd_s);

	vector<command_t> commands;
};

}
#endif /* INTERPRETER_CPP_ */
