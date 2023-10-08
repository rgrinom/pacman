#pragma once

#include <cstdint>

enum class AppState: int16_t {
  InGame,
  Paused,
  GameOver
};