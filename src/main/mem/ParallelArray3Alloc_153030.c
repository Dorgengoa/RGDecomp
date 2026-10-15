/* ParallelArray3Alloc_153030 -- byte-identical clone of ParallelArray3Alloc_152d10 (232 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 3-member byte-identical group (232 B each):
   ParallelArray3Alloc_153030 / ParallelArray3Alloc_152ea0 / ParallelArray3Alloc_153030.
   Allocate three parallel n-element s32 arrays out of one pool, then zero
   them.  Every array pointer is RELOADED through the owner. */

struct Tri52d10 {
    s32  count;                 /* +0x00 */
    s32 *a;                     /* +0x04 */
    s32 *b;                     /* +0x08 */
    s32 *c;                     /* +0x0C */
};

extern s32 *MemStackNew_14e1b0(s32 bytes, void *pool);

s32 ParallelArray3Alloc_153030(struct Tri52d10 *t, s32 n, void *pool)
{
    s32 i;

    t->count = 0;
    t->a = MemStackNew_14e1b0(n * 4, pool);
    t->b = MemStackNew_14e1b0(n * 4, pool);
    t->c = MemStackNew_14e1b0(n * 4, pool);
    if (t->a == 0 || t->b == 0 || t->c == 0) {
        return 0;
    }
    t->count = n;
    for (i = 0; i < n; i++) {
        t->b[i] = 0;
        t->c[i] = 0;
        t->a[i] = 0;
    }
    return 1;
}
