#include <stdlib.h>
#include <stdio.h>

#include <pthread/pthread.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "typedefs.h"

#include "count_worker.h"
#include "create_tree.h"

pthread_mutex_t lock;
vector_t vec;

vector_t reference_vec;

InternalNode int_arr[SIZEOF_INTERNAL_QUEUE];

char* restrict _file;

int main(int argc, char** argv) 
{
    int filedes = open(argv[1], O_RDONLY);
    struct stat _stat;

    fstat(filedes, &_stat);

    _file = mmap(NULL, _stat.st_size, PROT_READ, MAP_SHARED, filedes, 0);
    if (_file == MAP_FAILED) {
        perror("");
        return EXIT_FAILURE;
    }

    #ifndef NDEBUG
    printf("filesize is: %lld\n", _stat.st_size);
    #endif


    int partition = strtol(argv[2], NULL, 10);
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_t* tids = alloca(sizeof(pthread_t) * partition);
    thread_arg* args = create_args(partition, _stat.st_size);


    #ifndef NDEBUG
    for (int i = 0; i < partition; i++) 
        printf("args[%d] is .start:%d .end:%d\n", i, args[i].start, args[i].end);
    #endif

    for (int i = 0; i < partition; i++)
        pthread_create(tids + i, &attr, count_worker, args + i);

    for (int i = 0; i < partition; i++)
        pthread_join(tids[i], NULL);
    
    reference_vec = vec;

    #ifndef NDEBUG
    puts("\n\n\n================\nFrom main");
    for (int i = 47; i < 122; i++)
        printf("%c appears %u\n", i, vec[i]);
    #endif

    insertion_sort();
    //create_tree();

    int arb_break = 1;
    arb_break++;
}
