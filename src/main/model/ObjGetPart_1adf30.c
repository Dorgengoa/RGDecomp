#include "types.h"

/* A negative index returns the object's own inline record at +0x120; anything
   else goes through the inlined accessor -- null check on the table pointer at
   +0x218, then the asymmetric guard pair against the count at +0x214.

   The accessor's first load sits in the OUTER guard's `bgezl` delay slot,
   which is what says it is inlined rather than called. */

typedef struct Rec50 { u8 bytes[0x50]; } Rec50;

typedef struct Owner214 {
    u8 pad000[0x120];
    u8 own[0xF4];      /* +0x120 */
    s32 count;         /* +0x214 */
    Rec50 *rec;        /* +0x218 */
} Owner214;

static inline void *lookup(Owner214 *o, s32 index)
{
    Rec50 *rec;
    u8 ok;

    rec = o->rec;
    if (rec == 0) {
        return 0;
    }
    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &rec[index];
}

void *ObjGetPart_1adf30(Owner214 *o, s32 index)
{
    if (index < 0) {
        return o->own;
    }
    return lookup(o, index);
}
