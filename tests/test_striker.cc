//
// Created by Samyak Jain on 12/8/20.
//

#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>
#include "core/striker.h"

TEST_CASE("test striker constructor") {
  Striker striker;
  REQUIRE(striker.GetDegrees() == 270);
  REQUIRE(striker.GetPosition() == glm::vec2(350, 550));
  REQUIRE(striker.GetVelocity() == glm::vec2(0, 0));
  REQUIRE(striker.GetPointValue() == -10);
  REQUIRE(striker.GetColor() == "yellow");
}

TEST_CASE("test reset striker") {
  Striker striker;
  striker.ResetStriker();
  REQUIRE(striker.GetDegrees() == 270);
  REQUIRE(striker.GetPosition() == glm::vec2(350, 550));
  REQUIRE(striker.GetVelocity() == glm::vec2(0, 0));
}

// this is not tested thoroughly since the only logic inside the method is the
// use of the += overloaded operator of glm::vec2
TEST_CASE("test update location") {
  Striker striker;
  striker.UpdateLocation(glm::vec2(10, 10));
  REQUIRE(striker.GetPosition() == glm::vec2(360, 560));
}

TEST_CASE("test update striker properties") {
  Striker striker;
  SECTION("increase degrees") {
    striker.ResetStriker();
    striker.UpdateStrikerProperties(10, 0);
    REQUIRE(striker.GetDegrees() == 280);
  }SECTION("decrease degrees") {
    striker.ResetStriker();
    striker.UpdateStrikerProperties(-10, 0);
    REQUIRE(striker.GetDegrees() == 260);
  }SECTION("increase velocity") {
    striker.ResetStriker();
    striker.SetVelocity(glm::vec2(3, 4));
    striker.UpdateStrikerProperties(0, 1);
    REQUIRE(glm::length(striker.GetVelocity()) == 6);
  }SECTION("decrease velocity") {
    striker.ResetStriker();
    striker.SetVelocity(glm::vec2(3, 4));
    striker.UpdateStrikerProperties(0, -1);
    REQUIRE(glm::length(striker.GetVelocity()) == 4);
  }
}