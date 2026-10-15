#include "types.h"

/* the beql at 31B4 duplicates the join block's `sw $16,0x4($17)` into its
   delay slot, so `out[1] = obj` is ONE statement after the guard; the
   second guard re-tests obj. */

extern void MemStackReset_14d830(void *);
extern void *MemStackNew_14e130(s32, void *);
extern void PoolCtor_36b0c0(void *);
extern void PoolInit_36ae50(void *, void *, s32, s32, s32);
extern void DamagePopupListSetDefaultCullDist_2d3210(void *);

void DamagePopupListInit_2d3180(void **out, void *heap)
{
    void *obj;

    MemStackReset_14d830(heap);
    out[0] = heap;
    obj = MemStackNew_14e130(0x2C, heap);
    if (obj != 0) {
        PoolCtor_36b0c0(obj);
    }
    out[1] = obj;
    if (obj != 0) {
        PoolInit_36ae50(obj, out[0], 0x40, 0x80, 0x10);
        DamagePopupListSetDefaultCullDist_2d3210(out);
    }
}
