//
// Created by Samyak Jain on 12/5/20.
//

#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>
#include "core/pocket.h"
#include "core/chip.h"

TEST_CASE("test pcoket constructor") {
  glm::vec2 center(200, 300);
  double radius = 10;

  Pocket pocket(center, radius);

  REQUIRE(pocket.GetCenter() == center);
  REQUIRE(pocket.GetRadius() == radius);
}

TEST_CASE("test is inside pocket") {
  Pocket pocket(glm::vec2(50, 50), 50);
  SECTION("center of disk = center of pocket") {
    Chip chip(pocket.GetCenter(), 10);
    REQUIRE(pocket.IsDiskInsidePocket(chip));
  }SECTION("center of disk inside pocket") {
    Chip chip(glm::vec2(75, 75), 10);
    REQUIRE(pocket.IsDiskInsidePocket(chip));
  }SECTION("center of disk on boundary of pocket") {
    Chip chip(glm::vec2(100, 50), 10);
    REQUIRE(pocket.IsDiskInsidePocket(chip));
  }SECTION("center of disk not in pocket") {
    Chip chip(glm::vec2(300, 400), 10);
    REQUIRE_FALSE(pocket.IsDiskInsidePocket(chip));
  }
}