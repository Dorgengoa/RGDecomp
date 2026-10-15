#include "types.h"

/* Same shape as CharaCmdFramePos_22ddd0 but the 16-byte local is cleared by the guarded
   inline byte loop (the beqz on an obviously non-null stack address is in the
   SOURCE) instead of being seeded from the four gp floats.
   MEASURED: declaring `y` before `x` puts the FIRST cf0 result in $f20 and the
   second in $f21 - the reverse of CharaCmdFramePos_22ddd0's x,y,z order. */

extern s32 ScriptArgGetInt_302d70(s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern void FrameSetScale_14a2c0(s32, f32 *);

struct Obj0 {
    s32 m00;
};

s32 CharaCmdFrameScale_22dbf0(struct Obj0 *p0, s32 p1, s32 argc)
{
    f32 v[4];
    s32 a;
    s32 b;
    s32 o;
    f32 y;
    f32 x;
    f32 z;
    u8 *q;
    u32 n;

    if (argc != 5) {
        return 0;
    }
    a = ScriptArgGetInt_302d70(p1);
    b = ScriptArgGetStr_302cb0(p1 + 5);
    o = GetObjNodeByName_1ce3a0(p0->m00, a, b);
    if (o == 0) {
        return 1;
    }
    x = ScriptArgGetFloat_302cf0(p1 + 0x14);
    y = ScriptArgGetFloat_302cf0(p1 + 0xF);
    z = ScriptArgGetFloat_302cf0(p1 + 0xA);
    q = (u8 *)v;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    v[0] = z;
    v[1] = y;
    v[2] = x;
    FrameSetScale_14a2c0(o, v);
    return 1;
}
