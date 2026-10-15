/* PARKED s15i: m2c draft references an unresolved pseudo-variable (`sp5C`)
 * compared against a global float, inside a fairly large state-machine
 * function; 0 round trips spent. Needs asm/matchings/main/LoadingIconStep_2ee740.s
 * read by hand to identify sp5C (likely a field of the sp50 struct passed
 * to ScreenFadeGetColor_1cf660). Not attempted. */
/* s49m: MATCH */
#include "types.h"
#undef NULL
#define NULL 0

typedef struct { f32 x, y, z, w; } V4;

extern "C" u8 D_00482788;
extern "C" f32 D_00482790;
extern "C" u8 D_0048278C;
extern "C" f32 D_00482794;
extern "C" f32 D_0047D890;
extern "C" s32 D_00461AC0[16];
extern "C" u8 D_00461AC8[];
extern "C" u8 *GetGameData_1fede0(void);
extern "C" s32 StateFlagTest_3ccd70(s32, s32);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" s32 GetDrawCtx_15de80(void);
extern "C" u8 *GetReadBuffHeap_2025e0(void);
extern "C" f32 DrawCtxGetFrameTime_144120(s32);
extern "C" void ScreenFadeGetColor_1cf660(s32, V4 *);
extern "C" u8 TaskIsEnabled_27c2c0(void *);
extern "C" f32 LoadingIconGetTime_2ee9a0(void);
extern "C" s32 GetLoaderMgr_1f59d0(void);
extern "C" s32 LoaderCountQueued_1cd620(s32);

extern "C" void LoadingIconStep_2ee740(void)
{
    V4 sp50;
    s32 a;
    s32 b;
    u8 *c;
    f32 dt;
    f32 y;
    s32 r;
    bool ok;

    if (D_00482788 == 0) {
        D_00482790 = 0.0f;
        D_0048278C = 0;
        return;
    }
    if (StateFlagTest_3ccd70(*(s32 *)(GetGameData_1fede0() + 0x10), 0x7E2) != 0) {
        D_00482790 = 0.0f;
        D_0048278C = 0;
        return;
    }
    a = GetCurrentScene_1f5be0();
    b = GetDrawCtx_15de80();
    c = GetReadBuffHeap_2025e0();
    dt = DrawCtxGetFrameTime_144120(b) / 2.0f;
    ScreenFadeGetColor_1cf660(a, &sp50);
    y = sp50.w;
    r = TaskIsEnabled_27c2c0(D_00461AC8);
    ok = true;
    if (y < D_0047D890 || r == 0) {
        if (!(D_00482790 < 90.0f)) {
            if (!(D_00482794 < (f32)D_00461AC0[0])) {
                ok = false;
            } else {
                D_00482794 = D_00482794 + dt;
            }
        } else {
            ok = false;
        }
    }
    if (!ok) {
        D_00482790 = 0.0f;
        D_0048278C = 0;
        return;
    }
    D_00482790 = D_00482790 + dt;
    if (D_0048278C != 0) {
        return;
    }
    if (LoadingIconGetTime_2ee9a0() <= 0.0f) {
        return;
    }
    if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) >= 12
        || *(s32 *)(c + 0x34) - *(s32 *)(c + 0x2C) < 0x140001) {
        D_00482790 = 90.0f + dt;
        D_00482794 = 0.0f;
        D_0048278C = 1;
    }
}
