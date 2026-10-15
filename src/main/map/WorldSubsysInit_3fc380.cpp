#include "types.h"

/* Clone of WorldSubsysInit_3f9370 -- this group varies only in the allocation
   size, the wrapper and the flag global.

   Allocate the handler, wrap it, publish it on the owner, then fire it once.
   The `sw $2, 0x8($16)` appears twice because mwcc duplicated the single
   store into the branch-likely slot; it is one statement in source. */

class VE {
public:
    virtual void d0();
    virtual s32 v1(s32, s32, s32, s32);
};

typedef struct Owner003fc380 {
    s32   m00;
    s32   m04;
    VE   *m08;
} Owner003fc380;

/* Wider than four bytes so mwcc gives it %hi/%lo instead of a $gp load. */
extern struct { s32 v; u8 pad[0xC]; } D_00465768;

extern "C" VE *MemStackNew_14e130(s32, void *);
extern "C" VE *DataTableCtor_3fc860(VE *);

extern "C" s32 WorldSubsysInit_3fc380(Owner003fc380 *o, void *heap)
{
    VE *h;

    if (heap == 0) {
        return 0;
    }
    o->m00 = (s32)heap;
    h = MemStackNew_14e130(0x94, heap);
    if (h != 0) {
        h = DataTableCtor_3fc860(h);
    }
    o->m08 = h;
    if (h == 0) {
        return 0;
    }
    h->v1(o->m00, 0, D_00465768.v != 0, 0);
    return 1;
}
