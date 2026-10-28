/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_354970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    s16 unk0;   /* 0x0 */
    s16 unk2;   /* 0x2 */
    u8  pad4[2];
    s16 unk6;   /* 0x6 */
    u8  pad8[0xA];
    s16 unk12;  /* 0x12 */
} Obj;

/*rgp*/
/*rgp*/
extern f32 D_0047D1FC;
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_0048236C;
extern f32 D_00482F0C;

s32 MenuGridCursorBobCb_354970(Obj *arg0)
{
    f32 t;

    t = D_00482F0C + D_0047D3B8;
    D_00482F0C = t;
    if (!(t <= 0.0f)) {
        D_00482F0C = t - D_0047D1FC;
    }
    {
        f32 s = 8.0f * Sinf_128fd0(D_00482F0C);
        UiMoveWidgetUniform_290f50(D_0048236C, 4, (s32)((f32)arg0->unk0 + s), arg0->unk2 + arg0->unk12 * arg0->unk6, 0.25f, 0);
    }
    return 1;
}
