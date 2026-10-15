#include "types.h"

/* Four one-bit/eight-bit fields packed into one 32-bit unit, all assigned 0.
   mwcc picks the access WIDTH per field: bit 0 and bit 1 are byte accesses,
   bits 2..9 straddle a byte so it is a halfword, bits 10..17 a word.  Every
   inserted value descends from $0 through its own field mask, which is the
   `= 0` tell.  First parameter is never read - the loop counter takes $4. */

typedef struct {
    u32 f0 : 1;
    u32 f1 : 1;
    u32 f2 : 8;
    u32 f3 : 8;
} Bits9AA0;

s32 RevelationBoardCellsClear_3e9aa0(s32 unused, Bits9AA0 *p)
{
    s32 i;

    if (p == 0) {
        return 0;
    }
    for (i = 0; i < 0x1D4; i++) {
        p->f0 = 0;
        p->f1 = 0;
        p->f2 = 0;
        p->f3 = 0;
        p++;
    }
    return 1;
}
