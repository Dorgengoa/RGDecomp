#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj {
    u8 pad000[0x4FC];
    s32 m4FC;
};

extern s32 ScriptSlotGetInt_3348b0(E8 *);
extern f32 ScriptSlotGetFloat_334890(E8 *);
extern s32 GetCurrentScene_1f5be0(void);
extern struct Obj *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, f32, s32);

s32 ScriptCmdObjPlaySound_32d090(E8 *p0, s32 p1)
{
    s32 a;
    s32 b;
    f32 t;
    s32 r;
    struct Obj *o;

    if (p1 <= 0) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0(p0);
    b = ScriptSlotGetInt_3348b0(p0 + 1);
    t = 1.0f;
    if (p1 > 2) {
        t = ScriptSlotGetFloat_334890(p0 + 2);
    }
    r = GetCurrentScene_1f5be0();
    o = ObjRecGetLiveObject_1c4a90(r, a);
    if (o == 0) {
        return 1;
    }
    SoundPlayScaledVolume_1b9520(o->m4FC, b, t, 0);
    return 1;
}
