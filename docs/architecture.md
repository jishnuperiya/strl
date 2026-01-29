# STRL Architecture Overview

This document describes the high-level architecture and core design concepts of STRL (Sensor Truth Replay Lab).

STRL is designed as a **deterministic, validation-first dataflow framework** for replaying recorded multi-sensor data and running controlled experiments on perception pipelines. The architecture prioritizes reproducibility, explicit time modeling, and observability over feature breadth or runtime flexibility.

---

## Design Goals

The architecture of STRL is guided by the following goals:

1. **Deterministic execution**  
   Given identical inputs and configuration, STRL must produce identical execution order, timing behavior, and outputs.

2. **Explicit time modeling**  
   Sensor time, system time, and scheduling behavior must be visible and controllable.

3. **Validation-first design**  
   The primary purpose of the system is inspection, measurement, and failure analysis.

4. **Minimalism**  
   Only architectural elements required to expose system behavior are included.

5. **Domain-agnostic applicability**  
   The same core architecture should apply to robotics, autonomous systems, and aerospace pipelines.

---

## Architectural Overview

At a high level, STRL consists of a **linear, component-based dataflow pipeline** executed under a deterministic scheduler.

Recorded Sensor Data
|
v
+------------------+
| Ingestion |
| - IO |
| - Timestamping |
+------------------+
|
v
+------------------+
| Time & Sync |
| - Clock models |
| - Alignment |
| - Jitter |
+------------------+
|
v
+------------------+
| Calibration |
| - Intrinsics |
| - Extrinsics |
| - Perturbation |
+------------------+
|
v
+------------------+
| Processing |
| - Projection |
| - Vision stages |
+------------------+
|
v
+------------------+
| Validation |
| - Latency |
| - Error metrics |
+------------------+
|
v
+------------------+
| Replay & Analysis|
| - Comparison |
| - Visualization |
+------------------+



Each stage is implemented as a **component** with well-defined inputs, outputs, and execution semantics.

---

## Components

A **component** is the fundamental unit of execution in STRL.

Components:
- Consume one or more typed input streams
- Produce one or more typed output streams
- Execute deterministically given the same inputs and configuration
- Are configured externally (configuration over code)

Components are intentionally simple and composable.

---

## Data Streams

Components communicate via **strongly typed, timestamped data streams**.

Key properties:
- Explicit ownership and lifetime
- No untyped payloads or implicit global state
- Data objects carry timestamps and clock-domain information

This enables precise reasoning about data movement and timing behavior.

---

## Time Model

Time is a first-class concept in STRL.

The system distinguishes between:
- **Sensor time**: timestamps originating from recorded sensors
- **System time**: execution and scheduling time within STRL

Clock domains are modeled explicitly, allowing:
- Deterministic alignment strategies
- Controlled offset and drift injection
- Repeatable timing experiments

Time advancement is controlled by the scheduler, not wall-clock time.

---

## Scheduler

STRL uses a **deterministic, explicit scheduler**.

Design choices:
- Execution order is fixed and reproducible
- Buffering and queueing are bounded
- Backpressure behavior is observable
- Single-threaded execution is the baseline; parallelism is optional and explicit

The scheduler exists to make timing behavior visible, not to maximize throughput.

---

## Replay and Controlled Experiments

Replay in STRL is defined as **deterministic re-execution under controlled conditions**, not passive playback.

During replay, the following parameters may be varied:
- Latency and jitter
- Buffer sizes and scheduling behavior
- Calibration parameters
- Component configuration

Only one variable is changed per experiment to preserve causal reasoning.

---

## Validation and Metrics

STRL emphasizes **system-level validation metrics**, including:
- End-to-end and per-component latency
- Synchronization error
- Calibration sensitivity
- Throughput degradation
- Failure frequency under perturbation

Metrics are collected with sufficient context to support root-cause analysis and regression detection.

---

## Configuration

Pipelines and experiments are defined via external configuration (e.g., YAML or JSON).

Configuration specifies:
- Component graph
- Parameter values
- Fault injection settings
- Metric collection

This allows experiments to be reproduced without recompilation.

---

## Non-Goals

The following are explicitly out of scope for STRL:
- Full autonomy or robotics stacks
- Planning and control
- SLAM
- Physics-based simulation
- Distributed or cloud execution

STRL is intentionally focused on **validation and understanding**, not deployment.

---

## Summary

STRL is a minimal, deterministic, ADTF-inspired dataflow framework designed to make perception system behavior observable and reproducible. Its architecture emphasizes explicit time modeling, controlled experimentation, and system-level validation across robotics, autonomous, and aerospace domains.


