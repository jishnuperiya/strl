//******** Copyright   2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Unified interface for all motion models using modern C++23 features.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include "vehicle_state.hpp"
#include "motion_command.hpp"

//****************************************************************************
namespace sentinex::model{
//****************************************************************************

  using sentinex::estimation::vehicle_state;
  /**
  * Base class for all motion models
  */
  class motion_model
  {
  public:
    virtual ~motion_model() = default;

    virtual void update(double dt, const motion_command& cmd) = 0;
    virtual void reset(const vehicle_state& state) = 0;
    virtual vehicle_state get_state() const = 0;
  };

//****************************************************************************
} // namespace sentinex::model
//****************************************************************************




