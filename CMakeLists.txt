cmake_minimum_required(VERSION 3.24)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)

# Do not allow any warnings.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

project(libwheel_poc
        LANGUAGES C
        VERSION 0.0.1)

add_subdirectory(include)

enable_testing()
add_subdirectory(tests)
