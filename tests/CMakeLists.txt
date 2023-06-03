include(CTest)

file(GLOB impl "impl/*.h")
file(GLOB TESTS "./*.c" "./**/*.c")

foreach(TEST IN LISTS TESTS)
    cmake_path(GET TEST FILENAME NAME)
    add_executable(${NAME} ${TEST} ${HEADERS})
    target_link_libraries(${NAME} PUBLIC wheel)
    add_test(NAME ${NAME} COMMAND ${NAME})
endforeach()
