#include <doctest/doctest.h>
#include <a4z/typename.hpp>

#include <string>
#include <vector>

// This shows a few use cases,
// should be clear that this is not a real reflection and has limits

SCENARIO("Check simple typename") {
  GIVEN("the typename of an int") {
    auto tn = a4z::type_name<int>();
    WHEN("expecting the according typename") {
      std::string expected = "int";
      THEN("the typename matches the expected one") {
        CHECK(std::string{tn.c_str()} == expected);
      }
    }
  }
}

struct Foo {};

SCENARIO("Check struct typename") {
  GIVEN("the typename of Foo") {
    auto tn = a4z::type_name<Foo>();
    WHEN("expecting the according typename") {
      std::string expected = "Foo";
      THEN("the typename matches the expected one") {
        CHECK(std::string{tn.c_str()} == expected);
      }
    }
  }
}

namespace bar {
  struct Foo {};
}  // namespace bar

SCENARIO("Check struct in a namespace typename") {
  GIVEN("the typename of Foo") {
    auto tn = a4z::type_name<bar::Foo>();
    WHEN("expecting the according typename") {
      std::string expected = "bar::Foo";
      THEN("the typename matches the expected one") {
        CHECK(std::string{tn.c_str()} == expected);
      }
    }
  }
}

// This shows how to customize the typename for a type where compilers have
// different display names std::string could be something like
// basic_string<char, char_traits<char>, allocator<char>> and this is nothing
// you want to see (except for debug purposes)
namespace a4z {
  template <>
  constexpr auto type_name<std::string>() {
    return a4z::astr<12>{"std::string"};
  }
}  // namespace a4z

// std::string is always a bit special , basic_string blab bla bla
SCENARIO("Check specialized typename") {
  GIVEN("the typename of std::string") {
    constexpr auto tn = a4z::type_name<std::string>();
    static_assert(a4z::equal("std::string", tn.c_str()));  // real compile time
    WHEN("expecting the according typename") {
      std::string expected = "std::string";
      THEN("the typename matches the expected one") {
        CHECK(std::string{tn.c_str()} == expected);
      }
    }
  }
}
