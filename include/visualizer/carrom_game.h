//
// Created by Samyak Jain on 11/12/20.
//

#ifndef CARROM_GAME_CARROM_GAME_H
#define CARROM_GAME_CARROM_GAME_H

#include "cinder/gl/gl.h"
#include "core/striker.h"
#include "core/board.h"

class Game {
 public:
  /**
   * Updates the current state of the game
   */
  void Update();

  /**
   * Draws the current state of the game
   */
  void Draw() const;

  /**
   * Updates the location of the striker by appending the position vector with
   * the given vector
   * @param append how much you want to change the position of the
   *        striker by
   */
  void UpdateStrikerLocation(const glm::vec2 &append);

  /**
   * Updates the property of the strikers
   * @param degrees_increase the number of degrees that should be increased
   * @param vel_increase the magnitude of velocity that should be increased
   */
  void UpdateStrikerProperties(double degrees_increase, double vel_increase);

  /**
   * Creates a game with the following square dimension
   * @param bound_square_dim represents the length of one side of the square board
   * @param margin represents the margin between the window and the square board
   */
  Game(double bound_square_dim, double margin);

  /**
   * Launches the striker
   */
  void Launch();

  /**
   * represents the real life to game ratio: cm to pixels
   */
  static constexpr double kRealLifeToGameRatio = 10;
  static constexpr double kLowerBoundDiskVelocity_ = 0.1;

 private:
  Board board_;

  bool is_turn_in_progress_;
  bool has_user_launched_;

};

#endif //CARROM_GAME_CARROM_GAME_H