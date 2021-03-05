#pragma once

#include "custom.hpp"

#include <memory>
#include <string_view>

namespace CLI {

class App;

using App_p = std::shared_ptr<App>;

}

struct matcher_command {
    CLI::App_p cli;
    custom_t custom = {42};

    matcher_command() = default;

    matcher_command(const matcher_command&) = delete;
    matcher_command(matcher_command&&) = delete;

    matcher_command& operator=(const matcher_command&) = delete;
    matcher_command& operator=(matcher_command&&) = delete;

    void run(std::string_view format);

    static CLI::App_p make();

    static matcher_command& get();

    static void init(CLI::App& app);
};
