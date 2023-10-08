#include "../include/statistics.hpp"

void Statistics::Load(const std::string& config_file, int32_t coins_cnt) {
  std::ifstream config;
  config.open("../content/configs/" + config_file);
  config >> init_lives_ >> coin_score_ >> bonus_score_ >> ghost_score_;
  init_coins_cnt_ = coins_cnt;
  HardReset();
  config.close();
}

void Statistics::DecreaseLives() { --lives_; }
void Statistics::AddCoinScore() {
  score_ += coin_score_;
  --coins_cnt_;
}
void Statistics::AddBonusScore() { score_ += bonus_score_; }
void Statistics::AddGhostScore() { score_ += ghost_score_; }
void Statistics::NextLevel() { ++level_; }

bool Statistics::IsAlive() { return lives_ > 0; }
bool Statistics::IsLevelBeaten() { return coins_cnt_ == 0; }
int32_t Statistics::GetLives() { return lives_; }
int32_t Statistics::GetScore() { return score_; }
int32_t Statistics::GetLevel() { return level_; }

void Statistics::SoftReset() {
  coins_cnt_ = init_coins_cnt_;
}

void Statistics::HardReset() {
  lives_ = init_lives_;
  score_ = 0;
  coins_cnt_ = init_coins_cnt_;
  level_ = 1;
}