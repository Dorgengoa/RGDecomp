/* rgp:protos */
#define RGP_SELF_EventObjMgrGetTypeList_2e9d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Bounds-checked lookup into a 16-entry table of 0x10-byte records at +0x50.

   THE ASYMMETRIC GUARD PAIR, verbatim from the recipe in
   src/world/ObjRecTableGet_1c3f60.c: both guards `goto` the SAME label and the label
   goes PHYSICALLY BEFORE the compute block, which then needs its own `goto`.
   The only difference from that site is the bound, which is a CONSTANT here
   rather than a field -- so retail spells it `slti` instead of `lw`/`slt`. */

typedef struct Owner50 {
    u8 pad000[0x50];
    u8 rec[1];         /* +0x50, 0x10 bytes each, 16 of them */
} Owner50;

void *EventObjMgrGetTypeList_2e9d60(Owner50 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x10;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x10];
}
