#include "types.h"

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} BF;

typedef struct {
    u8 pad0[0x50];
    BF bf;
    u8 pad58[4];
    s32 mode;
} O;

void GsFrameSetMaskMode_156cc0(O *o, s32 m) {
    o->mode = m;
    switch (m) {
    case 0:
        o->bf.hi = 0;
        break;
    case 1:
        o->bf.hi = 0xFF000000;
        break;
    case 2:
        o->bf.hi = 0xFFFFFF;
        break;
    case 3:
        o->bf.hi = 0xFFFF;
        break;
    case 4:
        o->bf.hi = 0xFFFFFFFF;
        break;
    default:
        o->mode = -1;
        break;
    }
}
