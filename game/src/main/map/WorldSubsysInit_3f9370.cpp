#include "types.h"

/* Allocate the handler, wrap it, publish it on the owner, then fire it once.
   The `sw $2, 0x8($16)` appears twice because mwcc duplicated the single
   store into the branch-likely slot; it is one statement in source. */

class VE {
public:
    VC_VPTR_MEMBER;
    s32 v1(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(s32, (void *, s32, s32, s32, s32), 0xC, a0, a1, a2, a3); }
};

typedef struct Owner3f9370 {
    s32   m00;
    s32   m04;
    VE   *m08;
} Owner3f9370;

/* Wider than four bytes so mwcc gives it %hi/%lo instead of a $gp load. */
extern "C" struct rgp_anon_D_00465750 { s32 v; u8 pad[0xC]; } D_00465750;

extern "C" VE *MemStackNew_14e130(s32, void *);
extern "C" VE *DataTableCtor_3f9840(VE *);

extern "C" s32 WorldSubsysInit_3f9370(Owner3f9370 *o, void *heap)
{
    VE *h;

    if (heap == 0) {
        return 0;
    }
    o->m00 = (s32)heap;
    h = MemStackNew_14e130(0xD4, heap);
    if (h != 0) {
        h = DataTableCtor_3f9840(h);
    }
    o->m08 = h;
    if (h == 0) {
        return 0;
    }
    h->v1(o->m00, 0, D_00465750.v != 0, 0);
    return 1;
}
