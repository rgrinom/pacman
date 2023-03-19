#include "../include/statistics.hpp"

void Statistics::Load(const std::string& config_file, int32_t coins_cnt) {
  std::ifstream config;
  config.open("../content/" + config_file);
  config >> init_lives_ >> coin_score_ >> bonus_score_;
  init_coins_cnt_ = coins_cnt;
  Reset();
  config.close();
}

void Statistics::DecreaseLives() { --lives_; }
void Statistics::AddCoinScore() {
  score_ += coin_score_;
  --coins_cnt_;
}
void Statistics::AddBonusScore() { score_ += bonus_score_; }

bool Statistics::IsAlive() { return lives_ > 0; }
bool Statistics::HasWon() { return coins_cnt_ == 0; }
int32_t Statistics::GetLives() { return lives_; }
int32_t Statistics::GetScore() { return score_; }

void Statistics::Reset() {
  lives_ = init_lives_;
  score_ = 0;
  coins_cnt_ = init_coins_cnt_;
}