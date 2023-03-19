#pragma once

#include <cstdint>
#include <fstream>
#include <string>

class Statistics {
 public:
  Statistics() = default;
  void Load(const std::string& config_file, int32_t coins_cnt);
  void DecreaseLives();
  void AddCoinScore();
  void AddBonusScore();
  bool IsAlive();
  bool HasWon();
  int32_t GetLives();
  int32_t GetScore();
  void Reset();

 private:
  int32_t init_lives_;
  int32_t lives_;
  int32_t score_;

  int32_t coin_score_;
  int32_t bonus_score_;

  int32_t init_coins_cnt_;
  int32_t coins_cnt_;
};