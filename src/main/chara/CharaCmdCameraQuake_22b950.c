#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 ObjRecGetLiveObject_1c3bc0(s32, s32);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern s32 CameraShakeStart_3058c0(s32, f32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaCmdCameraQuake_22b950(s32 p0, s32 p1, s32 p2)
{
    s32 rv8;
    s32 r0;
    s32 r1;
    s32 rv7;
    f32 r2;
    f32 r3;
    f32 r4;
    f32 r5;
    s32 r6;

    if (p2 != 4) {
        rv8 = 0;
    } else {
        r0 = GetCurrentScene_1f5be0();
        r1 = ObjRecGetLiveObject_1c3bc0(r0, 1);
        rv7 = 1;
        if (r1 == 0) {
            rv7 = 0;
        } else {
            r2 = ScriptArgGetFloat_302cf0(p1);
            r3 = ScriptArgGetFloat_302cf0((p1 + 5));
            r4 = ScriptArgGetFloat_302cf0((p1 + 0xA));
            r5 = ScriptArgGetFloat_302cf0((p1 + 0xF));
            r6 = CameraShakeStart_3058c0(r1, r2, r3, r4, r5);
            rv7 = 1;
        }
        rv8 = rv7;
    }
    return rv8;
}
