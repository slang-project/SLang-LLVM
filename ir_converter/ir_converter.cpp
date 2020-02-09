#include "ir_converter.hpp"

#include "llvm/IR/IRBuilder.h"

#include <string>

using namespace SLang::CodeGenerator;

using namespace llvm;
using namespace std;

static LLVMContext context;

unique_ptr<Ir::LlvmIr> Ir::Convert(const SLangIr &program) noexcept
{
    if (!program.is_object())
    {
        // TODO: message on wrong actual type of module (object expected).
        return nullptr;
    }

    static const auto module_name_key = "name"s; // TODO: `L"name"s`.
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
    const auto &module_name = j_module_name.get_ref<const string&>(); // TODO: `std::wstring`.

    // TODO: remove `std::` when LLVM will move to C++14 and remove `llvm::make_unique`.
    auto module_opt = std::make_unique<Module>(module_name, context);
    auto &module = *module_opt;

    // module.setSourceFileName(file_name); // TODO: set source file name.

    // TODO: convert module.

    return module_opt;
}
