//
// Created by Samyak Jain on 11/13/20.
//

#ifndef CARROM_GAME_STRIKER_H
#define CARROM_GAME_STRIKER_H

#include "cinder/gl/gl.h"
#include "core/disk.h"

class Striker: public disk::Disk {
 public:
  /**
   * Creates a striker at the default position with no velocity
   */
  Striker();

  /**
   * Updates the property of the strikers
   * @param degrees_increase the number of degrees that should be increased
   * @param vel_increase the magnitude of velocity that should be increased
   */
  void UpdateStrikerProperties(double degrees_increase, double vel_increase);

  /**
   * Updates the location of the striker by appending the position vector with
   * the given vector
   * @param append_location how much you want to change the position of the
   *        striker by
   */
  void UpdateLocation(const glm::vec2 &append_location);

  /**
   * resets the striker to its default position and sets velocity back to 0
   */
  void ResetStriker();

  /**
   * FOR TESTING PURPOSES ONLY
   * @return returns the degree at which the striker is launched
   */
  double GetDegrees() const;

 private:
  double degrees_;

  static constexpr int kVelocityCap_ = 40;
  static constexpr int kStrikerPointVal_ = -10;
  static constexpr int kStrikerDefaultDegrees_ = 270;

  static constexpr int kStrikerMass_ = 15;
  static constexpr int kStrikerRealLifeRadius_ = 2;

  static constexpr float kXDefaultPosition_ = 350;
  static constexpr float kYDefaultPosition_ = 550;
};

#endif //CARROM_GAME_STRIKER_H