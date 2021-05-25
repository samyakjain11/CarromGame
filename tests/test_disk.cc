//
// Created by Samyak Jain on 12/5/20.
//

#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>
#include "core/chip.h"
#include "core/disk.h"
#include "core/striker.h"

TEST_CASE("test update velocity") {
  Chip chip(glm::vec2(30, 30), 10);
  SECTION("x,y components positive") {
    chip.SetVelocity(glm::vec2(100, 100));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x < glm::vec2(100, 100).x);
    REQUIRE(chip.GetVelocity().y < glm::vec2(100, 100).y);
  }SECTION("velocity x component = 0") {
    chip.SetVelocity(glm::vec2(0, 100));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x == glm::vec2(0, 100).x);
    REQUIRE(chip.GetVelocity().y < glm::vec2(0, 100).y);
  }SECTION("velocity y component = 0") {
    chip.SetVelocity(glm::vec2(100, 0));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x < glm::vec2(100, 0).x);
    REQUIRE(chip.GetVelocity().y == glm::vec2(100, 0).y);
  }SECTION("velocity magnitude = 0") {
    chip.SetVelocity(glm::vec2(0, 0));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x == glm::vec2(0, 0).x);
    REQUIRE(chip.GetVelocity().y == glm::vec2(0, 0).y);
  }SECTION("velocity x component negative") {
    chip.SetVelocity(glm::vec2(-100, 100));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x > glm::vec2(-100, 100).x);
    REQUIRE(chip.GetVelocity().y < glm::vec2(-100, 100).y);
  }SECTION("velocity y component negative") {
    chip.SetVelocity(glm::vec2(100, -100));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x < glm::vec2(100, -100).x);
    REQUIRE(chip.GetVelocity().y > glm::vec2(100, -100).y);
  }SECTION("velocity overall negative") {
    chip.SetVelocity(glm::vec2(-100, -100));
    chip.UpdateVelocity();
    REQUIRE(chip.GetVelocity().x > glm::vec2(-100, -100).x);
    REQUIRE(chip.GetVelocity().y > glm::vec2(-100, -100).y);
  }
}

// i didnt test this as thoroughly since the only logic the method contains is
// the += operator override of glm::vec2 which is an outside library
TEST_CASE("test update position") {
  Chip chip(glm::vec2(30, 30), 10);
  chip.SetVelocity(glm::vec2(1, 1));
  chip.UpdatePosition();
  REQUIRE(chip.GetPosition() == glm::vec2(31, 31));
}

TEST_CASE("test is collision") {
  SECTION("collision") {
    Chip first(glm::vec2(10, 99), 10);
    first.SetVelocity(glm::vec2(-1, -1));
    Chip second(glm::vec2(9, 98), 10);
    second.SetVelocity(glm::vec2(1, 1));
    REQUIRE(disk::IsCollision(first, second));
  }SECTION("no collision") {
    Chip first(glm::vec2(100, 99), 10);
    first.SetVelocity(glm::vec2(-1, -1));
    Chip second(glm::vec2(9, 98), 10);
    second.SetVelocity(glm::vec2(1, 1));
    REQUIRE_FALSE(disk::IsCollision(first, second));
  }SECTION("sticking glitch") {
    Chip first(glm::vec2(10, 99), 10);
    first.SetVelocity(glm::vec2(1, 1));
    Chip second(glm::vec2(9, 98), 10);
    second.SetVelocity(glm::vec2(-1, -1));
    REQUIRE_FALSE(disk::IsCollision(first, second));
  }
}

TEST_CASE("collision between disks") {
  SECTION("same masses") {
    SECTION("moving disk hits moving disk") {
      Chip first(glm::vec2(10, 99), 10);
      first.SetVelocity(glm::vec2(-1, -1));
      Chip second(glm::vec2(9, 98), 10);
      second.SetVelocity(glm::vec2(1, 1));
      disk::Collision(first, second);
      REQUIRE(first.GetVelocity().y == 1);
      REQUIRE(first.GetVelocity().x == 1);
      REQUIRE(second.GetVelocity().y == -1);
      REQUIRE(second.GetVelocity().x == -1);
    }SECTION("moving disk hits stationary disk") {
      Chip first(glm::vec2(10, 99), 10);
      first.SetVelocity(glm::vec2(-1, -1));
      Chip second(glm::vec2(9, 98), 10);
      second.SetVelocity(glm::vec2(0, 0));
      disk::Collision(first, second);
      REQUIRE(first.GetVelocity().y == 0);
      REQUIRE(first.GetVelocity().x == 0);
      REQUIRE(second.GetVelocity().y == -1);
      REQUIRE(second.GetVelocity().x == -1);
    }
  }SECTION("different masses") {
    Striker striker;
    striker.SetVelocity(glm::vec2(20, 20));
    Chip chip(glm::vec2(280, 480), 10);
    chip.SetVelocity(glm::vec2(-20, -20));
    disk::Collision(striker, chip);
    REQUIRE(striker.GetVelocity().y == 0);
    REQUIRE(striker.GetVelocity().x == 0);
    REQUIRE(chip.GetVelocity().y == 40);
    REQUIRE(chip.GetVelocity().x == 40);
  }
}

TEST_CASE("test axes collisions") {
  SECTION("collisions") {
    SECTION("walls") {
      SECTION("horizontal wall") {
        Chip chip(glm::vec2(99, 10), 10);
        chip.SetVelocity(glm::vec2(10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == -10);
      }SECTION("vertical \'wall\'") {
        Chip chip(glm::vec2(10, 99), 10);
        chip.SetVelocity(glm::vec2(10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().y == -10);
      }
    }SECTION("corners") {
      SECTION("top left") {
        Chip chip(glm::vec2(1, 1), 10);
        chip.SetVelocity(glm::vec2(-10, -10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == 10);
        REQUIRE(chip.GetVelocity().y == 10);
      }SECTION("bottom left") {
        Chip chip(glm::vec2(1, 99), 10);
        chip.SetVelocity(glm::vec2(-10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == 10);
        REQUIRE(chip.GetVelocity().y == -10);
      }SECTION("top right") {
        Chip chip(glm::vec2(99, 1), 10);
        chip.SetVelocity(glm::vec2(10, -10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == -10);
        REQUIRE(chip.GetVelocity().y == 10);
      }SECTION("bottom right") {
        Chip chip(glm::vec2(99, 99), 10);
        chip.SetVelocity(glm::vec2(10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == -10);
        REQUIRE(chip.GetVelocity().y == -10);
      }
    }
  }SECTION("no collision") {
    SECTION("walls") {
      SECTION("disk close to horizontal wall") {
        Chip chip(glm::vec2(99, 10), 10);
        chip.SetVelocity(glm::vec2(-10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == -10);
      }SECTION("disk close to vertical \'wall\'") {
        Chip chip(glm::vec2(10, 99), 10);
        chip.SetVelocity(glm::vec2(10, -10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().y == -10);
      }
    }SECTION("corners") {
      SECTION("top left") {
        Chip chip(glm::vec2(1, 1), 10);
        chip.SetVelocity(glm::vec2(10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == 10);
        REQUIRE(chip.GetVelocity().y == 10);
      }SECTION("bottom left") {
        Chip chip(glm::vec2(1, 99), 10);
        chip.SetVelocity(glm::vec2(10, -10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == 10);
        REQUIRE(chip.GetVelocity().y == -10);
      }SECTION("top right") {
        Chip chip(glm::vec2(99, 1), 10);
        chip.SetVelocity(glm::vec2(-10, 10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == -10);
        REQUIRE(chip.GetVelocity().y == 10);
      }SECTION("bottom right") {
        Chip chip(glm::vec2(99, 99), 10);
        chip.SetVelocity(glm::vec2(-10, -10));
        chip.HandleAxesCollisions(glm::vec2(0, 0), glm::vec2(100, 100));
        chip.UpdatePosition();
        REQUIRE(chip.GetVelocity().x == -10);
        REQUIRE(chip.GetVelocity().y == -10);
      }
    }
  }
}