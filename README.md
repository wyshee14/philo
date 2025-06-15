# philo
The philos sit at a rouond table with a bowl of spagetthi on the table
![Image](https://github.com/user-attachments/assets/2dec498f-8f48-4867-ad42-4d2186a017c9) \

The philosopher routine
- eat > sleep > think

The rules:
- must pick 2 forks (left and right) to eat
- take right **first**, then **left**
- after eat put the forks back on the table
- every philo must eat to avoid dying
- the program exits when a philo dies of starvation
- they dont know the status of other philo
- philo number starts from 1 to number_of_philo
- philo n must sit next to philo (n + 1) and (n - 1)
- (PROGRAM MUST NOT HAVE DATA RACE)

## What is data race?
- Data races occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior.
### Result:
- Inconsistent Data: Different threads might read different values from the same variable.
- Corrupted Data: One thread might overwrite the data being used by another thread.

## How to avoid data race?
- Using **Mutex**
- Only one thread can access the critical section (shared data) of code at a time.
- Locking a mutex before accessing shared data ensures that only one thread can access the data at a time.
- unlock it when we are done working on it.

## What is a thread?
A thread is an execution unit that has its own program counter, a stack and a set of registers that reside in a process. \
![Image](https://github.com/user-attachments/assets/7d0df3c8-979b-469f-9f9f-c08fe4bff847)

## Single thread vs Multithread
![Image](https://github.com/user-attachments/assets/3e9d0202-d9fa-4414-85be-3f114974c219)

### Arguments:
1. number_of_philo: equals to number of forks
2. time_to_die(ms): philo will die if they do not eat since the last meal or start of simulation within the time
3. time_to_eat(ms): time for philo to eat
4. time_to_sleep(ms): time the philo to sleep
5. number_of_times each philo must eat (optional): program stops when all philo eat witht the number, if not program stops when a philo die

# Function
1. int pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
- starts execution by invoking start routine
- stores the thread_ID in buffer pointed by thread
- RETURN VALUE: 0 (SUCCESS) / error number

attr (set as NULL) - is set to default

#### How it terminates:
- when calling pthread_exit
- when pthread_cancel
- any of the thread calls exit
