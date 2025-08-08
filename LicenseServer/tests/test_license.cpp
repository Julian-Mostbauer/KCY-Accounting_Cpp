#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/License.h"

TEST_CASE("License::fromString parses valid license string", "[license]") {
    std::string input = "example;example;2;0;example_mac_1,example_mac_2";
    License lic = License::fromString(input);
    REQUIRE(lic.Name == "example");
    REQUIRE(lic.LicenseKey == "example");
    REQUIRE(lic.AllowedUsers == 2);
    REQUIRE(lic.RedeemedUsers == 0);
    REQUIRE(lic.AllowedMacs.size() == 2);
    REQUIRE(lic.AllowedMacs[0] == "example_mac_1");
    REQUIRE(lic.AllowedMacs[1] == "example_mac_2");
}

TEST_CASE("License::fromString handles empty AllowedMacs", "[license]") {
    std::string input = "x;kxrim;2;0;";
    License lic = License::fromString(input);
    REQUIRE(lic.Name == "x");
    REQUIRE(lic.LicenseKey == "kxrim");
    REQUIRE(lic.AllowedUsers == 2);
    REQUIRE(lic.RedeemedUsers == 0);
    REQUIRE(lic.AllowedMacs.empty());
}

TEST_CASE("License::toString outputs correct format", "[license]") {
    License lic;
    lic.Name = "x";
    lic.LicenseKey = "kxrim";
    lic.AllowedUsers = 2;
    lic.RedeemedUsers = 0;
    lic.AllowedMacs = {"mac1", "mac2"};
    std::string expected = "x;kxrim;2;0;mac1,mac2";
    REQUIRE(lic.toString() == expected);
}

TEST_CASE("License::fromString throws on empty line", "[license]") {
    const std::string input;
    REQUIRE_THROWS_AS(License::fromString(input), std::runtime_error);
}

