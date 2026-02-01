#include <iostream>
#include <vehicle_state.hpp>

int main()
{
  
  sentinex::estimation::VehicleState state;

  std::cout << "x=" << state.x
    << " y=" << state.y
    << " psi=" << state.psi
    << " v=" << state.v
    << "\n";

  return 0;
}