#pragma once

#include "typedefs.h"


struct thread_arg {
    u32 start;
    u32 end;
};
typedef struct thread_arg thread_arg;



void* count_worker(void*);
struct thread_arg* create_args(u16, u64);
