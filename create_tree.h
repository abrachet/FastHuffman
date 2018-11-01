#pragma once

#include "typedefs.h"
/*
typedef struct {
    count_t _bool:1,
            count:15;
} if_leaf_count;

typedef struct {
    offset_t _bool:1,
             offset:7;
} if_leaf_offset;

typedef struct {
    if_leaf_offset right;
    if_leaf_offset left;
} ptrs;

typedef struct {
    union {
        if_leaf_count count;
        ptrs          _ptrs;
    };
} Node;

//"polymoorphic"
//both should have the same size and should be able to be read by any 
typedef struct {
    if_leaf_count count;
} Leaf;

typedef struct {
    if_leaf_offset right;
    if_leaf_offset left;
} Internal;
*/
/*
//can be cast to Internal
//8 + 8 + 32

typedef u64 internal_td;
#define SIZEOF_INTERNAL (32)



#define INTERNAL (1)
#define LEAF (0)

#define __MASK 0x40

#define IF_LEAF(node) (node & __MASK) ? INTERNAL : LEAF
*/

#define SIZEOF_INTERNAL_QUEUE ((VEC_SIZE) - 1)

#define INT_NODE_OFF(off) off + VEC_SIZE

#define IF_LEAF(ptr_off)     (ptr_off <= VEC_SIZE) ? 1 : 0
#define IF_INT_NODE(ptr_off) (ptr_off >  VEC_SIZE) ? 1 : 0

typedef struct {
    count_t  count;
    offset_t right;
    offset_t left;
} InternalNode;



void __attribute__((__always_inline__)) insertion_sort();
void __attribute__((__always_inline__)) create_tree();
