#include <doctest/doctest.h>
#include <a4z/filename.hpp>

#include <ostream>
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

SCENARIO("Truncate a astr") {
  GIVEN("some astr with 10 characters") {
    constexpr char abc[] = "0123456789";
    constexpr a4z::astr a10(abc);
    REQUIRE(a10.size() == 10);
    WHEN("requesting the last 5 characters") {
      constexpr auto a5 = a10.last_n<5>();
      THEN("we have a new astr of size 5") {
        CHECK(a5.size() == 5);
        std::string wanted = "56789";
        std::string_view having = a5;
        CHECK(wanted == having);
      }
    }
    WHEN("requesting the last characters of the same size") {
      // defacto a copy
      constexpr auto other = a10.last_n<a10.size()>();
      THEN("we have a new astr of size 10") {
        CHECK(other.size() == a10.size());
        std::string wanted = abc;
        std::string_view having = other;
        CHECK(wanted == having);
      }
    }
    WHEN("requesting the first 5 characters") {
      constexpr auto a5 = a10.first_n<5>();
      THEN("we have a new astr of size 5") {
        CHECK(a5.size() == 5);
        std::string wanted = "01234";
        std::string_view having = a5;
        CHECK(wanted == having);
      }
    }
    WHEN("requesting the first characters of the same size") {
      // defacto a copy
      constexpr auto other = a10.first_n<a10.size()>();
      THEN("we have a new astr of size 10") {
        CHECK(other.size() == a10.size());
        std::string wanted = abc;
        std::string_view having = other;
        CHECK(wanted == having);
      }
    }
  }
}

SCENARIO("Test with filename macro") {
  GIVEN("the current filename") {
    constexpr auto fn = a4z_file_name();

    WHEN("checking if it starts with base") {
      // cpp20
      //const auto starts_with_base = std::string(fn.c_str()).starts_with("base");
    const char* base = "base";
    auto start_str = fn.first_n<4>();
    const auto starts_with_base = a4z::equal(base,start_str.c_str());
      THEN("we find it at the expected position") {
        CHECK(starts_with_base);
      }
    }
    AND_WHEN("checking if it ends with ") {
      const char* filename = "filename_test.cpp";
      auto end_str = fn.last_n<17>();
      const auto ends_with_filename = a4z::equal(filename,end_str.c_str());
      // cpp20
      // std::string(fn.c_str()).ends_with("filename_test.cpp");
      THEN("we find it at the expected position") {
        CHECK(ends_with_filename);
      }
    }
  }
}
