#include <iostream>
#include <vehicle_state.hpp>
#include <bicycle_motion.hpp>
#include <motion_command.hpp>
#include <thread>
#include <chrono>

using sentinex::model::BicycleMotionModel;
using sentinex::model::MotionCommand;
using sentinex::estimation::VehicleState;
int main()
{
  BicycleMotionModel model;
  VehicleState state;

  model.reset(state);

  MotionCommand cmd;
  cmd.velocity_cmd = 10.0; // 10 m/s
  cmd.steering_cmd = 0.1;  // 0.1 rad

  constexpr double dt = 0.1; // time step of 0.1 seconds
  constexpr int steps = 100; // simulate for 10 seconds

  double t = 0.0;
  for(int i = 0; i < steps; ++i)
  {
    model.update(dt, cmd);
    state = model.getState();
    std::cout << "Time: " << t << "s, "
              << "Position: (" << state.x << ", " << state.y << "), "
              << "Heading: " << state.psi << " rad, "
              << "Velocity: " << state.v << " m/s"
              << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    t += dt;
  }
  return 0;
}