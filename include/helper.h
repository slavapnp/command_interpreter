/*
 * helper.h
 *
 *  Created on: Dec 18, 2020
 *      Author: pnp
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <functional>
#include <string_view>
#include <charconv>
#include <stdexcept>

using namespace std;

namespace bvv
{

bool contains(string_view str, char ch);

string_view skip_ws(string_view str);

template<typename T>
T get_param(string_view& sv)
{};

template<>
int get_param(string_view& sv);

template<>
float get_param(string_view& sv);

template<>
double get_param(string_view& sv);

template<>
string_view get_param(string_view& sv);

template<>
const char* get_param(string_view& sv);

inline void call_fn0(const function<void()>& fn)
{
	fn();
}

template<typename T>
inline void call_fn1(const function<void(T)>& fn, string_view sv)
{
	T p1 = get_param<T>(sv);
	fn(p1);
}

template<typename T, typename U>
inline void call_fn2(const function<void(T, U)>& fn, string_view sv)
{
	T p1 = get_param<T>(sv);
	U p2 = get_param<U>(sv);
	fn(p1, p2);
}

template<typename T, typename U, typename V>
inline void call_fn3(const function<void(T, U, V)>& fn, string_view sv)
{
	T p1 = get_param<T>(sv);
	U p2 = get_param<U>(sv);
	V p3 = get_param<V>(sv);
	fn(p1, p2, p3);
}

}
#endif /* HELPER_H_ */
