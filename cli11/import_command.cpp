#include "import_command.hpp"

#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

import_command &import_command::get() {
  static import_command x;
  return x;
}

CLI::App_p import_command::make() {
  auto &cmd = get();
  auto& cli = cmd.cli;
  cli = std::make_shared<CLI::App>("The import command", "import");
  cli->require_subcommand();
  cli->add_option("-s,--schema-file", cmd.custom, "File name");
  CLI::App *import_json =
      cli->add_subcommand("json", "The import JSON command")->callback([&]() {
        cmd.run("json");
      });
  import_json->add_option("-s,--schema-file", cmd.custom, "File name");
  CLI::App *import_zeek =
      cli->add_subcommand("zeek", "The import ZEEK command")->callback([&]() {
        cmd.run("zeek");
      });
  return cli;
}

void import_command::run(std::string_view format) {
  std::cout << "Running the import " << format << "\n";
  std::cout << "Working on --custom from start: " << custom.i << std::endl;
}
