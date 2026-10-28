/* rgp:protos */
#define RGP_SELF_EventSoundEntryReset_24a0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Reset one of the 0x40 slots EventSoundTableReset_249e60 sweeps. Same guard pair as
   ObjRecTableGet_1c3f60 -- shared label physically before the compute block -- with a
   constant bound and no return value, so the guards carry nothing in their
   delay slots and the outer one stays a plain `bltz` with a nop.
   ⚠ The `sll` sitting between the `b` and the compute block is DEAD code in
   the reference: it is the likely branch's delay-slot copy left stranded. */

typedef struct Slot0024a0f0 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
} Slot0024a0f0;

typedef struct Obj0024a0f0 {
    Slot0024a0f0 slot[0x40];
} Obj0024a0f0;

void EventSoundEntryReset_24a0f0(Obj0024a0f0 *self, s32 index)
{
    u8 ok;
    Slot0024a0f0 *s;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x40;
    if (ok != 0) {
        goto found;
    }
none:
    return;
found:
    s = &self->slot[index];
    s->unk0 = -1;
    s->unk4 = -1;
    s->unk8 = 1.0f;
    s->unkC = 1.0f;
    s->unk10 = 0;
}
