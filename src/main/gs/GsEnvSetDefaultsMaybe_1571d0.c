#include "types.h"
#pragma optimization_level 3
typedef struct {
    u8 pad0[0x10];
    s64 unk10;
    u8 pad18[0x20 - 0x18];
    u16 a : 1;
    u16 b : 3;
    u16 c : 8;
    u16 pad20 : 2;
    u16 d : 1;
    u16 e : 1;
    u8 f : 1;
    u8 g : 2;
    u8 pad22 : 5;
    u8 pad23[0x40 - 0x23];
    u8 h : 1;
    u8 pad40 : 7;
    u8 pad41[0x5C - 0x41];
    s32 unk5C;
} Obj001571D0;

extern s64 D_00449EF8[];

void GsEnvSetDefaultsMaybe_1571d0(Obj001571D0 *arg0) {
    s32 z;

    arg0->unk10 = D_00449EF8[0];
    z = 0;
    arg0->a = 1;
    arg0->b = 5;
    arg0->c = z;
    arg0->c = 1;
    arg0->d = z;
    arg0->e = z;
    arg0->f = 1;
    arg0->g = 2;
    arg0->h = z;
    arg0->unk5C = -1;
    arg0->unk5C = -1;
}
