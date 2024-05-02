#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define RUN_TESTS

#include <vector>

#include "String.h"
#include "MenuManager.h"

TEST_CASE("testing ctors and assignment operators, casting") {
	{
		String s;
		CHECK_EQ(s, s);
		CHECK_EQ(s, String(""));
		CHECK_EQ(s, String(std::string("")));
		CHECK_NE(s, String("aa"));
		CHECK_EQ(s.getSize(), 0);
	}
	{
		const char* data = "fddsfsd";
		String s(data);
		CHECK_EQ(s, s);
		CHECK_EQ(s.toString(), std::string(data));
		CHECK_EQ(strcmp((const char*)s, data), 0);
		CHECK_EQ(s.getSize(), std::strlen(data));
	}
	{
		std::string data = "qwr435";
		String s = String(data);
		CHECK_EQ(s.toString(), data);
		CHECK_EQ(strcmp((const char*)s, data.c_str()), 0);
		CHECK_EQ(s.getSize(), data.length());

		String s2 = std::move(s);
		CHECK_EQ(s2.toString(), data);
		CHECK_EQ(s2.getSize(), data.length());

		String s3;
		s3 = std::move(s2);
		CHECK_EQ(strcmp((const char*)s3, data.c_str()), 0);
		CHECK_EQ(s3.getSize(), data.length());

		String s4 = s3;
		CHECK_EQ(strcmp((const char*)s3, data.c_str()), 0);
		CHECK_EQ(strcmp((const char*)s4, data.c_str()), 0);
		CHECK_EQ(s4.getSize(), data.length());

		String s5;
		s5 = s4;
		CHECK_EQ(s4.toString(), data);
		CHECK_EQ(s5.toString(), data);
		CHECK_EQ(s5.getSize(), data.length());
	}
}

TEST_CASE("testing comparison") {
	std::vector<std::string> lhsValues = {
		"", "", "a", "a", "b", "ab", "sadfgfg", "YkjfsdU", "aaaa", "_UqYtbb"
	};
	std::vector<std::string> rhsValues = {
		"", "a", "", "b", "a", "ba", "sadfgfg", "ykgtrh", "aaaaa", "UqYtbb"
	};
	for(size_t i = 0; i < lhsValues.size(); ++i) {
		auto& lhs = lhsValues[i];
		auto& rhs = rhsValues[i];
		String s1(lhs);
		String s2(rhs);
		CHECK_EQ(s1 == s2, lhs == rhs);
		CHECK_EQ(s1 < s2, lhs < rhs);
		CHECK_EQ(s1 > s2, lhs > rhs);
		CHECK_EQ(s1 <= s2, lhs <= rhs);
		CHECK_EQ(s1 >= s2, lhs >= rhs);
	}
}

TEST_CASE("testing concatenation") {
	std::vector<std::string> prefixes = {
		"", "a", "b", "ab", "sadfgfg", "YkjfsdU", "aaaa", "_UqYtbb"
	};
	std::vector<std::string> suffixes = {
		"", "a", "b", "ba", "Sadfgfg", "ykgtrh", "aaaaa", "UqYtbb"
	};
	for (const auto& prefix : prefixes) {
		for (const auto& suffix : suffixes) {
			String s1(prefix);
			String s2(suffix);
			String sum = s1 + s2;
			CHECK_EQ(sum, String(prefix + suffix));
			s1 += s2;
			CHECK_EQ(s1, sum);
		}
	}
	CHECK_EQ(String("aa") + String("bb") + String("cc"), String("aabbcc"));
	CHECK_EQ(String("daa") += String("bb") += String("cc"), String("daabbcc"));
}

int main()
{
#ifdef RUN_TESTS
	doctest::Context context;
	context.run();
#endif // RUN_TESTS
	Menu::MenuManager menu;
	menu.run();
}