*This project has been created as part of the 42 curriculum by takhayas*

## Description

-`philosophers` is a dining philosophers simulation implemented in C. Its goal is to understand the concept of thread, data race, and dead lock.
- Each philosopher is represented by a thread.
- Philosophers are taking forks, eating, sleeping, or thinking and the don't do them in the same time.  They are sitting around the table.
- Each philosopher needs two forks to eat.
- A philosopher dies if they do not start eating within `time_to_die` milliseconds since their last meal.
- If `number_of_times_each_philosopher_must_eat` is provided, the simulation ends when all philosophers have eaten at least that many times.
- The simulation also ends immediately when any philosopher dies.

## Instructions

### compilation
to compile:
```sh
make
```
- The `Makefile` uses `cc` with `-Wall -Wextra -Werror -pthread`.
- The project requires `pthread` support.

### execution
- The program must be executed with 4 or 5 arguments:
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
#### Argument rules

- `number_of_philosophers` must be at least 1.
- All arguments must be positive integers.
- `number_of_times_each_philosopher_must_eat` is optional.

## Output

The output format is:

```txt
timestamp philosopher_id action
```

Where `timestamp` is milliseconds since the simulation start.

Actions are:

- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

This produces the executable `philo`.

## Usage examples

```sh
./philo 5 800 200 200
./philo 5 800 200 200 3
```

## Source files

- `main.c` - program startup, input parsing, simulation launch, cleanup
- `parse_input.c` - argument validation
- `fork.c` - fork mutex allocation and destroy functions
- `prepare.c` - philosopher and rule initialization, thread creation
- `philo_routine.c` - philosopher thread behavior
- `monitor.c` - death and completion monitoring
- `utils.c` - timing, logging, and sleep helper
- `philo.h` - shared types and function declarations

## Implementation details

- The program uses `pthread_mutex_t` for forks and shared state.
- The monitor thread checks for death and stops the simulation.
- Output is synchronized with a print mutex to avoid interleaved messages.
- Deadlock prevention uses different fork acquisition order for odd and even philosopher IDs.

## make rules
makefile contains the following rules:
- make all
- make clean
- make fclean
- make re
## Resources
- en.subject.pdf
- https://zenn.dev/tokochiz/scraps/7d7a0323f85201
- https://qiita.com/42yliu/items/86d16cdbc584c250ca6e

### AI usage
I used AI in this project for learning about the concept of thread, data race, dead lock and so on. Also, I learned how to use pthread library functions. Furthermore, I use AI to debug codes, to find edge case, and so on.
