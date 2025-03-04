#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <future>

#include "testsConstanst.hpp"

using namespace std::literals::string_view_literals;

using Catch::Matchers::ContainsSubstring;
using Catch::Matchers::EndsWith;
using Catch::Matchers::Message;
using Catch::Matchers::MessageMatches;
using Catch::Matchers::StartsWith;
//  using Catch::Matchers::SizeIs;
//  using Catch::Matchers::Equals;

#define REQ_FORMAT(type, string) REQUIRE(FORMAT("{}", type) == (string));
#define REQ_FORMAT_COMPTOK(type, string) REQUIRE(FORMAT("{}", comp_tokType(type)) == (string));
#define MSG_FORMAT(...) Message(FORMAT(__VA_ARGS__))

TEST_CASE("Logger setup", "[setup_logger]") {
    SECTION("Default setup") { REQUIRE_NOTHROW(setup_logger()); }
    SECTION("Logger sinks") {
        setup_logger();
        auto logger = spdlog::default_logger();
        REQUIRE(logger->sinks().size() == 1);
    }
}