//
// Created by Samyak Jain on 11/21/20.
//

#include "core/pocket.h"
#include "visualizer/carrom_game.h"

Pocket::Pocket(glm::vec2 center, double radius) {
  center_ = center;
  radius_ = radius;
}

double Pocket::GetRadius() const {
  return radius_;
}

glm::vec2 Pocket::GetCenter() const {
  return center_;
}

bool Pocket::IsDiskInsidePocket(const disk::Disk &disk) {
  if (glm::distance(disk.GetPosition(), center_) <= radius_)
    return true;
  return false;
}
