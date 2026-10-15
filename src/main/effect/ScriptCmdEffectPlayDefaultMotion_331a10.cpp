#include "types.h"

class C331 {
public:
    u8 pad[0x190];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 f();
};

typedef struct {
    s32 a;
    void *b;
    s32 c;
} It331;

extern "C" {
extern void MotionListInit_1726f0(It331 *arg0);
extern void ModelObjPlayMotionByName_1867a0(s32 arg0, s32 arg1, s32 arg2);
extern s32 EffectInstanceGetName_2dd5b0(C331 *arg0);
extern s32 ScriptSlotGetInt_3348b0(s32 arg0);
}
extern "C" C331 *D_004826E0;

extern "C" s32 ScriptCmdEffectPlayDefaultMotion_331a10(s64 *arg0, s32 arg1)
{
    s32 r;
    s32 obj;
    s32 found;
    It331 it;
    void *n;
    void *e;
    void *m;
    s32 t;

    if (arg1 <= 0 || arg1 > 3) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    r = 0;
    if (arg1 > 1) {
        r = ScriptSlotGetInt_3348b0((s32)arg0);
    }
    if (D_004826E0 == NULL) {
        return 0;
    }
    obj = D_004826E0->f();
    if (obj != 0) {
    found = 0;
    if (EffectInstanceGetName_2dd5b0(D_004826E0) != 0) {
        found = EffectInstanceGetName_2dd5b0(D_004826E0);
    } else {
        MotionListInit_1726f0(&it);
        it = *(It331 *)((u8 *)obj + 0x1F0);
        for (n = it.b; n != NULL; n = *(void **)n) {
            e = (u8 *)n + 0x10;
            if (e != NULL) {
                for (m = *(void **)((u8 *)e + 0x48); m != NULL; m = *(void **)m) {
                    t = *(s32 *)((u8 *)m + 0x18);
                    if (*(s32 *)((u8 *)m + 0x14) > 0) {
                        found = t;
                        break;
                    }
                }
            }
        }
    }
    if (found != 0) {
        ModelObjPlayMotionByName_1867a0(obj, found, r);
    }
    }
    return 1;
}
