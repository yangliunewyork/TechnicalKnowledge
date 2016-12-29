### What is Inter-thread communication?

Inter-thread communication is a process in which a thread is paused running in its critical region and another thread is allowed to enter (or lock) in the same critical region to be executed. i.e. synchronized threads communicate with each other.

### Inter-thread communication in C++
std::condition_variable
notify_one : notifies one waiting thread 
notify_all : notifies all waiting threads 
wait:blocks the current thread until the condition variable is woken up 
wait_for : blocks the current thread until the condition variable is woken up or after the specified timeout duration 
wait_until : blocks the current thread until the condition variable is woken up or until specified time point has been reached 
