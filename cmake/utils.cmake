macro(conan_init)
    execute_process(
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND conan install ${CMAKE_SOURCE_DIR}
    )

    set(CONAN_CMAKE_FILE ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CONAN_CMAKE_FILE})

    conan_basic_setup()
endmacro()