#include <catch.hpp>
#include "search/search.h"

SCENARIO("strings can be left-padded") {
  GIVEN("a string") {
    using namespace std::string_literals;
    auto string = "schneide"s;

    WHEN("the string is padded with lower length") {
      auto length = 4;
      REQUIRE(length < string.length());
      THEN("it stays the same") {
        REQUIRE(cog::search::left_pad(string, length) == string);
      }
    }

    WHEN("the string is padded with a higher length") {
      std::size_t length = 16;
      REQUIRE(length > string.length());
      THEN("empty characters are inserted to the left and the length is changed") {
        auto padded = cog::search::left_pad(string, length);
        REQUIRE(length == padded.length());
        auto padding = padded.substr(0, length - string.length());
        REQUIRE(padding == std::string(8, ' '));
      }
    }
  }
}