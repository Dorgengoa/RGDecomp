#include "types.h"

typedef struct {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
} Obj0026E380;

extern void GsPktWriteAD_13ec80(s32, s32, s64, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32 TextStyleHasClipRect_26f5f0(void);

void FontSetScissor_26e380(Obj0026E380 *arg0, s32 arg1) {
    s32 temp_7;

    if (arg1 != 0 && TextStyleHasClipRect_26f5f0() != 0) {
        GsPktOpenPrim_13f730(arg1, 6);
        temp_7 = arg0->unk24;
        GsPktWriteAD_13ec80(arg1, 0x40,
                     ((s64)arg0->unk30 << 0x30) |
                         (((s64)arg0->unk2C << 0x20) | (temp_7 | ((s64)arg0->unk28 << 0x10))),
                     temp_7);
        GsPktClose_13f5b0(arg1);
    }
}
