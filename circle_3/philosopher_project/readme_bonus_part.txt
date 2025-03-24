Philosophers Bonus
This project is part of the 42 School curriculum. It consists in simulating the Dining Philosophers Problem using processes and semaphores (bonus part).
📌 Project Goals
    • Understand and implement process synchronization using POSIX semaphores 
    • Work with processes instead of threads 
    • Ensure safe access to shared resources (forks) without data races 
    • Prevent deadlocks, starvation, and handle edge cases (e.g. 1 philosopher) 
⚙️ Compilation
make
To clean object files:
make clean
To clean everything:
make fclean
To recompile:
make re
🚀 Execution
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
Example:
./philo_bonus 5 800 200 200
🧠 Implementation Summary
    • Each philosopher is a separate process (using fork()) 
    • A monitor process checks if any philosopher has died or if all have eaten enough 
    • Synchronization and communication are handled using named semaphores: 
        ◦ /forks – represents the number of available forks 
        ◦ /philo_write – ensures atomic printing 
        ◦ /philo_dead, /philo_meal, /philo_stop – control flow and completion 
    • Special handling for edge case: only 1 philosopher 
📁 File Overview
    • philo_bonus.h – Header file with data structures and function prototypes 
    • main.c – Entry point, argument validation, data & process initialization 
    • init_data.c – Initializes shared data and philosophers 
    • init_process.c – Forks philosopher and monitor processes 
    • monitor_philosophers.c – Implements the monitor process logic 
    • philosopher_routine.c – Philosopher's life cycle: eat → sleep → think 
    • open_close_semaphores.c – Opens, closes, and unlinks named semaphores 
    • utils.c – Utility functions (ft_atoi, get_time, usleep, etc.) 
✅ Bonus Requirements Covered
    • All philosophers are separate processes 
    • Semaphore used to represent forks 
    • Main process is not a philosopher 
    • Handles all edge cases correctly (e.g. 1 philosopher) 
    • Norminette-compliant and memory-safe 
📚 Resources Used
    • POSIX semaphores (man sem_open) 
    • Dining Philosophers Problem - Wikipedia 

Made with 🧠 and ☕ by rghisoiu for 42 Luxembourg

