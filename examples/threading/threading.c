#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)


void* threadfunc(void* thread_param)
{
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    usleep((thread_func_args->wait_to_obtain_ms)*1000);
    int ret = pthread_mutex_lock(thread_func_args->mutex);
    if (ret != 0)
    {
        ERROR_LOG("pthread_mutex_lock failed with the error code %d", ret);
        (thread_func_args ->  thread_complete_success)  = false; 
        return NULL;
    }
    else
    {
        DEBUG_LOG("pthread_mutex_lock successful");
        (thread_func_args ->  thread_complete_success)  = true;
    }
    usleep((thread_func_args->wait_to_obtain_ms)*1000);
    ret = pthread_mutex_unlock(thread_func_args->mutex);
    if (ret != 0)
    {
        ERROR_LOG("pthread_mutex_unlock failed with the error code %d", ret);
        (thread_func_args ->  thread_complete_success)  = false; 
        return NULL;
    }
    else
    {
        DEBUG_LOG("pthread_mutex_unlock successful");
        (thread_func_args ->  thread_complete_success)  = true;
    }

    return thread_param;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
	// allocate memory to store thread data
	struct thread_data* thread_data_ptr = (struct thread_data*) malloc(sizeof(struct thread_data));
	thread_data_ptr->mutex = mutex;
	thread_data_ptr->wait_to_obtain_ms = wait_to_obtain_ms;
	thread_data_ptr->wait_to_release_ms = wait_to_release_ms;
	
	// create thread
	int err = pthread_create(thread, NULL, threadfunc, (void*) thread_data_ptr);
	if(err != 0) 
	{
		ERROR_LOG("Error while creating a thread");
		free(thread_data_ptr);
		return false;
	}
	
	DEBUG_LOG("Thread created");
	return true;
}
