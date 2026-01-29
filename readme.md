# STRL — Sensor Truth Replay Lab

STRL is a minimal, deterministic dataflow framework for replaying recorded multi-sensor data and running controlled experiments on perception pipelines.

The goal of STRL is to make timing, synchronization, calibration, and failure modes observable and reproducible — not to provide a full autonomy or robotics stack.


## Motivation


In production robotics, autonomous, and aerospace systems, many failures are caused by:
- timestamp misalignment
- latency accumulation
- calibration drift
- unobservable system interactions

These issues are difficult to analyze using live systems or simulation alone.

STRL provides a replay-based validation lab where recorded sensor data can be re-executed deterministically under controlled conditions.

## What STRL is

- Deterministic replay of recorded sensor data
- Explicit time and synchronization model
- ADTF-inspired, component-based dataflow
- Controlled fault injection (latency, jitter, drops)
- System-level validation and metrics

## What STRL is not

- Not a full autonomy stack
- Not a ROS replacement
- Not a simulator
- Not focused on ML accuracy benchmarks

## Documentation

- [White paper](docs/whitepaper.pdf)
- Architecture overview (docs/architecture.md)

---

## Project Layout

The project is structured conservatively to allow the architecture to evolve without premature commitment to specific binaries or libraries:

- **`strl-core`**  
  Core library containing the dataflow framework, time model, and validation primitives.

- **`strl-test`**  
  Doctest-based test and experimentation harness linking against `strl-core`.  
  Includes a rich command-line interface and property-based testing via RapidCheck.

- **`strl-cli`**  
  Reference executable demonstrating replay, configuration, and inspection workflows.

These choices are intentionally lightweight and may evolve as the project matures.

---

## Prerequisites

### macOS

```bash
sudo port install clang-20 cmake doxygen

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

    ./srtl-test

Run the reference CLI executable:

    ./srtl-cli

## Status

STRL is an active, early-stage open-source project.

Initial development focuses on:

- Deterministic replay

- Explicit time modeling

- Minimal, inspectable dataflow execution

Interfaces and APIs should be considered experimental at this stage.

# Contributors

- jishnuperiya@gmail.com
- jonathon.bell@gmail.com
