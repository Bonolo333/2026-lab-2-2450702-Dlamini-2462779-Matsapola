# =========================== Specify Minimum Tool Versions ============================

cmake_minimum_required(VERSION 4.3.4)
project(elen3009-lab-2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    # Check the version of the MinGW compiler that CMake will use to build the project
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16.1.0")
            message(FATAL_ERROR "MinGW version 16.1.0 or higher is required on Windows.")
        endif()
    endif()
endif()

# ====================== Declare Variables ======================

set(SRC_PATH "${CMAKE_SOURCE_DIR}/src/text-query-system/code")
set(TESTS_PATH "${CMAKE_SOURCE_DIR}/src/text-query-system/tests")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # sets output directory for targets
get_filename_component(COMPILER_PATH "${CMAKE_CXX_COMPILER}" DIRECTORY) # extract compiler directory

# ====================== Select Files for Compilation ======================

# Shared implementation files are compiled into both targets.
# Keeping this list explicit makes it clear which production files are tested.
set(CORE_SOURCES
    "${SRC_PATH}/FileReader.cpp"
    "${SRC_PATH}/Line.cpp"
    "${SRC_PATH}/Paragraph.cpp"
    "${SRC_PATH}/Word.cpp"
)

# ====================== Download Dependencies ======================

include(FetchContent)

# Download doctest at a fixed commit for reproducible builds.
FetchContent_Declare(
    doctest
    # repository URL
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    # corresponds to doctest v2.4.12 - good practice to specify the commit hash as tags can be moved
    GIT_TAG "1da23a3e8119ec5cce4f9388e91b065e20bf06f5" )

# Make the dependency available and populate variables such as doctest_SOURCE_DIR.
FetchContent_MakeAvailable(doctest)

# ====================== Setup Targets ======================

# The application includes main.cpp. Doctest supplies the test executable's main function.
add_executable(TextQuery
    "${SRC_PATH}/main.cpp"
    ${CORE_SOURCES}
)

add_executable(TextQueryTests
    "${TESTS_PATH}/TextQueryTests.cpp"
    ${CORE_SOURCES}
)
target_include_directories(TextQueryTests PRIVATE
    "${SRC_PATH}"
    "${doctest_SOURCE_DIR}/doctest"
)

# ====================== Post-Build ======================

# ----- platform/compiler-specific post-build commands -------

# Function to copy MinGW runtime DLLs alongside the executables.
# This allows the program and tests on PCs which do not have MinGW installed.
function(copy_runtime_dlls TARGET)
    add_custom_command(
        TARGET "${TARGET}" POST_BUILD
            # copy MinGW DLLs from compiler's bin directory to output directory
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${COMPILER_PATH}/libstdc++-6.dll $<TARGET_FILE_DIR:${TARGET}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${COMPILER_PATH}/libgcc_s_seh-1.dll $<TARGET_FILE_DIR:${TARGET}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${COMPILER_PATH}/libwinpthread-1.dll $<TARGET_FILE_DIR:${TARGET}>
    )
endfunction()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND WIN32) # if the MinGW GCC compiler is used on windows copy the required DLLs
    copy_runtime_dlls(TextQuery)
    copy_runtime_dlls(TextQueryTests)
else()
    message("Unknown platform and compiler combination. Library dependencies not copied to output directory.")
endif()

# -------- platform/compiler-independent post-build commands ---------

# Executables assume that alice.txt is in the same directory.
add_custom_command(TARGET TextQuery POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SRC_PATH}/alice.txt" $<TARGET_FILE_DIR:TextQuery>
)

add_custom_command(TARGET TextQueryTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SRC_PATH}/alice.txt" $<TARGET_FILE_DIR:TextQueryTests>
)

# ====================== CTest ======================

include(CTest) # include otherwise Site is missing
enable_testing()
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
# automatically add doctest tests to CTest; specify WORKING_DIRECTORY to ensure that relative paths are correct for CTest
doctest_discover_tests(TextQueryTests WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
