#include "../include/application.hpp"

Application::Application(const ApplicationMode& mode, const std::string& config_file) {
  std::ifstream config;
  config.open("../content/" + config_file);
  std::string source;
  config >> source;
  logic_.LoadObjects(source);
  if (mode == ApplicationMode::Sfml) {
    ui_ = new SfmlUI(logic_, Point(640, 480));
  }
  config.close();
}

void Application::Run() {
  sf::Clock clock;
  clock.restart();
  while (true) {
    if (clock.getElapsedTime() >= sf::milliseconds(1))
    {
      logic_.Run();
      if (!ui_->Run()) {
        break;
      }
      clock.restart();
    }
  }
}