#pragma once

#include "custom.hpp"

#include <memory>
#include <sstream>

namespace CLI {

class App;

using App_p = std::shared_ptr<App>;

}

struct import_command {
    CLI::App_p cli;
    custom_t custom = {42};

    import_command() = default;

    import_command(const import_command&) = delete;
    import_command(import_command&&) = delete;

    import_command& operator=(const import_command&) = delete;
    import_command& operator=(import_command&&) = delete;

    void run(std::string_view format);

    static CLI::App_p make();

    static import_command& get();
};
