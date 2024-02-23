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
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data *thread_data_arg = (struct thread_data *) thread_param;
    usleep(1000*thread_data_arg->wait_to_obtain_time);
    pthread_mutex_lock(thread_data_arg->mutex);
    usleep(1000*thread_data_arg->wait_to_release_time);
    pthread_mutex_unlock(thread_data_arg->mutex);
    thread_data_arg->thread_complete_success = true;
    return thread_data_arg;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    struct thread_data *t_data;
    t_data = (struct thread_data *) malloc(sizeof(struct thread_data));

    if(t_data == NULL)
    {
        printf("Memory allocation failed\n");
        return false;
    }

    t_data->mutex = mutex;
    t_data->wait_to_obtain_time = wait_to_obtain_ms;
    t_data->wait_to_release_time = wait_to_release_ms;

    int ret;
    ret = pthread_create(thread, NULL, threadfunc, (void *)t_data);
    if(ret != 0)
    {
        printf("Unable to create thread\n");
        return false;
    }

    else
    {
        return true;
    }

    return false;
}

