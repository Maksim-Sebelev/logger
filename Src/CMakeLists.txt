cmake_minimum_required(VERSION 3.27)

project(logger
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(INC_DIR include)


set(LOGGER_INC_DIR ${PROJECT_SOURCE_DIR}/include/logger)
set(LOGGER_SRC_DIR ${PROJECT_SOURCE_DIR}/src/logger    )

add_executable(log++_test
    ${PROJECT_SOURCE_DIR}/../tests/test.cpp
    ${LOGGER_SRC_DIR}/log++.cpp
)

target_include_directories(log++_test 
    PRIVATE
        ${LOGGER_INC_DIR}/
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
        # -Wpedantic
        # -g -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall
        # -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported
        # -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations
        # -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op
        # -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith
        # -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral
        # -fstrict-overflow -fno-omit-frame-pointer -Wstack-usage=8192
        # -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel
        # -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types
        # -Wsuggest-override -Wsync-nand -Wundef -Wunreachable-code -Wunused
        # -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing
        # -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector
        # -pie -fPIE -Werror=vla
        # -flto-odr-type-merging
        -Weffc++
        # -Wswitch-default
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
