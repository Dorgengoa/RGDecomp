/* rgp:protos */
#define RGP_SELF_GsFrameSetMaskMode_156cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    __extension__ unsigned int lo : 32;
    unsigned int  : 0, hi : 32;
} __attribute__((aligned(8))) BF;

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
