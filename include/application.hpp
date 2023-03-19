#pragma once

#include <fstream>
#include <string>

#include "ui.hpp"
#include "sfml_ui.hpp"
#include "logic.hpp"

class Application {
 public:
  enum class ApplicationMode: int16_t {
    Console,
    Sfml
  };

  Application(const ApplicationMode& mode, const std::string& config_file);
  void Run();

 private:
  UI* ui_;
  Logic logic_;
};