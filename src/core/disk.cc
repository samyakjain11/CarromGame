//
// Created by Samyak Jain on 11/13/20.
//

#include "core/disk.h"
#include "core/board.h"

void disk::Disk::UpdatePosition() {
  position_ += velocity_;
}

void disk::Disk::UpdateVelocity() {
  velocity_ *= Board::kFrictionCoefficient;
//velocity_ -= glm::vec2(velocity_.x * 0.1, velocity_.y * 0.1);
}

glm::vec2 disk::Disk::GetVelocity() const {
  return velocity_;
}

glm::vec2 disk::Disk::GetPosition() const {
  return position_;
}

double disk::Disk::GetRadius() const {
  return radius_;
}

bool disk::IsCollision(const Disk &first, const Disk &second) {
  glm::vec2
      diff_in_first_velocity =
      first.GetVelocity() - second.GetVelocity();
  glm::vec2
      diff_in_first_position =
      first.GetPosition() - second.GetPosition();

  double
      this_dot_product =
      glm::dot(diff_in_first_position, diff_in_first_velocity);

  // if the dot product is greater than 0 that tells us that the disks are
  // moving away from each other, in which scenario, changing the velocities will
  // cause bugs like sticking to each other
  if (this_dot_product >= 0) {
    return false;
  } else {
    double dist_between_particles =
        glm::distance(first.GetPosition(), second.GetPosition());
    if (dist_between_particles < 2 * first.GetRadius()
        || dist_between_particles < 2 * second.GetRadius())
      return true;
    return false;
  }
}

void disk::Collision(Disk &first, Disk &second) {
  glm::vec2
      diff_in_this_velocity = first.GetVelocity() - second.GetVelocity();
  glm::vec2
      diff_in_this_position = first.GetPosition() - second.GetPosition();

  glm::vec2 diff_in_other_velocity =
      second.GetVelocity() - first.GetVelocity();
  glm::vec2 diff_in_other_position =
      second.GetPosition() - first.GetPosition();

  double
      this_dot_product = glm::dot(diff_in_this_position, diff_in_this_velocity);
  double other_dot_product =
      glm::dot(diff_in_other_position, diff_in_other_velocity);

  double this_denom =
      pow(glm::length(diff_in_this_position), 2) * (first.GetMass() +
          second.GetMass());
  double other_denom =
      pow(glm::length(diff_in_other_position), 2) * (first.GetMass() +
          second.GetMass());

  glm::vec2
      this_expr = glm::vec2((float) (
                                ((this_dot_product * (2 * second.GetMass())) /
                                    this_denom)
                                    * diff_in_this_position.x),
                            (float) (
                                ((this_dot_product * (2 * second.GetMass()))
                                    / this_denom)
                                    * diff_in_this_position.y));
  glm::vec2
      other_expr =
      glm::vec2((float) (
                    ((other_dot_product * (2 * first.GetMass())) / other_denom)
                        * diff_in_other_position.x),
                (float) (((other_dot_product * (2 * first.GetMass()))
                    / other_denom)
                    * diff_in_other_position.y));


  first.SetVelocity(first.GetVelocity() - this_expr);
  second.SetVelocity(second.GetVelocity() - other_expr);
}

double disk::Disk::GetMass() const {
  return mass_;
}

void disk::Disk::SetVelocity(glm::vec2 new_vel) {
  velocity_ = new_vel;
}

void disk::Disk::VerticleCollision() {
  velocity_.y = -velocity_.y;
}

void disk::Disk::HorizontalCollision() {
  velocity_.x = -velocity_.x;
}

bool
disk::Disk::IsHorizontalCollision(double x_left_bound, double x_right_bound) {
  if (position_.x > x_left_bound && position_.x < x_right_bound) {
    double dist_from_left_bound =
        glm::distance(position_, glm::vec2(x_left_bound, position_.y));
    double dist_from_right_bound =
        glm::distance(position_, glm::vec2(x_right_bound, position_.y));

    if ((dist_from_left_bound < radius_ && velocity_.x < 0)
        || (dist_from_right_bound < radius_ && velocity_.x > 0))
      return true;
    return false;
  }
  return true;

}

bool
disk::Disk::IsVerticleCollision(double y_lower_bound, double y_upper_bound) {
  if (position_.y > y_lower_bound && position_.y < y_upper_bound) {
    double dist_from_lower_bound =
        glm::distance(position_, glm::vec2(position_.x, y_lower_bound));
    double dist_from_upper_bound =
        glm::distance(position_, glm::vec2(position_.x, y_upper_bound));

    if ((dist_from_lower_bound < radius_ && velocity_.y < 0)
        || (dist_from_upper_bound < radius_ && velocity_.y > 0))
      return true;
    return false;
  }
  return true;
}


void disk::Disk::HandleAxesCollisions(glm::vec2 top_left_corner,
                                      glm::vec2 bottom_right_corner) {
  if (IsHorizontalCollision(top_left_corner.x, bottom_right_corner.x))
    HorizontalCollision();
  if (IsVerticleCollision(top_left_corner.y, bottom_right_corner.y))
    VerticleCollision();
}

std::string disk::Disk::GetColor() const {
  return color_;
}

double disk::Disk::GetPointValue() const {
  return point_value_;
}