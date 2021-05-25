//
// Created by Samyak Jain on 11/20/20.
//
#include "core/board.h"
#include "core/disk.h"
#include "core/striker.h"
#include "core/pocket.h"
#include "visualizer/carrom_game.h"
#include "core/chip.h"

Board::Board(glm::vec2 top_left_corner, double board_dimension) {
  top_left_corner_ = top_left_corner;
  board_rectangle_ = ci::Rectf(top_left_corner_,
                               glm::vec2(top_left_corner.x + board_dimension,
                                         top_left_corner.y + board_dimension));

  pockets_ = GeneratePockets(top_left_corner,
                             glm::vec2(
                                 top_left_corner.x + board_dimension,
                                 top_left_corner.y + board_dimension));

  score_ = 0;

  double disk_radii = Chip::kChipRealLifeRadius_ * Game::kRealLifeToGameRatio;

  // initializing red chip
  disks_.push_back(Chip(board_rectangle_.getCenter(), 50));

  // initializing black chips
  disks_.push_back(Chip(glm::vec2(
      board_rectangle_.getCenter().x + kBlackCenteringCoefficient_ * disk_radii,
      board_rectangle_.getCenter().y), point_values::kBlackValue));
  disks_.push_back(Chip(glm::vec2(
      board_rectangle_.getCenter().x - kBlackCenteringCoefficient_ * disk_radii,
      board_rectangle_.getCenter().y), point_values::kBlackValue));
  disks_.push_back(Chip(glm::vec2(board_rectangle_.getCenter().x,
                                  board_rectangle_.getCenter().y
                                      + kBlackCenteringCoefficient_
                                          * disk_radii), point_values::kBlackValue));
  disks_.push_back(Chip(glm::vec2(board_rectangle_.getCenter().x,
                                  board_rectangle_.getCenter().y
                                      - kBlackCenteringCoefficient_
                                          * disk_radii), point_values::kBlackValue));

  // initializing white chips
  disks_.push_back(Chip(glm::vec2(
      board_rectangle_.getCenter().x + kWhiteCenteringCoefficient_ * disk_radii,
      board_rectangle_.getCenter().y
          - kWhiteCenteringCoefficient_ * disk_radii), point_values::kWhiteValue));
  disks_.push_back(Chip(glm::vec2(
      board_rectangle_.getCenter().x - kWhiteCenteringCoefficient_ * disk_radii,
      board_rectangle_.getCenter().y
          - kWhiteCenteringCoefficient_ * disk_radii), point_values::kWhiteValue));
  disks_.push_back(Chip(glm::vec2(
      board_rectangle_.getCenter().x + kWhiteCenteringCoefficient_ * disk_radii,
      board_rectangle_.getCenter().y
          + kWhiteCenteringCoefficient_ * disk_radii), point_values::kWhiteValue));
  disks_.push_back(Chip(glm::vec2(
      board_rectangle_.getCenter().x - kWhiteCenteringCoefficient_ * disk_radii,
      board_rectangle_.getCenter().y
          + kWhiteCenteringCoefficient_ * disk_radii), point_values::kWhiteValue));
}


void Board::DrawBoard() const {
  DrawBoardDesign();
  DrawDisks();
  DrawStriker();
  DrawScore();
}

void Board::DrawBoardDesign() const {
  ci::gl::color(ci::Color8u(kBoardColorR_,
                            kBoardColorG_,
                            kBoardColorB_)); //light brown
  ci::gl::drawSolidRect(board_rectangle_);

  ci::gl::color(ci::Color("green"));
  for (const Pocket &p : pockets_) {
    ci::gl::drawSolidCircle(p.GetCenter(), p.GetRadius());
  }

  //drawing center circle
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedCircle(board_rectangle_.getCenter(),
                            kCenterCircleRealLifeRadius_
                                * Game::kRealLifeToGameRatio);
}

void Board::DrawDisks() const {
  for (const disk::Disk &d : disks_) {
    ci::gl::color(ci::Color(d.GetColor().c_str()));
    ci::gl::drawSolidCircle(d.GetPosition(), d.GetRadius());
  }
}

void Board::UpdateBoard() {
  DetectPocketedDisks();

  DetectStrikerToDiskCollisions();
  DetectDiskCollisions();

  UpdateStriker();
  UpdateDisks();
}

bool Board::AreChipsMoving() {
  for (disk::Disk &d : disks_) {
    if (glm::length(d.GetVelocity()) > Game::kLowerBoundDiskVelocity_)
      return true;
    else
      d.SetVelocity(glm::vec2(0, 0));
  }
  return false;
}

void Board::DrawStriker() const {
  ci::gl::color(ci::Color(striker_.GetColor().c_str()));
  ci::gl::drawLine(striker_.GetPosition(),
                   glm::vec2(striker_.GetPosition().x + kGuideLineMultiplier_
                                 * striker_.GetVelocity().x,
                             striker_.GetPosition().y + kGuideLineMultiplier_
                                 * striker_.GetVelocity().y));
  ci::gl::drawSolidCircle(striker_.GetPosition(), striker_.GetRadius());
}

void Board::DetectDiskCollisions() {
  for (size_t i = 0; i < disks_.size(); ++i) {
    for (size_t j = i; j < disks_.size(); ++j) {
      if (disk::IsCollision(disks_[i], disks_[j])) {
        disk::Collision(disks_[i], disks_[j]);
      }
    }
  }
}

void Board::DetectStrikerToDiskCollisions() {
  for (size_t i = 0; i < disks_.size(); ++i) {
    if (disk::IsCollision(disks_[i], striker_))
      disk::Collision(disks_[i], striker_);
  }
}

void Board::UpdateDisks() {
  for (disk::Disk &d : disks_) {
    d.HandleAxesCollisions(board_rectangle_.getUpperLeft(),
                           board_rectangle_.getLowerRight());
    d.UpdatePosition();
    d.UpdateVelocity();
  }
}

void Board::UpdateStriker() {
  striker_.HandleAxesCollisions(board_rectangle_.getUpperLeft(),
                                board_rectangle_.getLowerRight());
  striker_.UpdatePosition();
  striker_.UpdateVelocity();
}

void Board::DetectPocketedDisks() {
  for (size_t pocket_counter = 0; pocket_counter < pockets_.size();
       ++pocket_counter) {
    for (size_t disk_counter = 0; disk_counter < disks_.size();
         ++disk_counter) {
      if (pockets_[pocket_counter].IsDiskInsidePocket(disks_[disk_counter])) {
        score_ += disks_[disk_counter].GetPointValue();
        disks_.erase(disks_.begin() + disk_counter);
      }
    }
    if (pockets_[pocket_counter].IsDiskInsidePocket(striker_)) {
      score_ += striker_.GetPointValue();
      striker_.ResetStriker();
    }
  }
}

void Board::DrawScore() const {
  ci::gl::drawStringCentered(("Score: " + std::to_string(score_)),
                             glm::vec2(kXCenterScoreText_,
                                       board_rectangle_.getCenter().y));
}

void Board::CheatCode(int ind, int p_val) {
  disks_.push_back(Chip(pockets_[ind].GetCenter(), p_val));
  DetectPocketedDisks();
}

std::vector<Pocket> Board::GeneratePockets(glm::vec2 top_left_corner,
                                           glm::vec2 bottom_right_corner) {
  std::vector<Pocket> pockets;
  double radius = Pocket::kRealLifePocketRadius_ * Game::kRealLifeToGameRatio;

  Pocket tl(glm::vec2(top_left_corner.x + radius, top_left_corner.y + radius),
            radius);
  Pocket tr
      (glm::vec2(bottom_right_corner.x - radius, top_left_corner.y + radius),
       radius);
  Pocket bl
      (glm::vec2(top_left_corner.x + radius, bottom_right_corner.y - radius),
       radius);
  Pocket br(glm::vec2(bottom_right_corner.x - radius,
                      bottom_right_corner.y - radius), radius);

  pockets.push_back(tl);
  pockets.push_back(tr);
  pockets.push_back(bl);
  pockets.push_back(br);

  return pockets;
}

void Board::AddChip(Chip *chip) {
  disks_.push_back(*chip);
  DetectDiskCollisions();
  DetectStrikerToDiskCollisions();
  DetectPocketedDisks();
}

disk::Disk Board::GetDisk(int index) {
  return disks_[index];
}

int Board::GetScore() const {
  return score_;
}