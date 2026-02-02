#include <iostream>
#include <vehicle_state.hpp>
#include <bicycle_motion_model.hpp>

int main()
{
  
  //sentinex::estimation::VehicleState state;
  sentinex::model::BicycleMotionModel model(2.5); // wheelbase of 2.5 meters

  model.reset({ 0.0, 0.0, 0.0, 0.0 }); // initial state: x=0, y=0, psi=0, v=0
  double dt = 0.1; // time step of 0.1 seconds
  double velocity_cmd = 5.0; // 5 m/s
  double steering_cmd = 0.1; // 0.1 radians

  for (int i = 0; i < 10; ++i)
  {
    model.update(dt, velocity_cmd, steering_cmd);
    sentinex::estimation::VehicleState state = model.getState();
    std::cout << state.x;
  }
  return 0;
}