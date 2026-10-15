#pragma opt_propagation off
#include "types.h"

typedef struct {
    s8 unk0;
    u8 unk1;
} Obj0026EE00;

u16 FontGlyphTableGetCount_26f660(s32);
u8 *FontGlyphTableGetCodes_26f680(s32);
/* big-endian u16 from its two bytes, low byte first */
static inline u16 mk(u8 l, u8 h)
{
    return l + (h << 8);
}

#define G(i) mk(tbl[(i) * 2 + 1], tbl[(i) * 2])

s32 FontFindCode_26ee00(s32 arg0, Obj0026EE00 *arg1)
{
    u8 *tbl;
    u16 key;
    u16 lo;
    u16 hi;
    u16 mid;
    u16 val;

    if (arg1->unk0 == 10) {
        return -2;
    }
    tbl = FontGlyphTableGetCodes_26f680(arg0);
    lo = 0;
    key = mk(arg1->unk1, arg1->unk0);
    hi = FontGlyphTableGetCount_26f660(arg0) - 1;
    val = G(0);
    if (val == key) {
        return 0;
    }
    val = G(hi);
    if (val == key) {
        return hi;
    }
    do {
        mid = (lo + hi) >> 1;
        val = G(mid);
        if (key < val) {
            hi = mid;
        } else if (val < key) {
            lo = mid;
        } else {
            return mid;
        }
    } while (hi != lo + 1);
    return -1;
}
