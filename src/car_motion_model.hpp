//******** Copyright   2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implements a simplified  model model for car used to propagate
//*            a vehicle state forward in time based on steering and velocity commands.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <cassert>                    // for assert
#include <cmath>                      // for atan2, tan, cos, sin, isfinite
   
#include "motion_model_interface.hpp"

//****************************************************************************
namespace sentinex::model{
//****************************************************************************
 /**
 * Kinematic bicycle motion model for planar vehicle state propagation.
 * 
 * Propagates a vehicle state forward in time based on steering and velocity commands.
 * 
 * Assume no slip dynamics beyond the simplified bicycle approximation.
 *
 * @see [Here](https://code.eng.buffalo.edu/dat/sites/model/bicycle.html)
 *      for more on kinematic bicycle model
 */
  class car_motion_model : public motion_model
  {
  public:
    /**
    * Constructs a car_motion_model with the specified wheelbase.
    */
    car_motion_model(double wheelbase = 4.0)
      : wheelbase_{ wheelbase }, state_{}
    {
      assert(wheelbase_ > 0.0);
    }

    // Update the vehicle state based on the kinematic bicycle model equations.
    void update(double dt, const motion_command& cmd) override;

    /**
    * Resets the internal state of the model to the provided state. 
    *
    * This allows the model to be re-initialized to an arbitrary state.
    */
    void reset(const vehicle_state& state) override
    {
      state_ = state;
    }

    /**
    * Returns the current state of the vehicle.
    */
    vehicle_state get_state() const override
    {
      return state_;
    }

  private:
    /**
   * Normalize angle to [-?, ?]
   *
   * @param angle Input angle [rad]
   * @return Normalized angle [rad]
   */
    static double normalize_angle(double angle)
    {
      return std::atan2(std::sin(angle), std::cos(angle));
    }

    double wheelbase_;
    vehicle_state state_;
  };







//****************************************************************************
} // namespace sentinex::model
//****************************************************************************

