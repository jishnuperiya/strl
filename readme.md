# Sentinex | State Estimation & Sensor Simulation Lab

Sentinex is a C++20 codebase for vehicle state propagation and estimation experiments, with an initial focus on clear contracts, deterministic behavior, and testable invariants.

The project currently provides a minimal, well-defined kinematic bicycle motion model and supporting infrastructure, intended as a foundation for future simulation and state-estimation work.

Generated documentation:
https://jishnuperiya.github.io/sentinex/

## Prerequisites

### macOS

```bash
sudo port install clang-20 cmake doxygen
```
## Building

    mkdir .bld
    cd .bld
    cmake ..
    make -j

Also:

    make help

to see a list of possible of build targets.

## Running

Run the test and experimentation harness:

    ./sentinex-test

Run the reference CLI executable:

    ./sentinex-cli


# Contributors

- jishnuperiya@gmail.com
- jonathon.bell@gmail.com
