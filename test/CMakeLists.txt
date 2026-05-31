add_executable(ini_parser_test
    test_basic.c
)

target_link_libraries(ini_parser_test
    PRIVATE
        ini_parser
)

target_compile_definitions(ini_parser_test
    PRIVATE
        TEST_INI_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test.ini"
)

add_test(
    NAME ini_parser_test
    COMMAND ini_parser_test
)
