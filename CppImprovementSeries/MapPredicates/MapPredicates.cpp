#include <map>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

struct param {
    size_t v;
    param(size_t v_) : v(v_) {}
    param(const param& v_) : v(v_.v) {}
    bool operator>(const param& rhs) const {
        return v > rhs.v;
    }
};

template<typename T>
struct cmpDesc {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs > rhs;
    }
};

TEST_CASE("testing size_t predicates with ctor") {
    std::map<size_t, std::string, cmpDesc<size_t>> m = {
        {2, "two"},
        {1, "one"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k, correct[counter++]);
    }

    auto found = m.find(2);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "two");
    found = m.find(10);
    REQUIRE(found == m.end());
}

TEST_CASE("testing size_t predicates with insert") {
    std::map<size_t, std::string, cmpDesc<size_t>> m;
    SUBCASE("Ascending") {
        auto res = m.insert({ 1, "one" });
        CHECK(res.second);
        res = m.insert({ 2, "two" });
        CHECK(res.second);
        res = m.insert({ 3, "three" });
        CHECK(res.second);
        res = m.insert({ 4, "four" });
        CHECK(res.second);
        res = m.insert({ 5, "five" });
        CHECK(res.second);
        res = m.insert({ 3, "replace_three" });
        CHECK_FALSE(res.second);
    }
    SUBCASE("Descending") {
        auto res = m.insert({ 5, "five" });
        CHECK(res.second);
        res = m.insert({ 4, "four" });
        CHECK(res.second);
        res = m.insert({ 3, "three" });
        CHECK(res.second);
        res = m.insert({ 2, "two" });
        CHECK(res.second);
        res = m.insert({ 1, "one" });
        CHECK(res.second);
        res = m.insert({ 1, "replace_one" });
        CHECK_FALSE(res.second);
    }
    SUBCASE("Random") {
        auto res = m.insert({ 2, "two" });
        CHECK(res.second);
        res = m.insert({ 1, "one" });
        CHECK(res.second);
        res = m.insert({ 5, "five" });
        CHECK(res.second);
        res = m.insert({ 3, "three" });
        CHECK(res.second);
        res = m.insert({ 4, "four" });
        CHECK(res.second);
        res = m.insert({ 2, "replace_two" });
        CHECK_FALSE(res.second);
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto  counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k, correct[counter++]);
    }

    auto found = m.find(3);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "three");
    found = m.find(6);
    REQUIRE(found == m.end());
}

TEST_CASE("testing param predicates with ctor") {
    std::map<param, std::string, cmpDesc<param>> m = {
        {{2}, "two"},
        {{1}, "one" },
        {{3}, "three" },
        {{4}, "four" },
        {{5}, "five" },
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto  counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k.v, correct[counter++]);
    }

    auto found = m.find(1);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "one");
    found = m.find(6);
    REQUIRE(found == m.end());
}

TEST_CASE("testing param predicates with insert") {
    std::map<param, std::string, cmpDesc<param>> m;
    SUBCASE("Ascending") {
        auto res = m.insert({1, "one"});
        CHECK(res.second);
        res = m.insert({ 2, "two" });
        CHECK(res.second);
        res = m.insert({ 3, "three" });
        CHECK(res.second);
        res = m.insert({ 4, "four" });
        CHECK(res.second);
        res = m.insert({ 5, "five" });
        CHECK(res.second);
        res = m.insert({ 3, "replace_three" });
        CHECK_FALSE(res.second);
    }
    SUBCASE("Descending") {
        auto res = m.insert({ 5, "five" });
        CHECK(res.second);
        res = m.insert({ 4, "four" });
        CHECK(res.second);
        res = m.insert({ 3, "three" });
        CHECK(res.second);
        res = m.insert({ 2, "two" });
        CHECK(res.second);
        res = m.insert({ 1, "one" });
        CHECK(res.second);
        res = m.insert({ 1, "replace_one" });
        CHECK_FALSE(res.second);
    }
    SUBCASE("Random") {
        auto res = m.insert({ 2, "two" });
        CHECK(res.second);
        res = m.insert({ 1, "one" });
        CHECK(res.second);
        res = m.insert({ 5, "five" });
        CHECK(res.second);
        res = m.insert({ 3, "three" });
        CHECK(res.second);
        res = m.insert({ 4, "four" });
        CHECK(res.second);
        res = m.insert({ 2, "replace_two" });
        CHECK_FALSE(res.second);
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto  counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k.v, correct[counter++]);
    }

    auto found = m.find(1);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "one");
    found = m.find(6);
    REQUIRE(found == m.end());
}

// lambda has unique type
TEST_CASE("testing size_t inline predicates with initialization list") {
    std::map < size_t, std::string, decltype([](const size_t& lhs, const size_t& rhs) {return lhs > rhs; })> m = {
        {2, "two"},
        {1, "one"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k, correct[counter++]);
    }

    auto found = m.find(2);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "two");
    found = m.find(10);
    REQUIRE(found == m.end());
}

TEST_CASE("testing size_t inline predicates (with auto parameters) with initialization list") {
    std::map < size_t, std::string, decltype([](const auto& lhs, const auto& rhs) {return lhs > rhs; }) > m = {
        {2, "two"},
        {1, "one"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k, correct[counter++]);
    }

    auto found = m.find(2);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "two");
    found = m.find(10);
    REQUIRE(found == m.end());
}

TEST_CASE("testing param inline predicates with initialization list") {
    std::map<param, std::string, decltype([](const param& lhs, const param& rhs) {return lhs > rhs; })> m = {
        {{2}, "two"},
        {{1}, "one" },
        {{3}, "three" },
        {{4}, "four" },
        {{5}, "five" },
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto  counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k.v, correct[counter++]);
    }

    auto found = m.find(1);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "one");
    found = m.find(6);
    REQUIRE(found == m.end());
}

TEST_CASE("testing param inline predicates (with auto parameters) with initialization list") {
    std::map < param, std::string, decltype([](const auto& lhs, const auto& rhs) {return lhs > rhs; }) > m = {
        {{2}, "two"},
        {{1}, "one" },
        {{3}, "three" },
        {{4}, "four" },
        {{5}, "five" },
    };
    std::vector<size_t> correct = { 5, 4, 3, 2, 1 };
    REQUIRE_EQ(correct.size(), m.size());
    auto  counter = 0;
    for (const auto& [k, v] : m) {
        CHECK_EQ(k.v, correct[counter++]);
    }

    auto found = m.find(1);
    REQUIRE(found != m.end());
    CHECK_EQ(found->second, "one");
    found = m.find(6);
    REQUIRE(found == m.end());
}