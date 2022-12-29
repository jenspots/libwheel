include(CTest)

file(GLOB SOURCES_CONCRETE "concrete/*.h")
add_executable(main main.c ${SOURCES_CONCRETE})
target_link_libraries(main PUBLIC wheel)
add_test(NAME main COMMAND main)
