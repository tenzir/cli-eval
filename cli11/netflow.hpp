#pragma once

#include <memory>

namespace CLI {

class App;

using App_p = std::shared_ptr<App>;

}

struct netflow {
  static void init(CLI::App& app);
};
