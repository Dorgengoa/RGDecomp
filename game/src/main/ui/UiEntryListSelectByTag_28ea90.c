/* rgp:protos */
#define RGP_SELF_UiEntryListSelectByTag_28ea90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Hub function, called from many already-merged src/ files -- their
   extern declarations pin the signature as (void ptr or s32, s32, s32)
   returning s32 (some callers discard the return value).  arg0 begins
   with the same layout UiEntryListFindByTag_28ea40 reads (a Head0028ea40), plus its own
   fields at +0xC (the found-slot pointer), +0x10 and +0x1C. */

struct Slot0028ea40 {
    void *f0;
    u8 pad4[0x1C];
};

struct Obj0028ea90 {
    u8 pad0[0xC];
    struct Slot0028ea40 *fC;
    s32 f10;
    u8 pad14[8];
    s32 f1C;
};

struct Val0028ea90 {
    u8 pad0[0x2C];
    s32 (*fn)(void *, s32);
};

/*rgp*/
/*rgp*/

s32 UiEntryListSelectByTag_28ea90(struct Obj0028ea90 *arg0, s32 arg1, s32 arg2)
{
    struct Slot0028ea40 *slot;
    struct Val0028ea90 *val;

    slot = ((struct Slot0028ea40 *)UiEntryListFindByTag_28ea40(arg0, arg1));
    if (slot == 0) {
        return 0;
    }
    arg0->fC = slot;
    arg0->f1C = 0;
    if (arg2 != 0) {
        UiEntryListResetEntryRect_28eb40(arg0, slot);
    }
    slot = arg0->fC;
    val = slot->f0;
    if (val->fn != 0) {
        val->fn((u8 *)slot + 4, arg0->f10);
    }
    return 1;
}
