set(UNIT_TEST_LIST
    search)

foreach(NAME IN LISTS UNIT_TEST_LIST)
    list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}.test.cpp)
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME} main.cpp ${UNIT_TEST_SOURCE_LIST})

target_precompile_headers(${TARGET_NAME} PRIVATE ../source/utils/pch.h)
target_link_libraries(${TARGET_NAME} PUBLIC search)
target_link_libraries(${TARGET_NAME} PUBLIC profiling)
target_include_directories(${TARGET_NAME} PUBLIC ../externals/catch2)

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o report.xml -r junit)
