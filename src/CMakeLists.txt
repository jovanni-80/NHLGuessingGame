cmake_minimum_required(VERSION 3.27.1)

project(NHLPlayerGuesser)

add_executable(${PROJECT_NAME} main.cpp game.cpp player.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)