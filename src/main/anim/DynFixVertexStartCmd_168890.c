#include "types.h"

extern s32 VariantGetInt_15f780(s64 *arg0);
extern s32 MemStackAllocQw_14d950(s32 arg0, u32 arg1);
extern void memset(s32, s32, s32);
extern u8 *D_00481154;
extern s32 D_00481158;

s32 DynFixVertexStartCmd_168890(s64 *arg0, s32 arg1) {
    s32 i;
    s32 c;
    s32 d;
    u32 t;
    u32 n;
    u8 *p;

    VariantGetInt_15f780(arg0++);
    p = D_00481154;
    d = D_00481158;
    c = *(s32 *)(p + 0xA0);
    *(s32 *)(p + 0xBC) = c;
    t = c << 5;
    if (t & 0xF) {
        n = (t >> 4) + 1;
    } else {
        n = t >> 4;
    }
    *(s32 *)(p + 0xC0) = MemStackAllocQw_14d950(d, n);
    for (i = 0; i < *(s32 *)(p + 0xA0); i++) {
        memset(*(s32 *)(p + 0xC0) + (i << 5), 0, 0x20);
    }
    if (arg1 >= 2) {
        *(s32 *)(D_00481154 + 0x118) = VariantGetInt_15f780(arg0);
    }
    return 1;
}
