#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    u8 pad0[0x10];
    u128 unk10;
    union {
        struct { f32 unk20; f32 unk24; f32 unk28; u32 unk2C; } f;
        u128 q;
    } u20;
} Obj00192FB0;

f32 VariantGetFloat_15f740(s32);                              /* extern */
extern Obj00192FB0 *D_00481304;

s32 MapSceneCfgBgColor2_192fb0(s64 *arg0) {
    if (D_00481304 == NULL) {
        return 0;
    }
    D_00481304->u20.f.unk20 = VariantGetFloat_15f740((s32)arg0++);
    D_00481304->u20.f.unk24 = VariantGetFloat_15f740((s32)arg0++);
    D_00481304->u20.f.unk28 = VariantGetFloat_15f740((s32)arg0++);
    D_00481304->u20.f.unk2C = 0x43000000;
    if ((D_00481304->u20.f.unk20 == 0.0f) && (D_00481304->u20.f.unk24 == 0.0f) && (D_00481304->u20.f.unk28 == 0.0f)) {
        D_00481304->u20.q = D_00481304->unk10;
    }
    return 1;
}
