# Copyright 2011 by Alex Turbov <i.zaufi@gmail.com>

# check if doxygen is even installed
find_package(Doxygen)
if(DOXYGEN_FOUND STREQUAL "NO")
    message(WARNING "Doxygen not found. Please get a copy http://www.doxygen.org to produce HTML documentation")
else()
    # prepare doxygen configuration file
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)

    # add doxygen as target
    add_custom_target(
        doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        DEPENDS ${CMAKE_BINARY_DIR}/Doxyfile
      )

    # cleanup $build/docs on "make clean"
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES docs)
    set_property(TARGET doxygen PROPERTY EchoString "Generate API documentation")

endif()
