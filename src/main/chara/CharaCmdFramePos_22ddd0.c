#include "types.h"

/* The four gp-relative floats are loaded in a batch and every one of them is
   overwritten before the buffer is used; they survive DCE because the local
   ESCAPES into FrameSetPos_14a450.  A 16-byte extern leaves small data and costs a
   %hi/%lo pair, so each word is its own <=8 B gp extern. */

extern s32 ScriptArgGetInt_302d70(s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern void FrameSetPos_14a450(s32, void *);

struct Obj0 {
    s32 m00;
};

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

extern f32 D_0047E680;
extern f32 D_0047E684;
extern f32 D_0047E688;
extern f32 D_0047E68C;

s32 CharaCmdFramePos_22ddd0(struct Obj0 *p0, s32 p1, s32 argc)
{
    V4 v;
    s32 a;
    s32 b;
    s32 o;
    f32 x;
    f32 y;
    f32 z;

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
    v.x = D_0047E680;
    v.y = D_0047E684;
    v.z = D_0047E688;
    v.w = D_0047E68C;
    v.x = z;
    v.y = y;
    v.z = x;
    FrameSetPos_14a450(o, &v);
    return 1;
}
