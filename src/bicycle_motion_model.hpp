//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
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

  class BicycleMotionModel
  {
  public:
    /**
     * Construct a bicycle model.
     *
     * @param wheel_base Distance between front and rear axle [m]
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
     * Propagate the state forward in time.
     *
     * @param dt             Time step [s]
     * @param velocity_cmd   Longitudinal velocity command [m/s]
     * @param steering_cmd   Steering angle [rad]
     */
    void update(double dt, double velocity, double steering_angle)
    {
       double beta = std::atan(0.5 * std::tan(steering_angle)); 
       state_.x += velocity * std::cos(state_.psi + beta) * dt;
       state_.y += velocity * std::sin(state_.psi + beta) * dt;
       state_.psi += (velocity / wheelbase_) * std::sin(beta) * dt;
       state_.v = velocity;
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