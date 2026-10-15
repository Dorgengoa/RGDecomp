#include "types.h"

/* ConstructArray_100620 -- MSL C++ runtime __construct_array(block, ctor, dtor, size, n):
 * construct n elements of `size` bytes with ctor(p, 1); the inlined
 * __partial_array_destructor then destroys (dtor(p, -1), last to first) any
 * elements already built if construction stopped early.  The pad object is
 * address-taken, so it lives in the frame and `i` is re-read after each call.
 * Built with `-O4,p` (optimize for speed, config/toolchain.txt): that enables
 * 8-byte alignment of the join after the first loop (retail's lone nop) and
 * leaves the tail branches without branch-likely slots. */

typedef void (*CtorDtor)(void *, s32);

typedef struct {
    void *p;
    u32 size;
    u32 n;
    CtorDtor dtor;
    u32 i;
} PartialArrayDtor;

void ConstructArray_100620(void *block, CtorDtor ctor, CtorDtor dtor, u32 size, u32 n)
{
    PartialArrayDtor pad;
    PartialArrayDtor *pp = &pad;
    char *p;
    char *ptr;
    u32 i;

    pp->p = block;
    pp->size = size;
    pp->n = n;
    pp->dtor = dtor;
    pp->i = 0;
    i = pp->i;
    p = (char *)block;
    if (i < n) {
        do {
            ctor(p, 1);
            i = pp->i + 1;
            p += size;
            pp->i = i;
        } while (i < n);
    }
    if (i < pp->n && pp->dtor) {
        ptr = (char *)pp->p + pp->size * i;
        if (i != 0) {
            do {
                ptr -= pp->size;
                pp->dtor(ptr, -1);
            } while (--pp->i != 0);
        }
    }
}
