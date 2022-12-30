include(CTest)

file(GLOB SOURCES_CONCRETE "concrete/*.h")
file(GLOB TESTS "*.c")

foreach(TEST IN LISTS TESTS)
    cmake_path(GET TEST FILENAME NAME)
    add_executable(${NAME} ${TEST} ${SOURCES_CONCRETE})
    target_link_libraries(${NAME} PUBLIC wheel)
    add_test(NAME ${NAME} COMMAND ${NAME})
endforeach()
