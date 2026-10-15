/* PARKED s17b: m2c fails outright (jump table not provided). Not attempted. */
/* s49m: MATCH (jtbl, rodata_check) */
#include "types.h"

typedef struct Pad {
    u32 lo : 13;
    u32 btn : 8;
    u32 hi : 11;
} Pad;

extern s32 RevelationBoardCellDirBits_409db0(Pad *);

s32 RevelationBoardCellLinkMask_409b50(Pad *o, s32 idx, u8 *out)
{
    s32 r;
    s32 res;
    u32 b;

    if (idx < 0 || idx > 7) {
        return 0xFF;
    }
    *out = 0;
    r = RevelationBoardCellDirBits_409db0(o);
    if (r == 0) {
        return 0xFF;
    }
    if (r == 3) {
        *out = 1;
    }
    res = 0;
    switch (idx) {
    case 0:
        b = o->btn;
        res = res | ((b & 0x2) ? 0x10 : 0);
        res = res | ((b & 0x8) ? 0x40 : 0);
        break;
    case 1:
        b = o->btn;
        res = res | ((b & 0x1) ? 0x8 : 0);
        res = res | ((b & 0x4) ? 0x10 : 0);
        break;
    case 2:
        b = o->btn;
        res = res | ((b & 0x2) ? 0x8 : 0);
        res = res | ((b & 0x10) ? 0x40 : 0);
        break;
    case 3:
        b = o->btn;
        res = res | ((b & 0x1) ? 0x2 : 0);
        res = res | ((b & 0x20) ? 0x40 : 0);
        break;
    case 4:
        b = o->btn;
        res = res | ((b & 0x4) ? 0x2 : 0);
        res = res | ((b & 0x80) ? 0x40 : 0);
        break;
    case 5:
        b = o->btn;
        res = res | ((b & 0x40) ? 0x10 : 0);
        res = res | ((b & 0x8) ? 0x1 : 0);
        break;
    case 6:
        b = o->btn;
        res = res | ((b & 0x20) ? 0x8 : 0);
        res = res | ((b & 0x80) ? 0x10 : 0);
        break;
    case 7:
        b = o->btn;
        res = res | ((b & 0x40) ? 0x8 : 0);
        res = res | ((b & 0x10) ? 0x1 : 0);
        break;
    }
    return res;
}
