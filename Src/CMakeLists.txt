cmake_minimum_required(VERSION 3.28)

project(logger
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(logger_module)

target_sources(logger_module
    PUBLIC
    FILE_SET CXX_MODULES
    TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${CMAKE_SOURCE_DIR}/modules/log.cppm
)

target_include_directories(logger_module
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/logger/
        ${CMAKE_SOURCE_DIR}/include/global/
)

add_executable(log++_test
    ${PROJECT_SOURCE_DIR}/../tests/test.cpp
)

target_link_libraries(log++_test logger_module)

target_include_directories(log++_test 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/logger/
        ${PROJECT_SOURCE_DIR}/include/global/
)

add_custom_target(run
    DEPENDS log++_test
    COMMAND ${CMAKE_BINARY_DIR}/log++_test
)

add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}

)

function(add_release_and_debug_options_to_executable executable)
    # some saitizers for debug version
    set(DEBUG_SANITIZERS
        -fsanitize=address
        -fsanitize=alignment
        -fsanitize=bool
        -fsanitize=bounds
        -fsanitize=enum
        -fsanitize=float-cast-overflow
        -fsanitize=undefined
        -fsanitize=unreachable
        -fsanitize=vla-bound
        -fsanitize=vptr
        -fsanitize=float-divide-by-zero
        -fsanitize=integer-divide-by-zero
        -fsanitize=leak
        -fsanitize=nonnull-attribute
        -fsanitize=null
        -fsanitize=object-size
        -fsanitize=return
        -fsanitize=returns-nonnull-attribute
        -fsanitize=shift
        -fsanitize=signed-integer-overflow
    )

    set(DEBUG_FLAGS
        -D_DEBUG
        -DSAVE_HTML_STYLE
        -O0
        -Wall
        -Wextra
        -Wshadow
        -Weffc++
    )

    target_compile_options(${executable} PRIVATE
        # some santizers and DED32 debug flags for debug version
        $<$<CONFIG:Debug>:
            ${DEBUG_SANITIZERS}
            ${DEBUG_FLAGS}
        >
    )

    # linking sanitizers
    target_link_options(${executable} PRIVATE
        $<$<CONFIG:Debug>:
            ${DEBUG_SANITIZERS}
        >
    )

endfunction(add_release_and_debug_options_to_executable)

add_release_and_debug_options_to_executable(log++_test)

target_compile_options(logger_module PRIVATE
    $<$<CONFIG:Debug>:-DSAVE_HTML_STYLE>
)
