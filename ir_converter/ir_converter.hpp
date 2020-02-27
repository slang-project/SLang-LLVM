#ifndef IR_CONVERTER_HPP
#define IR_CONVERTER_HPP

#include "llvm/IR/Module.h"

#define RAPIDJSON_HAS_STDSTRING 1
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#undef RAPIDJSON_HAS_STDSTRING

#include <istream>
#include <memory>
#include <optional>
#include <ostream>

namespace SLang::CodeGenerator
{
    // TODO: document!
    class RapidJsonAdapter
    {
        // TODO: document!
        RapidJsonAdapter() noexcept
        {
        }

    public:
        // TODO: document!
        [[nodiscard]] static std::optional<RapidJsonAdapter> Parse(rapidjson::IStreamWrapper is) noexcept
        {
            using namespace rapidjson;

            RapidJsonAdapter result;

            {
                // TODO: detect encoding? Then ensure \c is to be byte input.
                /// For reading encoded files (assuming UTF-8).
                EncodedInputStream<UTF8<>, IStreamWrapper> eis(move(is));

                if (result.doc_.ParseStream(eis).HasParseError())
                {
                    // TODO: message (not to \c std::cout) on invalid JSON.
                    return std::nullopt;
                }
            }

            return result;
        }

    private:
        rapidjson::Document doc_;
    };

    /**
     * \brief Provides access, logging and error handling over JSON implementation.
     * \tparam JsonAdapter Class providing an interface of JSON reader.
     */
    template <class JsonAdapter>
    class JsonManager
    {
        // TODO: document!
        JsonManager(
            JsonAdapter &&adapter,
            std::wostream &outs,
            std::wostream &errs,
            std::wostream &logs
        ) :
            adapter_(std::forward(adapter)),
            outs_(outs),
            errs_(errs),
            logs_(logs)
        {
        }

    public:
        // TODO: document!
        [[nothrow]] static std::optional<JsonManager> Parse(
            std::istream &is,
            std::wostream &outs,
            std::wostream &errs,
            std::wostream &logs) noexcept
        {
            std::optional<JsonAdapter> adapter_opt = JsonAdapter::Parse(is);
            if (!adapter_opt)
            {
                // TODO: log parse error.
                return std::nullopt;
            }
            return JsonManager(move(*adapter_opt));
        }

    private:
        JsonAdapter adapter_;
        std::wostream &outs_, &errs_, &logs_;
    };

    /**
     * \brief Convert program represented by SLang IR into LLVM IR Module.
     * \tparam JsonAdapter Class providing an interface of JSON reader.
     * \param source JSON document containing SLang IR wrapped into \c JsonManager.
     * \return \c nullptr - conversion failed; LLVM IR Module with program - otherwise.
     */
    template <class JsonAdapter>
    [[nodiscard]] std::unique_ptr<const llvm::Module> ConvertToLlvmModule(JsonManager<JsonAdapter> &source) noexcept
    {
        return ConvertCompilation(source);
    }
}

#endif
