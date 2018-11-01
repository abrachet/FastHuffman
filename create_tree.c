#include "create_tree.h"
#include "typedefs.h"

extern vector_t vec;
extern vector_t reference_vec; //read only
extern InternalNode int_arr[SIZEOF_INTERNAL_QUEUE];


//insertion sort is good on small arrays
//especially when partially sorted
//TODO: most chars will be in the middle
//of the ASCII range, ie letters, 
//optimize to look on the edges first
//might be slower though

static void __attribute__((__always_inline__)) 
insertion_sort()
{
    for (int j, i = 1; i < VEC_SIZE; ++i) {
        u32 current = vec[i];

        for (j = i - 1; j >= 0 && vec[j] > current; j-- )
            vec[j + 1] = vec[j];
        
        vec[j + 1] = current;
    }
}


void __attribute__((__always_inline__)) 
create_tree()
{
    //sort vec to create tree
    insertion_sort();
    int vec_c = 0;
    int int_c = 0;

    //ignoring characters which never appear
    for (int i = 0; !vec[i]; i++ ) vec_c++;

    //InternalNode int_arr[SIZEOF_INTERNAL_QUEUE];
    int_arr[0] = (InternalNode){ .count = vec[vec_c] + vec[vec_c + 1], .left = 0, .right = 1 };
    //first two chars are always less, assign them to the first internal node

    vec_c += 2;

    //in place creation of "internal nodes" for the tree.
    //pointers left and right are uchar offsets from the start of the underlying vector, vec
    while (vec_c < VEC_SIZE) {
        if (vec[vec_c] < int_arr[int_c].count) {
            if ( vec_c != VEC_SIZE - 1 && vec[vec_c + 1] < int_arr[int_c].count) {
                int_arr[int_c + 1] = (InternalNode){.count = vec[vec_c] + vec[vec_c + 1],
                                                    .left = vec_c, .right = vec_c + 1};
                vec_c++;
            } else {
                int_arr[int_c + 1] = (InternalNode){ .count = vec[vec_c] + int_arr[int_c].count, 
                                        .left = vec_c, .right = INT_NODE_OFF(int_c) };
            }
            
        } else {
            int_arr[int_c + 1] = (InternalNode){.count = vec[vec_c] + int_arr[int_c].count,
                                                .left = INT_NODE_OFF(int_c), .right = vec_c};
        }
        
        vec_c++;
        int_c++;
    }
    int_arr[int_c + 1] = (InternalNode) {.count = int_arr[int_c].count + int_arr[int_c - 1].count,
                                         .left = INT_NODE_OFF(int_c - 1), .right = INT_NODE_OFF(int_c)};

}

