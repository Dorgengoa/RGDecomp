/* rgp:protos */
#define RGP_SELF_MinimapInit_32a660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern const struct { f32 v; f32 pad[3]; } D_0045B078;
extern f32 D_00482B98;
extern f32 D_00482B9C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MinimapInit_32a660(void *p)
{
    u8 *q;
    void *ctx;
    s32 i;
    u8 *d;
    u32 n;
    u8 buf[0x10] __attribute__((aligned(16)));

    q = (u8 *)p;
    *(s16 *)(q + 0x10C) = -1;
    ctx = GetDrawCtx_15de80();
    DrawEnvGetWidth_1451e0(ctx);
    DrawEnvGetHeight_1451d0(ctx);
    *(q + 0x11A) = 0;
    MinimapSetScreenAnchorPos_324ca0(q, -1, -1);
    MinimapSetSizeClamped_324960(q, 0x140, 0x140);
    MinimapSetWinSize_324c50(q, 0xA0, 0x90);
    MinimapResetScroll_324900(q);
    MinimapSetBackdropPos_324a30(q, 0, 0);
    MinimapSetBackdropSize_3249b0(q, -1, -1);
    *(q + 0x11C) = 0;
    MinimapSetColor_324990(q, 0, 0, 0, 0);
    *(f32 *)(q + 0xF0) = 1.0f;
    MinimapSelectNow_32ad20(q, 0);
    MinimapRequestEntry_32ab90(q, 0);
    *(f32 *)(q + 0xDC) = 1.0f;
    *(s32 *)(q + 0xE4) = 0;
    *(s32 *)(q + 0x80) = 0;
    *(s32 *)(q + 0xC4) = 0;
    for (i = 0; i < 0x10; i++) {
        *(s32 *)(q + i * 4 + 0x84) = 0;
    }
    MinimapSetAngle_324160(q, 0.0f);
    *(s32 *)(q + 0xD0) = 0;
    d = buf;
    n = 0x10;
    if (d != 0) {
        do {
            *d = 0;
            n--;
            d++;
        } while (n != 0);
    }
    MinimapSetOrigin_323fb0(q, buf);
    *(s32 *)(q + 0x170) = 0;
    *(s32 *)(q + 0x174) = 0;
    *(s16 *)(q + 0x104) = 0;
    *(f32 *)(q + 0x164) = 1.0f;
    *(s32 *)(q + 0x160) = 0;
    *(s32 *)(q + 0x168) = 0;
    *(s32 *)(q + 0x16C) = 0;
    D_00482B98 = 3.0f * D_0045B078.v;
    D_00482B9C = D_00482B98 + D_0045B078.v;
}
