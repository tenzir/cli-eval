#include "add_command.hpp"
#include "matcher_command.hpp"

#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

matcher_command &matcher_command::get() {
  static matcher_command x;
  return x;
}

CLI::App_p matcher_command::make() {
  auto &cmd = get();
  auto &cli = cmd.cli;
  cli = std::make_shared<CLI::App>("The matcher command", "matcher");
  std::make_shared<CLI::App>("matcher");
  cli->require_subcommand();
  cli->add_option("-s,--schema-file", cmd.custom, "File name");
  CLI::App *matcher_json =
      cli->add_subcommand("json", "The matcher JSON command")->callback([&]() {
        cmd.run("json");
      });
  matcher_json->add_option("-s,--schema-file", cmd.custom, "File name");
  CLI::App *matcher_zeek =
      cli->add_subcommand("zeek", "The matcher ZEEK command")->callback([&]() {
        cmd.run("zeek");
      });
  return cli;
}

void matcher_command::run(std::string_view format) {
  std::cout << "Running the matcher " << format << "\n";
  std::cout << "Working on --custom from start: " << custom.i << std::endl;
}

void matcher_command::init(CLI::App& app) {
  add_command<matcher_command>(app);
}

