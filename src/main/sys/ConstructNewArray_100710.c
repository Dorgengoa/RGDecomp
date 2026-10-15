#include "types.h"

/* ConstructNewArray_100710 -- MSL C++ runtime __construct_new_array(block, ctor, dtor, size, n):
 * writes the array header {size, n, dtor} at block, then constructs n elements of
 * `size` bytes at block+16 with ctor(p, 1); the inlined __partial_array_destructor
 * destroys (dtor(p, -1), last to first) any elements already built if construction
 * stopped early.  The pad object is address-taken, so it lives in the frame.
 * Built with `-O4,p` (optimize for speed, config/toolchain.txt row): that leaves
 * the lone nop after the first loop and no branch-likely slots in the tail.
 * Returns block+16 (or 0 for a null block). */

typedef void (*CtorDtor)(void *, s32);

typedef struct {
    void *p;
    u32 size;
    u32 n;
    CtorDtor dtor;
    u32 i;
} PartialArrayDtor;

void *ConstructNewArray_100710(void *block, CtorDtor ctor, CtorDtor dtor, u32 size, u32 n)
{
    PartialArrayDtor pad;
    PartialArrayDtor *pp;
    char *ptr;
    char *p;
    char *q;
    u32 i;

    if ((ptr = (char *)block) != 0) {
        ((u32 *)ptr)[0] = size;
        ((u32 *)ptr)[1] = n;
        ((u32 *)ptr)[2] = (u32)dtor;
        ptr += 16;
        if (ctor) {
            pp = &pad;
            p = ptr;
            pp->p = ptr;
            pp->size = size;
            pp->n = n;
            pp->dtor = dtor;
            pp->i = 0;
            i = pp->i;
            if (i < n) {
                do {
                    ctor(p, 1);
                    i = pp->i + 1;
                    p += size;
                    pp->i = i;
                } while (i < n);
            }
            if (i < pp->n && pp->dtor) {
                q = (char *)pp->p + pp->size * i;
                if (i != 0) {
                    do {
                        q -= pp->size;
                        pp->dtor(q, -1);
                    } while (--pp->i != 0);
                }
            }
        }
    }
    return ptr;
}
