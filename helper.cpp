/*
 * helper.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: PnP
 */
#include <cstdlib>
#include <cstring>
#include <string>
#include "helper.h"

namespace bvv
{
static string_view ws(" \t");

bool contains(string_view str, char ch) {
	return find(str.begin(), str.end(), ch) != str.end();
}

string_view skip_ws(string_view str) {
	auto cur = str.begin();
	while (cur != str.end() && contains(ws, *cur))
		++cur;

	return string_view(&*cur, str.end() - cur);
}

template<>
int get_param(string_view& sv)
{
	sv = skip_ws(sv);
	int base = 10;
#define PREF_LEN 2
	if(sv.substr(0, PREF_LEN) == "#H"sv || sv.substr(0, PREF_LEN) == "#h"sv)
	{
		base = 16;
		sv = sv.substr(PREF_LEN, sv.size() - PREF_LEN);
	}
	else if(sv.substr(0, PREF_LEN) == "#Q"sv || sv.substr(0, PREF_LEN) == "#q"sv)
	{
		base = 8;
		sv = sv.substr(PREF_LEN, sv.size() - PREF_LEN);
	}
	else if(sv.substr(0, PREF_LEN) == "#B"sv || sv.substr(0, PREF_LEN) == "#b"sv)
	{
		base = 2;
		sv = sv.substr(PREF_LEN, sv.size() - PREF_LEN);
	}

	int value;
	auto res = from_chars(sv.data(), sv.data() + sv.size(), value, base);
	if(res.ec != errc())
	{
		// TODO: remove string because of memory allocations
		string mess("can not parse integer:");
		mess += string(sv.data(),  sv.size());
		throw invalid_argument(mess);
	}

	sv = string_view(res.ptr, &sv.data()[sv.size()] - res.ptr);
	return value;
};

template<>
float get_param(string_view& sv)
{
	sv = skip_ws(sv);

	// TODO: remove string because of memory allocations
	string s1(sv.data(), sv.size());
	char* end;
	float value = strtof(s1.c_str(), &end);
	auto len = end - s1.data();
	sv = string_view(sv.data() + len, sv.size() - len);
	return value;
};

template<>
double get_param(string_view& sv)
{
	sv = skip_ws(sv);

	// TODO: remove string because of memory allocations
	string s1(sv.data(), sv.size());
	char* end;
	double value = strtod(s1.c_str(), &end);
	auto len = end - s1.data();
	sv = string_view(sv.data() + len, sv.size() - len);
	return value;
};

template<>
string_view get_param(string_view& sv)
{
	sv = skip_ws(sv);

	auto cur = sv.begin();
	while (cur != sv.end() && !contains(ws, *cur))
		++cur;
	string_view ret = string_view(sv.data(), cur - sv.begin());
	sv = string_view(&*cur, sv.end() - cur);
	return ret;
};

#define MAX_CSTR_BUF_SIZE 128
template<>
const char* get_param(string_view& sv)
{
	sv = skip_ws(sv);

	static char buffer[MAX_CSTR_BUF_SIZE];

	auto cur = sv.begin();
	while (cur != sv.end() && !contains(ws, *cur))
		++cur;

	strncpy(buffer, sv.data(), cur - sv.begin());
	sv = string_view(&*cur, sv.end() - cur);
	return buffer;
}


}


