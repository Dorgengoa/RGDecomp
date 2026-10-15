#include "types.h"

/* Reset one record: two halfwords, two words and a byte, in that order. The
   -1 is materialised once and stored as a halfword, so the second field is
   s16 and not s32. */

typedef struct Rec002e71d0 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
    u8 padC[0x4];
    u8 unk10;
} Rec002e71d0;

void TargetRefClear_2e71d0(Rec002e71d0 *r)
{
    r->unk0 = 0;
    r->unk2 = -1;
    r->unk4 = 0;
    r->unk8 = 0;
    r->unk10 = 0;
}
