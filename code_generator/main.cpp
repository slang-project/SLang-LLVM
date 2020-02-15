﻿#include "code_generator_driver/code_generator_driver.hpp"

#include <cstdlib>

using namespace SLang::CodeGenerator;

using namespace std;

/**
 * \brief Convert c-style arguments of \c main into modern C++ structures.
 * \param argv Pointer to array of c-style strings of arguments (like <tt>main</tt>'s \c argv).
 * \param argc Size of the array \c argv (like <tt>main</tt>'s \c argc).
 * \return \c std::vector of \c std::string_view pointing to values pointed by elements of \p argv.
 * \pre \p argv is pointer to contiguous memory block containing \p argc number of elements.
 * \pre Each element pointed by elements of \p argv is null-terminated c-style string.
 * \note The order of parameters was changed due to possible usage of \c std::span.
 */
static auto ArgsToVector(const char *const *const argv, const int argc) noexcept
// TODO: use `const std::span<const char *> &` instead of `argv` and `argc` in C++20.
{
    vector<string_view> result;
    result.reserve(argc);

    // TODO: use range-based for loop
    for (auto i = static_cast<decltype(argc)>(0); i < argc; ++i)
    {
        result.emplace_back(argv[i]);
    }

    return result;
}

int main(const int argc, const char *const *const argv) noexcept
{
    /// Turn off synchronization with C standard streams.
    ios_base::sync_with_stdio(false);

    if (const auto args = CommandLineArgs::Parse(ArgsToVector(argv, argc)); args.has_value())
    {
        return Driver::Main(*args) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}
