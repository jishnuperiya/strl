//******** Copyright   2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implements a simplified kinematic bicycle model used to propagate
//*            a vehicle state forward in time based on steering and velocity commands.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <cassert>                    // for assert
#include <cmath>                      // for std::atan, std::tan, std::cos, std::sin, std::isfinite
#include "vehicle_state.hpp"          // for sentinex::estimation::VehicleState
#include "motion_command.hpp"         // for sentinex::modell::MotionCommands

//****************************************************************************
namespace sentinex::model{
//****************************************************************************

 /**
 * Represents a kinematic bicycle motion model for planar vehicle motion.
 *
 */
  class BicycleMotionModel
  {
  public:
    /**
     * Construct a bicycle model.
     *
     * @param wheelbase Distance between front and rear axle [m]
     */
    explicit BicycleMotionModel(double wheelbase = 4.0)
      : wheelbase_(wheelbase)
    {
    }

    /**
     * Reset the vehicle state.
     *
     * @param state New vehicle state
     */
    void reset(const estimation::VehicleState& state)
    {
      state_ = state;
    }

  /**
  * @brief Propagates the vehicle state forward in time using a kinematic
  *        bicycle model.
  *
  * The model assumes constant longitudinal velocity and steering angle
  * over the time step and neglects dynamic effects such as tire slip,
  * roll, or pitch.
  *
  * State update:
  *  - x, y  : global position [m]
  *  - psi   : heading angle [rad]
  *  - v     : longitudinal velocity [m/s]
  *
  * @param dt                   Integration time step [s], must be > 0
  * @param velocity_cmd         Longitudinal velocity command [m/s]
  * @param steering_angle_cmd   Front wheel steering angle [rad]
  */
    void update(double dt, const MotionCommand& cmd)
    {
      assert(dt > 0.0 && "Time step must be positive");
      assert(std::isfinite(cmd.velocity_cmd) && "Velocity must be finite");
      assert(std::isfinite(cmd.steering_cmd) && "Steering angle must be finite");

       // Slip angle at the vehicle center of mass
       const double beta = std::atan(0.5 * std::tan(cmd.steering_cmd)); 
       
       state_.x += cmd.velocity_cmd * std::cos(state_.psi + beta) * dt;
       state_.y += cmd.velocity_cmd * std::sin(state_.psi + beta) * dt;
       state_.psi += (cmd.velocity_cmd / wheelbase_) * std::sin(beta) * dt;
       
       state_.psi = normalizeAngle(state_.psi);

       state_.v = cmd.velocity_cmd;
    }
    /**
     * Get the current vehicle state.
     *
     * @return Current vehicle state
     */
    estimation::VehicleState getState() const
    {
      return state_;
    }

  private:
    /**
    * Normalize angle to [-π, π]
    *
    * @param angle Input angle [rad]
    * @return Normalized angle [rad]
    */
    static double normalizeAngle(double angle)
    {
      return std::atan2(std::sin(angle), std::cos(angle));
    }

    estimation::VehicleState state_;
    double wheelbase_;
  };
}