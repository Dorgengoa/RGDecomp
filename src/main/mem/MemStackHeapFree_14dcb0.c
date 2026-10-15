#include "types.h"

/* Unlink a node from a doubly-linked list, after stepping BACK from the
   payload to the header: the word just below the pointer is a count of
   16-byte units to subtract. The first parameter is never read -- this is a
   member function whose `this` the body does not need. */

typedef struct Link {
    struct Link *a;    /* +0x00 */
    struct Link *b;    /* +0x04 */
} Link;

void MemStackHeapFree_14dcb0(void *self, Link *p)
{
    if (p == 0) {
        return;
    }
    p = (Link *)((u8 *)p - *((s32 *)p - 1) * 16);
    p->b->a = p->a;
    p->a->b = p->b;
}
