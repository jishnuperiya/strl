//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Simple example demonstrating usage of the car_motion_model to propagate a vehicle state forward in time.
//****************************************************************************
#pragma once
//****************************************************************************

#include <iostream>                // for cout
#include <chrono>                  // for chrono

#include "vehicle_state.hpp"
#include "motion_command.hpp"
#include "car_motion_model.hpp"

//****************************************************************************

using sentinex::model::car_motion_model;
using sentinex::model::motion_command;
using sentinex::estimation::vehicle_state;

int main()
{
  /**
  * demonstrates usage of the car_motion_model to propagate a vehicle state forward in time.
  */
  car_motion_model model;

  vehicle_state state;

  model.reset(state);

  motion_command cmd;
  cmd.velocity_cmd = 10.0; // 10 m/s
  cmd.steering_cmd = 0.1;  // 0.1 rad

  constexpr double dt = 0.1; // 0.1s
  constexpr int steps = 100; 

  double t = 0.0;
  for (int i = 0; i < steps; ++i)
  {
    model.update(dt, cmd);
    state = model.get_state();
    std::cout << "Time: " << t << "s, "
      << "Position: (" << state.x << ", " << state.y << "), "
      << "Heading: " << state.psi << " rad, "
      << "Velocity: " << state.v << " m/s"
      << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    t += dt;
  }
}