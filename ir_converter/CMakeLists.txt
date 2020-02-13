cmake_minimum_required(VERSION 3.12)

add_library(ir_converter ir_converter.cpp)
target_include_directories(ir_converter PRIVATE ${SLANG_LLVM_CURRENT_SOURCE_DIR})

llvm_map_components_to_libnames(llvm_libs support core)

target_link_libraries(ir_converter PUBLIC ${llvm_libs} nlohmann_json::nlohmann_json)
