#include "netflow.hpp"

#include "import_command.hpp"

#include <CLI/App.hpp>

void netflow::init(CLI::App &app) {
  auto &cmd = import_command::get();
  auto &cli = cmd.cli;
  // This can also be used if we don't need access to `cmd`:
  // auto cli = app.get_subcommand("import");
  cli->add_subcommand("netflow", "The import netflow command")->callback([&]() {
    cmd.run("netflow");
  });
}
