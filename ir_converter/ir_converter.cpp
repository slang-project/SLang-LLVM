#include "ir_converter.hpp"

#include "llvm/IR/IRBuilder.h"

#include <string>

using namespace SLang::CodeGenerator;

using namespace llvm;
using namespace std;

static LLVMContext context;

unique_ptr<const Ir::LlvmIr> Ir::Convert(const SLangIr &program) noexcept
{
    if (!program.is_object())
    {
        // TODO: message on wrong actual type of module (object expected).
        return nullptr;
    }

    // Extract field "name" to `module_name`.
    static const auto module_name_key = u8"name"s;
    const auto j_module_name_it = program.find(module_name_key);
    if (j_module_name_it == program.end())
    {
        // TODO: message on absence of the field "name" in module.
        return nullptr;
    }
    const auto &j_module_name = *j_module_name_it;
    if (!j_module_name.is_string())
    {
        // TODO: message on "name" attribute not being string.
        return nullptr;
    }
    const auto &module_name = j_module_name.get_ref<const string&>(); // TODO: `std::u8string`.

    auto module_ptr = std::make_unique<Module>(module_name, context);
    auto &module = *module_ptr;

    // module.setSourceFileName(file_name); // TODO: set source file name.

    // TODO: convert module.
    return nullptr;
    //return module_ptr;
}
