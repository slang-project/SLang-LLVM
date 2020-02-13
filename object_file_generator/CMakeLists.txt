cmake_minimum_required(VERSION 3.12)

add_library(object_file_generator object_file_generator.cpp)
target_include_directories(object_file_generator PRIVATE ${SLANG_LLVM_CURRENT_SOURCE_DIR})

# llvm_map_components_to_libnames(llvm_libs support core irreader)

# target_link_libraries(object_file_generator ${llvm_libs})
