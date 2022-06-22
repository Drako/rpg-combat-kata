cmake_minimum_required(VERSION 3.20)
cmake_policy(VERSION 3.20)
project(rpg_combat_kata)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929
    # release-1.11.0
)
FetchContent_Declare(
    GSL
    GIT_REPOSITORY https://github.com/Microsoft/GSL.git
    GIT_TAG a3534567187d2edc428efd3f13466ff75fe5805c
    # v4.0.0
)
FetchContent_MakeAvailable(GoogleTest GSL)

add_library(rpgCombatKata STATIC
    src/health.hxx src/health.cxx
     src/character.hxx src/character.cxx)
target_include_directories(rpgCombatKata PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")
target_link_libraries(rpgCombatKata PUBLIC Microsoft.GSL::GSL)

enable_testing()

add_executable(rpgCombatKataTests
    tests/health_tests.cxx tests/character_tests.cxx)
target_link_libraries(rpgCombatKataTests PRIVATE rpgCombatKata gtest gmock gmock_main)
add_test(NAME rpgCombatKataTests COMMAND rpgCombatKataTests)
