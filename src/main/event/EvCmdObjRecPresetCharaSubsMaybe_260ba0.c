#include "types.h"

extern void ObjRecClearFlag2_1c3e40(s32, s32, s32);
extern void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern s32 D_00481F78;

static inline s32 slot(s32 i, s32 k) {
    return (i >= 0 && i < 12) ? i * 4 + k : -1;
}

s32 EvCmdObjRecPresetCharaSubsMaybe_260ba0(void)
{
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    i = 0;
    do {
        a = slot(i, 0xC);
        b = slot(i, 0xD);
        c = slot(i, 0xE);
        d = slot(i, 0xF);
        ObjRecSetFlag2_1c3e80(D_00481F78, 1, a);
        ObjRecClearFlag2_1c3e40(D_00481F78, 1, b);
        ObjRecSetFlag2_1c3e80(D_00481F78, 1, c);
        ObjRecClearFlag2_1c3e40(D_00481F78, 1, d);
        i += 1;
    } while (i <= 0xb);
    ObjRecClearFlag2_1c3e40(D_00481F78, 1, 0x10);
    ObjRecSetFlag2_1c3e80(D_00481F78, 1, 0x1B);
    return 1;
}
