//
// Created by Samyak Jain on 11/13/20.
//
#include "core/striker.h"
#include "cinder/gl/gl.h"
#include "visualizer/carrom_game.h"

Striker::Striker() {
  point_value_ = kStrikerPointVal_;
  radius_ = kStrikerRealLifeRadius_ * Game::kRealLifeToGameRatio;
  mass_ = kStrikerMass_;
  color_ = "yellow";

  velocity_ = glm::vec2(0, 0);
  position_ = glm::vec2(kXDefaultPosition_, kYDefaultPosition_);
  degrees_ = kStrikerDefaultDegrees_;
}

void
Striker::UpdateStrikerProperties(double degrees_increase, double vel_increase) {
  double vel_mag = glm::length(velocity_);

  if (vel_mag < kVelocityCap_ || vel_increase < 0)
    vel_mag += vel_increase;

  if ((vel_increase < 0 && vel_mag > 0) || (vel_increase >= 0)) {
    double adjusted_rads = (degrees_increase + degrees_) * M_PI / 180.0;
    velocity_.x = vel_mag * cos(adjusted_rads);
    velocity_.y = vel_mag * sin(adjusted_rads);
    degrees_ += degrees_increase;
  }
}

void Striker::UpdateLocation(const glm::vec2 &location) {
  position_ += location;
}

void Striker::ResetStriker() {
  position_ = {kXDefaultPosition_, kYDefaultPosition_};
  velocity_ = {0, 0};
  degrees_ = kStrikerDefaultDegrees_;
}

double Striker::GetDegrees() const {
  return degrees_;
}