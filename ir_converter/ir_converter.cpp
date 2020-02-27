#include "ir_converter.hpp"

#include "llvm/IR/IRBuilder.h"

#include <string>

using namespace SLang::CodeGenerator;

using namespace llvm;
using namespace std;

static LLVMContext context;

template <class JsonAdapter>
unique_ptr<const Module> ConvertToLlvmModule(JsonManager<JsonAdapter>& source) noexcept
{
    if (!source_.IsObject())
    {
        // TODO: message on wrong actual type of module (object expected).
        return nullptr;
    }

    static const auto module_name_key = u8"name"s;
    string_view module_name; // TODO: \c std::u8string_view.
    /// Extract field "name" to \c module_name.
    {
        const auto j_module_name_it = source_.FindMember(module_name_key);
        if (j_module_name_it == source_.MemberEnd())
        {
            // TODO: message on absence of the field "name" in module.
            return nullptr;
        }
        const auto &j_module_name = j_module_name_it->value;
        if (!j_module_name.IsString())
        {
            // TODO: message on "name" attribute not being string.
            return nullptr;
        }
        module_name = j_module_name.GetString();
    }

    auto module_ptr = std::make_unique<Module>(module_name.data(), context);
    auto &module = *module_ptr;

    // TODO: set source file name.
    //module.setSourceFileName(file_name);

    // TODO: convert module.
    return nullptr;
    //return module_ptr;
}
