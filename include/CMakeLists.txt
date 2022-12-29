file(GLOB SOURCES "wheel/*.h")

add_library(wheel SHARED ${SOURCES})
set_property(TARGET wheel PROPERTY LINKER_LANGUAGE C)
set_property(TARGET wheel PROPERTY POSITION_INDEPENDENT_CODE 1)

target_include_directories(wheel PUBLIC .)

install(FILES ${SOURCES} DESTINATION include/wheel)