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

#include "vehicle_state.hpp"          // for sentinex::estimation::VehicleState

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
    void update(double dt, double velocity_cmd, double steering_angle_cmd)
    {

       // Slip angle at the vehicle center of mass
       const double beta = std::atan(0.5 * std::tan(steering_angle_cmd)); 
       
       state_.x += velocity_cmd * std::cos(state_.psi + beta) * dt;
       state_.y += velocity_cmd * std::sin(state_.psi + beta) * dt;
       state_.psi += (velocity_cmd / wheelbase_) * std::sin(beta) * dt;
       state_.v = velocity_cmd;
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
    estimation::VehicleState state_;
    double wheelbase_;
  };
}