//
// Created by Samyak Jain on 11/13/20.
//

#ifndef CARROM_GAME_DISK_H
#define CARROM_GAME_DISK_H

#include "cinder/gl/gl.h"

namespace disk {

class Disk {
 protected:
  glm::vec2 position_;
  glm::vec2 velocity_;

  double mass_;
  double radius_;
  int point_value_;
  std::string color_;

 public:
  glm::vec2 GetVelocity() const;
  glm::vec2 GetPosition() const;
  double GetRadius() const;
  double GetMass() const;
  std::string GetColor() const;
  double GetPointValue() const;
  void SetVelocity(glm::vec2 new_vel);

  /**
   * Updates the velocity of the disk by accounting for friction
   */
  void UpdateVelocity();

  /**
   * Updates the position of the disk by accounting for velocity
   */
  void UpdatePosition();

  /**
   * Checks to see if there are any collisions on the basis of the bounds given
   * @param x_left_bound the minimum x value of the square
   * @param x_right_bound the maximum x value of the square
   * @param y_upper_bound the maximum y value of the square
   * @param y_lower_bound the minimum y value of the square
   */
  void HandleAxesCollisions(glm::vec2 top_left_corner,
                            glm::vec2 bottom_right_corner);

 private:
  /**
 * changes velocity of this particle according to a vertical collision
 */
  void VerticleCollision();

  /**
   * changes velocity of this particle according to a horizontal collision
   */
  void HorizontalCollision();

  /**
   * checks if the particle has collided with the ceiling or the floor
   * @param y_lower_bound the minimum y value
   * @param y_upper_bound the maximum y value
   * @return true if the particle has collided with a vertical bound, else false
   */
  bool IsVerticleCollision(double y_lower_bound, double y_upper_bound);

  /**
  * checks if the particle has collided with the left wall or the right wall
  * @param x_left_bound the minimum x value
  * @param x_right_bound the maximum x value
  * @return true if the particle has collided with a horizontal bound, else
   * false
  */
  bool IsHorizontalCollision(double x_left_bound, double x_right_bound);
};
/**
 * Detects if there is a collision between 2 disks
 * @param first the first disk
 * @param second the second disk
 * @return true, if the disks collide, false otherwise
 */
bool IsCollision(const Disk &first, const Disk &second);

/**
 * Changes velocities of disks as necessary to account for a collision happening
 * using physics formulas and math
 * @param first the first disk
 * @param second the second disk
 */
void Collision(Disk &first, Disk &second);

} // end namespace disk

#endif //CARROM_GAME_DISK_H