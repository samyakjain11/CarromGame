//
// Created by Samyak Jain on 11/21/20.
//

#ifndef CARROM_GAME_POCKET_H
#define CARROM_GAME_POCKET_H

#include "cinder/gl/gl.h"
#include "core/disk.h"

class Pocket {
 public:
  /**
   * Creates a Pocket at the given location with the specified radius
   * @param center represents the coordinate at which the center of the pocket
   *        lies
   * @param radius represents the radius of the circle that represents the
   *        pocket
   */
  Pocket(glm::vec2 center, double radius);

  /**
   * determines whether a certain disk is inside the pocket
   * @param disk the disk which you are checking for
   * @return true, if the disk is inside the pocket, false otherwise
   */
  bool IsDiskInsidePocket(const disk::Disk &disk);

  glm::vec2 GetCenter() const;
  double GetRadius() const;

  static constexpr double kRealLifePocketRadius_ = 2.22;

 private:
  glm::vec2 center_;
  double radius_;
};
#endif //CARROM_GAME_POCKET_H
