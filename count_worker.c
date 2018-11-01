#include <pthread/pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "count_worker.h"


extern pthread_mutex_t lock;
extern vector_t vec;

extern char* restrict _file;

struct thread_arg* create_args(u16 partition, u64 filesize)
{
    thread_arg* arr = malloc(sizeof(thread_arg) * partition);

    u32 average = filesize / partition;
    int prev = 0;

    
    for (int i = 0; i < partition - 1; i++) {
        arr[i].start = prev;
        prev += average;
        arr[i].end = prev;
    }

    arr[partition - 1].start = prev;
    arr[partition - 1].end = filesize;

    return arr;
}


void* count_worker(void* arg)
{
    vector_t thread_vec;
    #pragma clang loop vectorize_width(8) interleave_count(8)
    for (int i = ((thread_arg*)arg)->start; i < ((thread_arg*)arg)->end; i++ )
        thread_vec[(int)_file[i]] += 1;


    pthread_mutex_lock(&lock);
    vec = vec + thread_vec;
    pthread_mutex_unlock(&lock);

    return 0;
}
