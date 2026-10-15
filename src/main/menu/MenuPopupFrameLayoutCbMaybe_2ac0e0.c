#include "types.h"

typedef struct P_FUN_002ac0e0 {
    u8 pad000[0x12];
    s16 m12;
} P_FUN_002ac0e0;

extern void *D_00482360;

extern void *UiGetWidgetSprite_28fe10(void *ctx, s32 a, s32 b);
extern void UiLayoutWindowFrame_28b8e0(void *w, s32 a, s32 b, s32 c);
extern void UiSetSpriteW_28fbf0(void *ctx, s32 a, s32 b, s32 c);
extern void UiSetSpriteUvW_28f850(void *ctx, s32 a, s32 b, s32 c);
extern void UiSetSpritePos_28fd10(void *ctx, s32 a, s32 b, s32 c, s32 d);

s32 MenuPopupFrameLayoutCbMaybe_2ac0e0(P_FUN_002ac0e0 *p)
{
    void *w;

    w = UiGetWidgetSprite_28fe10(D_00482360, 0x89, 0);
    if (w == 0) return 0;
    UiLayoutWindowFrame_28b8e0(w, 0xE8, 0x59, 3);
    UiSetSpriteW_28fbf0(D_00482360, 0x89, 0, p->m12 + 4);
    UiSetSpriteUvW_28f850(D_00482360, 0x89, 0, p->m12 + 4);
    UiSetSpritePos_28fd10(D_00482360, 0x7D, 0xB8, p->m12 * 27 + 0xB2, 0);
    return 1;
}
