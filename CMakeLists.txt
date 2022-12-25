cmake_minimum_required(VERSION 3.21)
project(CandyCrush LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CandyCrush src/main.cpp)
target_link_libraries(CandyCrush PRIVATE sfml-graphics)
target_compile_features(CandyCrush PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CandyCrush POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CandyCrush> $<TARGET_FILE_DIR:CandyCrush> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CandyCrush)