/*
 * interpreter_tests.cpp
 *
 *  Created on: Dec 19, 2020
 *      Author: PnP
 */
#ifdef GTEST

#include <gtest/gtest.h>

#include "interpreter.h"

bool handler1_run = false;

void handler1()
{
	handler1_run = true;
}

TEST(interpreter, param_0)
{
	bvv::interpreter inter;
	inter.add_command("CMD1", handler1);
	inter.interpret("CMD1");

	EXPECT_TRUE(handler1_run);
}

bool handler2_run = false;
int handler2_par = 0;

const int PAR_I1 = 123;
const int PAR_I2 = 31;
const int PAR_I3 = 17;

void handler2(int i)
{
	handler2_par = i;
	handler2_run = true;
}

TEST(interpreter, int_param_1)
{
	bvv::interpreter inter;
	inter.add_command("CMD2", handler2);
	inter.interpret("CMD2 123  ");

	EXPECT_TRUE(handler2_run);
	EXPECT_EQ(PAR_I1, handler2_par);
}


bool handler3_run = false;
int handler3_par1 = 0;
int handler3_par2 = 0;

void handler3(int i1, int i2)
{
	handler3_par1 = i1;
	handler3_par2 = i2;
	handler3_run = true;
}

TEST(interpreter, int_param_2)
{
	bvv::interpreter inter;
	inter.add_command("CMD3", handler3);
	inter.interpret("CMD3 123 31 ");

	EXPECT_TRUE(handler3_run);
	EXPECT_EQ(PAR_I1, handler3_par1);
	EXPECT_EQ(PAR_I2, handler3_par2);
}

bool handler4_run = false;
int handler4_par1 = 0;
int handler4_par2 = 0;
int handler4_par3 = 0;

void handler4(int i1, int i2, int i3)
{
	handler4_par1 = i1;
	handler4_par2 = i2;
	handler4_par3 = i3;
	handler4_run = true;
}

TEST(interpreter, int_param_3_octal_hex_bin_format)
{
	bvv::interpreter inter;
	inter.add_command("CMD4", handler4);
	inter.interpret("CMD4 #Q173\t#h1f \t #b010001");

	EXPECT_TRUE(handler4_run);
	EXPECT_EQ(PAR_I1, handler4_par1);
	EXPECT_EQ(PAR_I2, handler4_par2);
	EXPECT_EQ(PAR_I3, handler4_par3);
}

bool handler5_run = false;
float handler5_par1 = 0;
double handler5_par2 = 0;
int handler5_par3 = 0;

const float PAR_F1 = -12.3f;
const double PAR_D2 = 2.34;

void handler5(float f1, double d2, int i3)
{
	handler5_par1 = f1;
	handler5_par2 = d2;
	handler5_par3 = i3;
	handler5_run = true;
}

TEST(interpreter, float_double_int_param_3)
{
	bvv::interpreter inter;
	inter.add_command("CMD5", handler5);
	inter.interpret("CMD5 -1.23e1\t+23.4e-1 \t #b010001");

	EXPECT_TRUE(handler5_run);
	EXPECT_FLOAT_EQ(PAR_F1, handler5_par1);
	EXPECT_NEAR(PAR_D2, handler5_par2, 1e-7);
	EXPECT_EQ(PAR_I3, handler5_par3);
}

bool handler6_run = false;
const char* handler6_par1 = 0;
float handler6_par2 = 0.0f;
int handler6_par3 = 0;

const char* PAR_S1 = "Qwerty!";

void handler6(const char* s1, double f2, int i3)
{
	handler6_par1 = s1;
	handler6_par2 = f2;
	handler6_par3 = i3;
	handler6_run = true;
}

TEST(interpreter, cstr_float_int_param3)
{
	bvv::interpreter inter;
	inter.add_command("CMD6", handler6);
	inter.interpret("CMD6\tQwerty! -0.123e2 \t #q173 ");

	EXPECT_TRUE(handler6_run);
	EXPECT_STREQ(PAR_S1, handler6_par1);
	EXPECT_EQ(PAR_F1, handler6_par2);
	EXPECT_EQ(PAR_I1, handler6_par3);
}

bool handler7_run = false;
const char* handler7_par1 = 0;
string_view handler7_par2;
string_view handler7_par3;

const string_view PAR_SV2 = "AsdfG$$"sv;
const string_view PAR_SV3 = "A§sd_"sv;

void handler7(const char* s1, string_view sv2, string_view sv3)
{
	handler7_par1 = s1;
	handler7_par2 = sv2;
	handler7_par3 = sv3;
	handler7_run = true;
}

TEST(interpreter, cstr_string_view_string_view_param3)
{
	bvv::interpreter inter;
	inter.add_command("CMD7", handler7);
	inter.interpret("CMD7\tQwerty! AsdfG$$ \tA§sd_ ");

	EXPECT_TRUE(handler7_run);
	EXPECT_STREQ(PAR_S1, handler7_par1);
	EXPECT_TRUE(PAR_SV2 == handler7_par2);
	EXPECT_TRUE(PAR_SV3 == handler7_par3);
}

#endif // GTEST
