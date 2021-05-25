//
// Created by Samyak Jain on 11/12/20.
//
#include "visualizer/carrom_game.h"

void Game::UpdateStrikerLocation(const glm::vec2 &append) {
  if (!is_turn_in_progress_)
    board_.striker_.UpdateLocation(append);
}

void Game::UpdateStrikerProperties(double degrees_increase,
                                   double vel_increase) {
  if (!is_turn_in_progress_)
    board_.striker_.UpdateStrikerProperties(degrees_increase, vel_increase);
}

Game::Game(double bound_square_dim, double margin) {
  board_ = Board(glm::vec2(50, 50), 600);
}

void Game::Draw() const {
  board_.DrawBoard();
}

void Game::Update() {
  /*
   * when will turn be in progress:
   *  case 1: if the chips are moving
   *  case 2: striker has some velocity AND striker has been launched
   */
  is_turn_in_progress_ = (board_.AreChipsMoving() ||
      (glm::length(board_.striker_.GetVelocity()) > kLowerBoundDiskVelocity_
          && has_user_launched_));

  if (is_turn_in_progress_) {
    board_.UpdateBoard();
  }

  // this is a reset, if the striker doesnt have velocity anymore(due to friction)
  // and the chips have stopped moving then the user has to launch again
  if (glm::length(board_.striker_.GetVelocity()) < kLowerBoundDiskVelocity_
      && !board_.AreChipsMoving()) {
    has_user_launched_ = false;
    board_.striker_.ResetStriker();
  }

}

void Game::Launch() {
  has_user_launched_ = true;
}
