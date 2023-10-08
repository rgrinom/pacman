#include "../include/application.hpp"

Application::Application(const ApplicationMode& mode, const std::string& config_file)
  : logic_(statistics_),
    state_(AppState::InGame) {
  std::ifstream config;
  config.open("../content/configs/" + config_file);
  std::string source;
  config >> source;
  logic_.LoadObjects(source);

  if (mode == ApplicationMode::Sfml) {
    ui_ = new SfmlUI(logic_, statistics_, Point(600, 800));
    sounds_ = new SfmlSounds();
  }
  config.close();
}

Application::~Application() {
  delete ui_;
  delete sounds_;
}

void Application::Run() {
  sf::Clock clock;
  clock.restart();
  bool new_game = true;
  while (true) {
    if (clock.getElapsedTime() >= sf::milliseconds(1))
    {
      Logic::Event logic_ret = Logic::Event::Nothing;

      if (state_ == AppState::InGame) {
         logic_ret = logic_.Run();
         if (logic_ret == Logic::Event::GameEnded) {
          state_ = AppState::GameOver;
         }
      }

      UI::Signal ui_ret = ui_->Run(logic_ret);
      switch (ui_ret) {
        case UI::Signal::Paused:
          if (state_ == AppState::Paused) {
            state_ = AppState::InGame;
          } else {
            state_ = AppState::Paused;
          }
          break;
        case UI::Signal::Muted:
          sounds_->Mute();
          break;
        case UI::Signal::NewGame:
          logic_.Reset();
          ui_->Run(Logic::Event::Nothing);
          new_game = true;
          state_ = AppState::InGame;
          break;
        default:
          break;
      }
      if (ui_ret == UI::Signal::WindowClosed) {
        break;
      }

      if (state_ == AppState::InGame) {
        if (new_game) {
          sounds_->Run(Logic::Event::LevelStarted);
          new_game = false;
        }
        sounds_->Run(logic_ret);
      }

      clock.restart();
    }
  }
}