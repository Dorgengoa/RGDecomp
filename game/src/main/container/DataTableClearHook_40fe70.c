/* rgp:protos */
#define RGP_SELF_DataTableClearHook_40fe70 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x94];
    s32 m94;
};

void DataTableClearHook_40fe70(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m94 = 0;
    l0 = 0;
    do {
        l1 = 0;
        do {
            *(s16 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (((((l0 << 3) - l0) << 2) - ((l0 << 3) - l0)) << 2)) + (l1 << 2) + 0x98) = -1;
            *(s16 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (((((l0 << 3) - l0) << 2) - ((l0 << 3) - l0)) << 2)) + (l1 << 2) + 0x9A) = -1;
            l1 = (l1 + 1);
        } while (l1 < 0x15);
        l0 = (l0 + 1);
    } while (l0 < 0xA);
}
