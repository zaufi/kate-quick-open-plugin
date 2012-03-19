# kate: hl cmake;
set(UNIT_TESTS unit_tests)
set(UNIT_TESTS_SOURCES
    directory_scanner_tester.cpp
    ${PROJECT_SOURCE_DIR}/src/files_index.cpp
  )

add_executable(${UNIT_TESTS} ${UNIT_TESTS_SOURCES})

target_link_libraries(
    ${UNIT_TESTS}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${KDE4_KDEUI_LIBS}
  )

add_boost_tests(${UNIT_TESTS} "--catch_system_errors=no" ${UNIT_TESTS_SOURCES})
