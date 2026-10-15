#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj0 {
    s32 m00;
};

extern struct Obj0 * gEventContext;
extern s32 ScriptGetInt_2490f0(E8 *);
extern f32 TaggedGetFloat_2490d0(E8 *);
extern void ScreenFadeSetOverlayMaybe_1cf540(s32, s32, s32, s32);
extern void ScreenFadeSetOverlayZoomMaybe_1cf530(s32, f32, f32, f32);

s32 EvCmdScreenFadeSetOverlayZoomMaybe_246ba0(E8 *p0, s32 p1)
{
    s32 x;
    f32 t;
    s32 y;
    s32 a;

    x = 0x100;
    t = 1.0f;
    y = 0xE0;
    a = ScriptGetInt_2490f0(p0);
    if (p1 > 1) {
        t = TaggedGetFloat_2490d0(p0 + 1);
    }
    if (p1 > 2) {
        x = ScriptGetInt_2490f0(p0 + 2);
    }
    if (p1 > 3) {
        y = ScriptGetInt_2490f0(p0 + 3);
    }
    ScreenFadeSetOverlayMaybe_1cf540(gEventContext->m00, a, 0, 0);
    ScreenFadeSetOverlayZoomMaybe_1cf530(gEventContext->m00, t, (f32)x, (f32)y);
    return 1;
}
