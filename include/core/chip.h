//
// Created by Samyak Jain on 11/20/20.
//

#ifndef CARROM_GAME_CHIP_H
#define CARROM_GAME_CHIP_H

#include "core/disk.h"
#include "cinder/gl/gl.h"

namespace point_values {
static const int kWhiteValue = 20;
static const int kBlackValue = 10;
static const int kQueenValue = 50;
}

class Chip: public disk::Disk {
 public:
  Chip(glm::vec2 position, int point_value);
  static constexpr double kChipRealLifeRadius_ = 1.5;

 private:
  static constexpr int kChipRealLifeMass_ = 5;

};


#endif //CARROM_GAME_CHIP_H
