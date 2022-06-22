cmake_minimum_required(VERSION 3.20)
cmake_policy(VERSION 3.20)
project(rpg_combat_kata)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(rpgCombatKata STATIC
    src/character.hxx src/character.cxx
    src/combat.hxx src/combat.cxx
    src/health.hxx src/health.cxx
    src/position.hxx
    src/cxx_17_traits.hxx
    )
target_include_directories(rpgCombatKata PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929
    # release-1.11.0
)
FetchContent_MakeAvailable(GoogleTest)

enable_testing()

add_executable(rpgCombatKataTests
    tests/character_tests.cxx
    tests/combat_tests.cxx
    tests/health_tests.cxx)
target_link_libraries(rpgCombatKataTests PRIVATE rpgCombatKata gtest gmock gmock_main)
add_test(NAME rpgCombatKataTests COMMAND rpgCombatKataTests)
