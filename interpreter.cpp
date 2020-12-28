#include <algorithm>
#include <tuple>
#include <stdexcept>
#include "interpreter.h"

using namespace std;

namespace bvv
{

inline bool in_range(char start, char end, char ch) {
	return start <= ch && ch <= end;
}

// CMD := [A-Z_0_9]+
tuple<string_view, string_view> parse_cmd(string_view str) {
	auto cur = str.begin();
	while (cur != str.end()
			&& (in_range('A', 'Z', *cur) || *cur == '_'
					|| in_range('0', '9', *cur)))
		++cur;
	return make_tuple(string_view(&str.data()[cur - str.begin()], str.end() - cur),
			string_view(str.data(), cur - str.begin()));
}

command_t interpreter::find_command(string_view cmd_s) {
	auto it = find_if(commands.begin(), commands.end(), [&cmd_s](auto &v) {
		return v.command == cmd_s;
	});
	if (it == commands.end())
		throw runtime_error("command not found");

	return *it;
}

void interpreter::interpret(string_view line) {
	string_view cur = skip_ws(line);
	string_view cmd_s;
	tie(cur, cmd_s) = parse_cmd(cur);
	auto cmd = find_command(cmd_s);
	cmd.handler(cur);
}

}
