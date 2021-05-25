//
// Created by Samyak Jain on 12/8/20.
//

#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>
#include "core/chip.h"
#include "core/disk.h"
#include "core/striker.h"
#include "core/board.h"

TEST_CASE("detect disk collisions") {
  Board board(glm::vec2(0, 0), 500);
  SECTION("check disk to disk collisions") {
    Chip *first = new Chip(glm::vec2(10, 99), 10);
    first->SetVelocity(glm::vec2(-1, -1));
    Chip *second = new Chip(glm::vec2(9, 98), 10);
    second->SetVelocity(glm::vec2(1, 1));

    board.AddChip(first);
    board.AddChip(second);

    REQUIRE(board.GetDisk(9).GetVelocity() == glm::vec2(1, 1));
    REQUIRE(board.GetDisk(10).GetVelocity() == glm::vec2(-1, -1));
  }SECTION("check striker to disk collisions") {
    board.striker_.ResetStriker();
    board.striker_.SetVelocity(glm::vec2(1, 1));

    Chip *first = new Chip(glm::vec2(351, 551), 10);
    first->SetVelocity(glm::vec2(-1, -1));
    board.AddChip(first);

    REQUIRE(board.striker_.GetVelocity() == glm::vec2(0, 0));
    REQUIRE(board.GetDisk(9).GetVelocity() == glm::vec2(2, 2));
  }
}

TEST_CASE("detect pocketed disks") {
  Board board(glm::vec2(0, 0), 500);
  SECTION("test top left pocket") {
    board.CheatCode(0, 100);
    REQUIRE(board.GetScore() == 100);
  }SECTION("test top right pocket") {
    board.CheatCode(1, 100);
    REQUIRE(board.GetScore() == 100);
  }SECTION("test bottom left pocket") {
    board.CheatCode(2, 100);
    REQUIRE(board.GetScore() == 100);
  }SECTION("test bottom right pocket") {
    board.CheatCode(3, 100);
    REQUIRE(board.GetScore() == 100);
  }SECTION("no pocketed disks") {
    Chip *first = new Chip(glm::vec2(10, 99), 10);
    board.AddChip(first);
    REQUIRE(board.GetScore() == 0);
  }
}

TEST_CASE("test are chips moving") {
  Board board(glm::vec2(0, 0), 500);
  SECTION("chips stationary") {
    REQUIRE_FALSE(board.AreChipsMoving());
  }SECTION("chip moving positive x, positive y direction") {
    Chip *first = new Chip(glm::vec2(10, 99), 10);
    first->SetVelocity(glm::vec2(1, 1));
    board.AddChip(first);
    REQUIRE(board.AreChipsMoving());
  }SECTION("chip moving negative x, negative y direction") {
    Chip *first = new Chip(glm::vec2(10, 99), 10);
    first->SetVelocity(glm::vec2(-1, -1));
    board.AddChip(first);
    REQUIRE(board.AreChipsMoving());
  }SECTION("chip moving negative x, positive y direction") {
    Chip *first = new Chip(glm::vec2(10, 99), 10);
    first->SetVelocity(glm::vec2(-1, 1));
    board.AddChip(first);
    REQUIRE(board.AreChipsMoving());
  }SECTION("chip moving positive x, negative y direction") {
    Chip *first = new Chip(glm::vec2(10, 99), 10);
    first->SetVelocity(glm::vec2(1, -1));
    board.AddChip(first);
    REQUIRE(board.AreChipsMoving());
  }
}

TEST_CASE("test generated pockets") {
  Board board(glm::vec2(0, 0), 500);

  std::vector<Pocket>
      pockets = board.GeneratePockets(glm::vec2(0, 0), glm::vec2(500, 500));

  REQUIRE(pockets[0].GetCenter() == glm::vec2(22.2, 22.2));
  REQUIRE(pockets[1].GetCenter() == glm::vec2(477.8, 22.2));
  REQUIRE(pockets[2].GetCenter() == glm::vec2(22.2, 477.8));
  REQUIRE(pockets[3].GetCenter() == glm::vec2(477.8, 477.8));
  REQUIRE(pockets[0].GetRadius() - 22.2 < 0.001);
  REQUIRE(pockets[1].GetRadius() - 22.2 < 0.001);
  REQUIRE(pockets[2].GetRadius() - 22.2 < 0.001);
  REQUIRE(pockets[3].GetRadius() - 22.2 < 0.001);
}