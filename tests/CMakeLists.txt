include(CTest)

file(GLOB SOURCES_CONCRETE "concrete/*.h")
file(GLOB TESTS "*.c")

foreach(TEST IN LISTS TESTS)
    cmake_path(GET TEST FILENAME FILE_NAME)
    add_executable(${FILE_NAME} ${TEST} ${SOURCES_CONCRETE})
    target_link_libraries(${FILE_NAME} PUBLIC wheel)
    add_test(NAME ${FILE_NAME} COMMAND ${FILE_NAME})
endforeach()
