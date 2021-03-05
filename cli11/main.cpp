// SPDX-License-Identifier: BSD-3-Clause

#include "add_command.hpp"
#include "import_command.hpp"
#include "matcher_command.hpp"
#include "netflow.hpp"

#include <CLI/CLI.hpp>
#include <fmt/format.h>
//#include <spdlog/spdlog.h>

#include <iostream>

class MyFormatter : public CLI::Formatter {
public:
  MyFormatter() : Formatter() {}
  std::string make_option_opts(const CLI::Option * opt) const override {
    const auto& dflt = opt->get_default_str();
    if (dflt.empty())
      return "";
    return fmt::format(" <{}>", opt->get_default_str());
  }
};

bool enable_matcher(const std::string &) { return true; }

int main(int argc, char **argv) {
  CLI::App app("VAST Cli11 Demo");

  auto fmt = std::make_shared<MyFormatter>();
  app.formatter(fmt);

  std::string config = "vast.yaml";
  auto cfg = app.add_option("-c,--config", config, "path of the config file");
  cfg->capture_default_str();
  //cfg->default_val("vast.yaml");

  // We call parse twice: once after the options on the root command are
  // specified to get the config file parameter, and later when the full
  // command line parser is defined to actually run the app.
  app.set_help_flag("", "");
  app.allow_extras();
  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }
  app.allow_extras(false);
  app.set_help_flag("-h,-?,--help", "Print this help message and exit");

  std::cout << "Using config file: " << config << '\n';

  // Here we parse the config file.

  app.set_help_all_flag("--help-all", "Expand all help");

  // Does not list the availabe subcommands by default.
  app.require_subcommand();

  add_command<import_command>(app);

  // This is missing some indirection to be realistic, but the fundamental idea
  // should be possible with dlopen as well.
  if (enable_matcher(config))
    matcher_command::init(app);
  // Hooks into the import command
  netflow::init(app);

  try {
    app.parse(argc, argv);
  } catch (const CLI::RequiredError &e) {
    // Attempt to list the available subcommands. Doesn't work if only the root
    // command was called.
    for (auto &sub : app.get_subcommands()) {
      std::cout << sub->help("", CLI::AppFormatMode::Sub);
    }
    return app.exit(e);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  return 0;
}
