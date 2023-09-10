#pragma once

#include <fstream>
#include <string>

#include "ui.hpp"
#include "sfml_ui.hpp"
#include "logic.hpp"
#include "statistics.hpp"
#include "sounds.hpp"
#include "sfml_sounds.hpp"
#include "app_state.hpp"

class Application {
 public:
  enum class ApplicationMode: int16_t {
    Console,
    Sfml
  };

  Application(const ApplicationMode& mode, const std::string& config_file);
  Application(const Application& app) = delete;
  ~Application();
  
  void Run();

 private:
  UI* ui_;
  Sounds* sounds_;
  Logic logic_;
  Statistics statistics_;
  AppState state_;
};