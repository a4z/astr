#include <doctest/doctest.h>
#include <a4z/filename.hpp>

#include <string>

SCENARIO("Check find slashes") {
  GIVEN("a string with more than 2 slashes") {
    constexpr char abc[] = "/a/b/c";

    WHEN("looking for the second last string") {
      constexpr auto n = a4z::find_nth_r_occurrence(abc, '/', 2);
      THEN("we find it at the expected position") {
        CHECK(n == 2);
        CHECK(abc[n] == '/');
      }
    }
  }

  GIVEN("a string with just 1 slash") {
    constexpr char abc[] = "ab/c";

    WHEN("looking for the second last string") {
      constexpr auto n = a4z::find_nth_r_occurrence(abc, '/', 2);
      THEN("we get npos") {
        CHECK(n == std::string::npos);
      }
    }
  }
  // all I need now is copy the part into a carrier
  // and there is a constant file name implementation
}

SCENARIO("Test with filename macro") {
  GIVEN("the current filename") {
    constexpr auto fn = a4z_file_name();

    WHEN("checking if it starts with base") {
      const auto starts_with_base = std::string(fn.c_str()).starts_with("base");
      THEN("we find it at the expected position") {
        CHECK(starts_with_base);
      }
    }
    AND_WHEN("checking if it ends with ") {
      const auto ends_with_filename =
          std::string(fn.c_str()).ends_with("filename_test.cpp");
      THEN("we find it at the expected position") {
        CHECK(ends_with_filename);
      }
    }
  }
}
