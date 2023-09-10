#include "../include/sfml_ui.hpp"

SfmlUI::SfmlUI(Logic& logic, Statistics& statistics, const Point& size)
    : UI(logic, statistics),
      is_pressed_(7),
      state_(AppState::InGame),
      grid_size_(size.x, size.x * logic_.GetGridSize().y / logic_.GetGridSize().x),
      grid_drawer_(logic, Point(0, 0), grid_size_),
      score_drawer_(statistics, Point(0, grid_size_.y), Point(size.x, size.y - grid_size_.y)),
      pause_drawer_(Point(0, 0), size),
      gameover_drawer_(statistics, Point(0, 0), size) {
  window_.create(sf::VideoMode(size.x, size.y), "Pacman");
}

UI::Signal SfmlUI::Run(const Logic::Event& logic_event) {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
      return Signal::WindowClosed;
    } else if (event.type == sf::Event::LostFocus) {
      if (state_ != AppState::Paused) {
        state_ = AppState::Paused;
        return Signal::Paused;
      }
    }
  }

  if (logic_event == Logic::Event::GameEnded) {
    state_ = AppState::GameOver;
  }

  Signal clicks_ret = CheckClicks();
  Draw();

  if (clicks_ret != Signal::Nothing) {
    return clicks_ret;
  }
  return Signal::Nothing;
}

void SfmlUI::Draw() {
  window_.clear();

  if (state_ == AppState::GameOver) {
    gameover_drawer_.Draw(window_);
  } else {
    grid_drawer_.Draw(window_, state_ == AppState::Paused);
    score_drawer_.Draw(window_);
    if (state_ == AppState::Paused) {
      pause_drawer_.Draw(window_);
    }
  }

  window_.display();
}

UI::Signal SfmlUI::CheckClicks() {
  if (state_ == AppState::GameOver) {
    if (IsKeyClicked(sf::Keyboard::R, 6)) {
      state_ = AppState::InGame;
      return Signal::NewGame;
    }
    return Signal::Nothing;
  }

  if (state_ == AppState::InGame) {
    if (IsKeyClicked(sf::Keyboard::Left, 0)) {
      logic_.SetPacmanDir(MovingObject::DirId::Left);
    }
    if (IsKeyClicked(sf::Keyboard::Right, 1)) {
      logic_.SetPacmanDir(MovingObject::DirId::Right);
    }
    if (IsKeyClicked(sf::Keyboard::Up, 2)) {
      logic_.SetPacmanDir(MovingObject::DirId::Up);
    }
    if (IsKeyClicked(sf::Keyboard::Down, 3)) {
      logic_.SetPacmanDir(MovingObject::DirId::Down);
    }
  }
  if (IsKeyClicked(sf::Keyboard::P, 4)) {
    if (state_ == AppState::Paused) {
      state_ = AppState::InGame;
    } else {
      state_ = AppState::Paused;
    }
    return Signal::Paused;
  }
  if (IsKeyClicked(sf::Keyboard::M, 5)) {
    return Signal::Muted;
  }
  return Signal::Nothing;
}

bool SfmlUI::IsKeyClicked(sf::Keyboard::Key key, uint32_t ind) {
  if (sf::Keyboard::isKeyPressed(key)) {
    if (!is_pressed_[ind]) {
      is_pressed_[ind] = true;
      return true;
    }
  } else {
    is_pressed_[ind] = false;
  }
  return false;
}