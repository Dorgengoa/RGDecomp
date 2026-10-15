#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

extern "C" {
s32 NameTableFindByName_159fb0(s32, u8 *, s32);
s32 GetDrawCtxNameTable_15de40();
void SwordTrailTick_2d7570(u8 *, f32);
void SwordTrailStop_2d7620(u8 *);
void SwordTrailAddPoint_2d7710(u8 *, Vec *, Vec *);
bool TargetRefResolve_2e5ed0(u8 *, s32);
void TargetRefGetPos_2e6a60(u8 *, Vec *);
void TargetRefClear_2e71d0(u8 *);
}

extern "C" void SwordTrailUpdate_2158c0(u8 *arg0, f32 f) {
    bool ok;
    Vec b;
    Vec a;

    if (*(s16 *)arg0 == 0) {
        return;
    }
    ok = true;
    ok &= TargetRefResolve_2e5ed0(arg0 + 0x30, 0);
    ok &= TargetRefResolve_2e5ed0(arg0 + 0x60, 0);
    *(s32 *)(arg0 + 0xB4) = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), arg0 + 0x94, *(s32 *)(arg0 + 0x90));
    if (ok && *(s32 *)(arg0 + 0xB4) != 0) {
        TargetRefGetPos_2e6a60(arg0 + 0x30, &a);
        TargetRefGetPos_2e6a60(arg0 + 0x60, &b);
        SwordTrailAddPoint_2d7710(arg0, &a, &b);
    } else {
        TargetRefClear_2e71d0(arg0 + 0x30);
        TargetRefClear_2e71d0(arg0 + 0x60);
        SwordTrailStop_2d7620(arg0);
    }
    SwordTrailTick_2d7570(arg0, f);
}
