//******** copyright © 2025 jishnu periya, jonathon bell. all rights reserved.
//*
//*
//*  version : $header:$
//*
//*
//*  purpose : Unit tests for the BicycleMotionModel used in
//*            the Sentinex model module.
//*
//*
//*  see also: https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
//*            for more on the doctest main entry point.
//*                                                                     0-0
//*                                                                   (| v |)
//**********************************************************************w*w***

#include <doctest/doctest.h>         // for doctest
#include <rapidcheck.h>              // for rc 
#include <bicycle_motion.hpp>        // for sentinex::model::BicycleMotionModel

//****************************************************************************

using sentinex::model::BicycleMotionModel;
using sentinex::estimation::VehicleState;

//****************************************************************************
// Baseline generator: unconstrained VehicleState
template<>
struct rc::Arbitrary<sentinex::estimation::VehicleState>
{
  static rc::Gen<sentinex::estimation::VehicleState> arbitrary()
  {
    auto gen_x = rc::gen::arbitrary<double>();
    auto gen_y = rc::gen::arbitrary<double>();
    auto gen_psi = rc::gen::arbitrary<double>();
    auto gen_v = rc::gen::arbitrary<double>();

    return rc::gen::construct<VehicleState>(
      gen_x,
      gen_y,
      gen_psi,
      gen_v
    );
  }
};

TEST_CASE("BicycleMotionModel: reset reproduces state exactly")
{
  rc::check("reset sets the internal state to the provided state",
    [](const VehicleState& state)
    {
      BicycleMotionModel model{ 4.0 };
      model.reset(state);
      const auto new_state = model.getState();
      RC_ASSERT(new_state.x == state.x);
      RC_ASSERT(new_state.y == state.y);
      RC_ASSERT(new_state.psi == state.psi);
      RC_ASSERT(new_state.v == state.v);

    });
}

TEST_CASE("BicycleMotionModel: zero velocity causes no motion ")
{
  rc::check("v=0 implied no change in pose",
    [](VehicleState state, double steering)
    {
      BicycleMotionModel model{ 4.0 };
      model.reset(state);

      model.update(1.0, 0.0, steering);
      const auto new_state = model.getState();

      RC_ASSERT(new_state.x == state.x);
      RC_ASSERT(new_state.y == state.y);
      RC_ASSERT(new_state.psi == state.psi);
      RC_ASSERT(new_state.v == state.v);
    });

}


TEST_CASE("BicycleMotionModel: straight line motion ")
{
  rc::check("zero steering cause y and psi constant",
    [](VehicleState state, double velocity_cmd, double dt)
    {
     BicycleMotionModel model{ 4.0 };
     model.reset(state);

      model.update(dt, velocity_cmd,0.0);
      const auto new_state = model.getState();

      RC_ASSERT(new_state.y == state.y);
      RC_ASSERT(new_state.psi == state.psi);
      RC_ASSERT(new_state.v == doctest::Approx(new_state.v + dt * velocity_cmd));

    });

}

