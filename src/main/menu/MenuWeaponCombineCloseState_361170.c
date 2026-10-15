#include "types.h"

typedef struct {
    u8 pad0[0x83];
    s8 unk83;
    s32 unk84;
    u8 pad88[4];
    s32 unk8C;
} Mgr;

extern void ModelSetScale_150ff0(void *, f32 *);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern f32 GetSceneTimeStep_293350(void);
extern f32 D_0047D610;
extern f32 D_0047F8A0;
extern f32 D_0047F8A4;
extern Mgr *D_00482384;
extern s8 D_004823CC;
extern u8 *D_004823D0;
extern s32 D_0048303C;

static inline void clear(u8 *q, u32 n)
{
    if (q) {
        for (; n != 0; n--) {
            *q++ = 0;
        }
    }
}

s32 MenuWeaponCombineCloseState_361170(s32 arg0, s32 arg1)
{
    f32 v[4];
    f32 d;
    f32 t;
    f32 x;
    u8 *m;

    if (arg1 != 0) {
        D_0048303C = -1;
    }
    switch (D_0048303C) {
    case -1:
        D_0048303C = 0;
        D_0047F8A0 = 1.0f;
        D_0047F8A4 = 1.0f;
        if (!(UiGetWidgetAlpha_290770(D_00482384->unk84, 0x1E7) < 1.0f)) {
            UiFadeWidgetAlpha_290690(D_00482384->unk84, 0x1E7, 0.0f, 0.0625f, -1.0f);
        }
        break;
    case 0:
        d = D_0047D610 * GetSceneTimeStep_293350();
        t = D_0047F8A0 - d;
        D_0047F8A4 = D_0047F8A4 - d;
        D_0047F8A0 = t;
        if (t < 0.0f) {
            D_0047F8A0 = 0.0f;
        }
        if (D_0047F8A4 < 0.0f) {
            D_0047F8A4 = 0.0f;
        }
        x = D_0047F8A0;
        m = D_004823D0;
        clear((u8 *)v, sizeof(v));
        v[0] = x;
        v[1] = x;
        v[2] = x;
        ModelSetScale_150ff0(m, v);
        *(f32 *)(D_004823D0 + 0x170) = D_0047F8A4;
        if (D_0047F8A0 <= 0.0f && D_0047F8A4 <= 0.0f) {
            D_0048303C = 1;
        }
        break;
    case 1:
        UiSetWidgetVisible_290010(D_00482384->unk84, 0x1E7, 0, -1);
        D_004823CC = 0;
        StateMachineSetState_28ede0(D_00482384->unk8C, 9, 0);
        D_00482384->unk83 = 0;
        break;
    }
    return 1;
}
