//
// Created by Samyak Jain on 11/20/20.
//

#include "core/chip.h"
#include "visualizer/carrom_game.h"

Chip::Chip(glm::vec2 position, int point_value) {
  // call constructor for disk class

  position_ = position;
  velocity_ = glm::vec2(0, 0);

  mass_ = kChipRealLifeMass_;
  radius_ = kChipRealLifeRadius_ * Game::kRealLifeToGameRatio;
  point_value_ = point_value;

  if (point_value_ == point_values::kBlackValue)
    color_ = "black";
  else if (point_value_ == point_values::kWhiteValue)
    color_ = "white";
  else if (point_value_ == point_values::kQueenValue)
    color_ = "red";
}