cmake_minimum_required(VERSION 3.12)

add_library(command_line_args command_line_args.cpp)
target_include_directories(command_line_args PRIVATE ${SLANG_LLVM_CURRENT_SOURCE_DIR})
