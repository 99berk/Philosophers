# Philosopher's

## Introduction

This project is an implementation of the dining philosophers problem, a classic synchronization problem often used to illustrate the challenges of deadlock and resource allocation in concurrent computing.

## Overview

The project simulates a scenario where a number of philosophers sit at a round table, with a large bowl of spaghetti in the middle. The philosophers alternate between eating, thinking, and sleeping. Each philosopher must hold two forks to eat. However, there is a constraint that prevents philosophers from eating indefinitely, leading to the possibility of starvation if not managed correctly.

## Common Instructions

- The project is implemented in C.
- It adheres to a set of rules specified in the assignment, including error handling, memory management, and usage of threads and mutexes.
- A Makefile is included for compiling the source files with required flags.

## Installation

1. Clone the repository: `git clone https://github.com/99berk/42_philosophers.git`
2. Navigate to the project directory: `cd philosophers`
3. Compile the program using the provided Makefile: `make`

## Usage

The program can be executed with the following command-line arguments:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

- `number_of_philosophers`: The number of philosophers.
- `time_to_die`: Time in milliseconds before a philosopher dies if they haven't started eating.
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): Specifies how many times each philosopher must eat before the simulation stops.

## Implementation Details

The project is divided into multiple source files:

- `philo.c`: Main file containing the program entry point and the main logic of the dining philosophers simulation.
- `philo.h`: Header file containing function prototypes, struct definitions, and any necessary macro definitions.
- `life_of_philo.c`: Defines the life cycle of a philosopher, including actions such as eating, sleeping, and thinking.
- `smell_of_death.c`: Manages the detection of philosopher deaths and implements the logic to handle the end of the simulation.
- `utils.c`: Provides various utility functions for error handling, time calculation etc.
