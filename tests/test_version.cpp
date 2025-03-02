#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp> //test assertions
#include "version.hpp" //file to be tested

#include <new> //new, bad_alloc

using namespace dsh;

//START TEST: Default Version Construction on Stack Test, [stack-constructor]
TEST_CASE("Default Version Construction on Stack Test", "[stack-constructor]") {

    version ver;

    REQUIRE(ver.major == SHELL_VERSION_MAJOR);
    REQUIRE(ver.minor == SHELL_VERSION_MINOR);
    REQUIRE(ver.patch == SHELL_VERSION_PATCH);
    REQUIRE(ver.year == 2025);
    REQUIRE(ver.release == 0);
    REQUIRE(ver.st == stage::dev);
    REQUIRE(ver.rev == 0);

} //END TEST: Default Version Construction on Stack Test, [stack-constructor]

//START TEST: Default Version Construction Test on Heap Test, [heap-constructor]
TEST_CASE("Default Version Construction Test on Heap Test", "[heap-constructor]") {

    version * ver = new version{0, 0, 1, 2025, 0, stage::dev, 0};

    REQUIRE_NOTHROW(ver);
    REQUIRE_FALSE(ver == nullptr);

    REQUIRE(ver->major == SHELL_VERSION_MAJOR);
    REQUIRE(ver->minor == SHELL_VERSION_MINOR);
    REQUIRE(ver->patch == SHELL_VERSION_PATCH);
    REQUIRE(ver->year == 2025);
    REQUIRE(ver->release == 0);
    REQUIRE(ver->st == stage::dev);
    REQUIRE(ver->rev == 0);

    delete ver;

} //END TEST: Default Version Construction Test on Heap Test, [heap-constructor]

//START TEST: Version String Parsing Test, [stack-parsing]
TEST_CASE("Version String Parsing Test", "[stack-parsing]") {

    version ver = get_version("1.0.2");

    REQUIRE(ver.major == 1);
    REQUIRE(ver.minor == 0);
    REQUIRE(ver.patch == 2);

} //END TEST: Version String Parsing Test, [stack-parsing]

//START TEST: Version String Parsing Test, [heap-parsing]
TEST_CASE("Version String Parsing Test", "[heap-parsing]") {

    version * ver = new version(get_version("1.0.2"));

    REQUIRE_NOTHROW(ver);
    REQUIRE_FALSE(ver == nullptr);

    REQUIRE(ver->major == 1);
    REQUIRE(ver->minor == 0);
    REQUIRE(ver->patch == 2);

    delete ver;

} //END TEST: Version String Parsing Test, [heap-parsing]

//START TEST: Version String Formmating Test, [stack-format]
TEST_CASE("Version String Formmating Test", "[stack-format]") {

    version ver{1, 2, 3};

    REQUIRE(get_version_str(ver) == "1.2.3"); //default format value (Default = Semantic Format)

    REQUIRE(get_version_str(ver, VER_BRACED_FORMAT) == "{1,2,3}");
    REQUIRE(get_version_str(ver, VER_SQUARE_FORMAT) == "[1,2,3]");
    REQUIRE(get_version_str(ver, VER_PAREN_FORMAT) == "(1,2,3)");
    REQUIRE(get_version_str(ver, VER_SPACED_FORMAT) == "1 2 3");
    REQUIRE(get_version_str(ver, VER_UNDERSCORE_FORMAT) == "1_2_3");
    REQUIRE(get_version_str(ver, VER_SEMANTIC_FORMAT) == "1.2.3");

} //END TEST: Version String Formmating Test, [stack-format]

//START TEST: Version String Formmating Test, [heap-format]
TEST_CASE("Version String Formmating Test", "[heap-format]") {

    version * ver = new version{1, 2, 3};

    REQUIRE_NOTHROW(ver);
    REQUIRE_FALSE(ver == nullptr);

    REQUIRE(get_version_str(ver) == "1.2.3"); //default format value (Default = Semantic Format)

    REQUIRE(get_version_str(ver, VER_BRACED_FORMAT) == "{1,2,3}");
    REQUIRE(get_version_str(ver, VER_SQUARE_FORMAT) == "[1,2,3]");
    REQUIRE(get_version_str(ver, VER_PAREN_FORMAT) == "(1,2,3)");
    REQUIRE(get_version_str(ver, VER_SPACED_FORMAT) == "1 2 3");
    REQUIRE(get_version_str(ver, VER_UNDERSCORE_FORMAT) == "1_2_3");
    REQUIRE(get_version_str(ver, VER_SEMANTIC_FORMAT) == "1.2.3");

    delete ver;

} //END TEST: Version String Formmating Test, [heap-format]

//START TEST: Version Comparison Tests, [stack-comparison]
TEST_CASE("Version Comparison Tests", "[stack-comparison]") {

    version v1{1, 0, 0};
    version v2{1, 0, 1};

    REQUIRE(v1 < v2);
    REQUIRE(v2 > v1);
    REQUIRE(v1 <= v2);
    REQUIRE(v2 >= v1);
    REQUIRE_FALSE(v1 == v2);

} //END TEST: Version Comparison Tests, [stack-comparison]

//START TEST: Version Comparison Tests, [heap-comparison]
TEST_CASE("Version Comparison Tests", "[heap-comparison]") {

    version * v1 = new version{1, 0, 0};
    version * v2 = new version{1, 0, 1};

    REQUIRE_NOTHROW(v1);
    REQUIRE_NOTHROW(v2);

    REQUIRE_FALSE(v1 == nullptr);
    REQUIRE_FALSE(v2 == nullptr);

    REQUIRE(*v1 < *v2);
    REQUIRE(*v2 > *v1);
    REQUIRE(*v1 <= *v2);
    REQUIRE(*v2 >= *v1);
    REQUIRE_FALSE(*v1 == *v2);

    delete v1, v2;

} //END TEST: Version Comparison Tests, [heap-comparison]

//START TEST: Version Stage Enum Test, [stage]
TEST_CASE("Version Stage Enum Test", "[stage]") {

    REQUIRE(static_cast<int>(stage::preview) == 0);
    REQUIRE(static_cast<int>(stage::alpha) == 1);
    REQUIRE(static_cast<int>(stage::beta) == 2);
    REQUIRE(static_cast<int>(stage::release) == 3);
    REQUIRE(static_cast<int>(stage::dev) == 4);

} //END TEST: Version Stage Enum Test, [stage]