# CMakeLists.txt for compiling llama.cpp strictly for 32-bit ARMv7a (armeabi-v7a) on Android 11
cmake_minimum_required(VERSION 3.22.1)

project("offlineai" C CXX)

# Enforce C++17 standard for modern llama.cpp/ggml compatibility
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# Enforce strict 32-bit ARMv7-a architecture
if(NOT ANDROID_ABI STREQUAL "armeabi-v7a")
    message(FATAL_ERROR "Architecture ${ANDROID_ABI} is not supported! This build is strictly locked to 32-bit armeabi-v7a.")
endif()

# Compiler flags optimized for 32-bit ARMv7-a (NEON + VFPv4 vectorization, strict 32-bit limits)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG -march=armv7-a -mfpu=neon-vfpv4 -mfloat-abi=softfp -mthumb -fPIC -fPIE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -march=armv7-a -mfpu=neon-vfpv4 -mfloat-abi=softfp -mthumb -fPIC -fPIE -fexceptions -frtti")

# Definition flags for llama.cpp / ggml
add_definitions(-DGGML_USE_CPU=1)
add_definitions(-D_GNU_SOURCE=1)
add_definitions(-D__ARM_NEON=1)
add_definitions(-D__ARM_ARCH_7A__=1)

# Locate Android logging library
find_library(log-lib log)
find_library(android-lib android)

# Source files for llama.cpp native bridge
# When full llama.cpp sources (ggml.c, llama.cpp, etc.) are present in src/main/cpp,
# they are automatically compiled into the shared library.
file(GLOB_RECURSE LLAMA_SOURCES
    native-lib.cpp
    llama.cpp
    ggml.c
    ggml-alloc.c
    ggml-backend.c
    ggml-cpu.c
    ggml-quants.c
    unicode.cpp
    unicode-data.cpp
)

# Filter out non-existent files if partial source tree is used
if(NOT LLAMA_SOURCES)
    set(LLAMA_SOURCES native-lib.cpp)
endif()

# Build the shared native library for 32-bit Android
add_library(
    offlineai
    SHARED
    ${LLAMA_SOURCES}
)

# Header include paths
target_include_directories(
    offlineai
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link essential Android libraries
target_link_libraries(
    offlineai
    ${log-lib}
    ${android-lib}
)
