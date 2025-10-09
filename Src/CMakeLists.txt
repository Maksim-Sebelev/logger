cmake_minimum_required(VERSION 3.28)

project(logger
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================

if (NOT DEFINED LOG_OUT_DIR)
    set(LOG_OUT_DIR ${CMAKE_BINARY_DIR}/../log)
endif()

set(LOGGER_LIB logger)

add_library(${LOGGER_LIB})

target_sources(${LOGGER_LIB}
    PUBLIC
    FILE_SET CXX_MODULES
    TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${PROJECT_SOURCE_DIR}/modules/log.cppm
)

target_include_directories(${LOGGER_LIB}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/logger/
        ${PROJECT_SOURCE_DIR}/include/global/
)

target_compile_definitions(${LOGGER_LIB} PRIVATE
    LOG_DIR="${LOG_OUT_DIR}/"
    $<$<CONFIG:Debug>:SAVE_HTML_STYLE>
)

# ======================================================================

# creating test for logger
set(TEST_TARGET log_test)
add_executable(${TEST_TARGET}
    EXCLUDE_FROM_ALL
    ${PROJECT_SOURCE_DIR}/../tests/test.cpp
)

target_link_libraries(${TEST_TARGET} ${LOGGER_LIB})

target_include_directories(${TEST_TARGET} 
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/logger/
        ${PROJECT_SOURCE_DIR}/include/global/
)

add_custom_target(run
    DEPENDS ${TEST_TARGET}
    COMMAND ${PROJECT_BINARY_DIR}/${TEST_TARGET}
)

add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR}

)

function(add_release_and_debug_options_to_target executable)
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

endfunction(add_release_and_debug_options_to_target)

add_release_and_debug_options_to_target(${TEST_TARGET})
add_release_and_debug_options_to_target(${LOGGER_LIB})
