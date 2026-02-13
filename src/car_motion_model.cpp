//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class car_motion_model.
//*
//*
//****************************************************************************

#include "car_motion_model.hpp"

//****************************************************************************
namespace sentinex::model{
//****************************************************************************
  /**
  * Update the vehicle state based on the kinematic bicycle model equations.
  */
  void car_motion_model::update(double dt, const motion_command& cmd)
  {
    assert(dt > 0.0); 
    assert(std::isfinite(cmd.velocity_cmd)); 
    assert(std::isfinite(cmd.steering_cmd)); 
    
    // Slip angle at the vehicle center of mass
    const double beta = std::atan(0.5 * std::tan(cmd.steering_cmd));

    state_.x += cmd.velocity_cmd * std::cos(state_.psi + beta) * dt;
    state_.y += cmd.velocity_cmd * std::sin(state_.psi + beta) * dt;
    state_.psi += (cmd.velocity_cmd / wheelbase_) * std::sin(beta) * dt;

    state_.psi = normalize_angle(state_.psi);

    state_.v = cmd.velocity_cmd;
  }


//****************************************************************************
} // namespace sentinex::model
//****************************************************************************

