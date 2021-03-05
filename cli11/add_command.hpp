#pragma once

#include <CLI/CLI.hpp>

template <class T> void add_command(CLI::App &app) {
  app.add_subcommand(T::make());
}
