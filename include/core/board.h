//
// Created by Samyak Jain on 11/20/20.
//

#ifndef CARROM_GAME_BOARD_H
#define CARROM_GAME_BOARD_H
#include "core/disk.h"
#include "cinder/gl/gl.h"
#include "core/striker.h"
#include "core/pocket.h"
#include "chip.h"


class Board {
 public:
  /**
   * Updates all the different components on the board
   */
  void UpdateBoard();

  /**
   * Draws all the different components on the board
   */
  void DrawBoard() const;

  /**
   * Creates a board with the following dimensions
   * @param top_left_corner represents the top left coordinate of the board
   * @param board_dimension represents the boards size, the length of one side
   */
  Board(glm::vec2 top_left_corner, double board_dimension);

  /**
   * default constructor
   */
  Board() = default;

  /**
   * Determines if the chips that are on the board are moving
   * @return
   */
  bool AreChipsMoving();

  Striker striker_;

  /**
   * represents the friction coefficient
   */
  static constexpr double kFrictionCoefficient = 0.96;

  /**
   * TESTING PURPOSES ONLY
   * spawns a chip on top of the top left pocket
   * @param ind index of pockets you want to spawn a chip
   * @param p_val the point value of the chip you want to spawn
   */
  void CheatCode(int ind, int p_val);

  /**
   * TESTING PURPOSES ONLY
   * @param chip the chip you want to add to the board
   */
  void AddChip(Chip *chip);

  /**
   * TESTING PURPOSES ONLY
   * returns the disk at a specific index
   * @param index
   * @return a disk
   */
  disk::Disk GetDisk(int index);

  /**
   * TESTING PURPOSES ONLY
   * @return returns the score of the user
   */
  int GetScore() const;

  /**
    * Generates pockets given the top left and bottom right corner of a board
    * @param top_left_corner the top left coordinate of the board
    * @param bottom_right_corner the bottom right coordinate of the board
    * @return returns a vector that contains 4 pockets for each of the corners:
    *         1. top left
    *         2. top right
    *         3. bottom left
    *         4. bottom right
    */
  std::vector<Pocket>
  GeneratePockets(glm::vec2 top_left_corner, glm::vec2 bottom_right_corner);


 private:
  std::vector<disk::Disk> disks_;
  glm::vec2 top_left_corner_;

  static constexpr float kGuideLineMultiplier_ = 5;

  // rbg values for board color: light brown
  static constexpr int kBoardColorR_ = 255;
  static constexpr int kBoardColorG_ = 218;
  static constexpr int kBoardColorB_ = 173;

  static constexpr float kXCenterScoreText_ = 725;

  static constexpr double kCenterCircleRealLifeRadius_ = 6;

  int score_;

  /**
   * Draws the disks that exist on the board
   */
  void DrawDisks() const;

  /**
   * Draws the design that is on the board
   */
  void DrawBoardDesign() const;

  /**
   * Draws the striker on the board as well as a guideline which indicates where
   * the user is going to shoot the striker
   */
  void DrawStriker() const;

  /**
   * Draws the score that the user has achieved
   */
  void DrawScore() const;

  /**
   * Updates the striker
   */
  void UpdateStriker();

  /**
   * Updates the disks
   */
  void UpdateDisks();

  /**
   * Detects disk to disk collisions and changes velocities of disks on the
   * board accordingly
   */
  void DetectDiskCollisions();

  /**
   * Detects collisions between the striker and other disks and changes
   * velocities of disks as necessary
   */
  void DetectStrikerToDiskCollisions();

  /**
   * Detects if any disks (including the striker) was pocketed and updates the
   * score as well as the board accordingly
   */
  void DetectPocketedDisks();

  /**
   * represents the rectangle that the board is drawn upon
   */
  ci::Rectf board_rectangle_;

  /**
   * represents a vector of Pockets that are on the board: always size 4
   */
  std::vector<Pocket> pockets_;

  static constexpr double kBlackCenteringCoefficient_ = 2.5;
  static constexpr double kWhiteCenteringCoefficient_ = 2;
};

#endif //CARROM_GAME_BOARD_H
