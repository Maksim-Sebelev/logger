cmake_minimum_required(VERSION 3.28)

project(logger
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================

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
        -fsanitize=return
        -fsanitize=returns-nonnull-attribute
        -fsanitize=shift
        -fsanitize=signed-integer-overflow
        # -fsanitize=object-size
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

    # some santizers and DED32 debug flags for debug version
    target_compile_options(${executable} PRIVATE
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

# ======================================================================

endfunction(add_release_and_debug_options_to_target)
if (NOT DEFINED LOG_OUT_DIR)
    set(LOG_OUT_DIR ${CMAKE_BINARY_DIR}/../log)
endif()

set(LOGGER_LIB logger)

add_library(${LOGGER_LIB})

target_sources(${LOGGER_LIB}
    PUBLIC
    FILE_SET CXX_MODULES
    TYPE CXX_MODULES
    FILES
        ${PROJECT_SOURCE_DIR}/modules/log.cppm
)

target_include_directories(${LOGGER_LIB}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/logger/
        ${PROJECT_SOURCE_DIR}/include/global/
)

target_compile_definitions(${LOGGER_LIB} PRIVATE
    LOG_DIR="${LOG_OUT_DIR}/"
    $<$<CONFIG:Debug>:SAVE_HTML_STYLE>
    # GLOBAL_LOGGER_IMAGE="/path/to/image"
    # GLOBAL_LOGGER_GRADIENT
    # GLOBAL_LOGGER_DEFAULT
)

add_release_and_debug_options_to_target(${LOGGER_LIB})

# ======================================================================
# remove all log files target

add_custom_target(log_clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${LOG_OUT_DIR}/
)

# ======================================================================

# creating test for logger
set(TEST_TARGET log_test)
add_executable(${TEST_TARGET} EXCLUDE_FROM_ALL
    ${PROJECT_SOURCE_DIR}/../tests/test.cpp
)

target_link_libraries(${TEST_TARGET} ${LOGGER_LIB})

target_include_directories(${TEST_TARGET} 
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/logger/
        ${PROJECT_SOURCE_DIR}/include/global/
)

add_custom_target(rebuild_logger
    COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR}

)

add_release_and_debug_options_to_target(${TEST_TARGET})
