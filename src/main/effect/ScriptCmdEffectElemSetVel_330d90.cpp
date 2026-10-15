#include "types.h"
#include "vec.h"

typedef struct { u8 b[8]; } E8;
class VG {
public:
    u8 pad[0x190];
    virtual s32 v08();
    virtual s32 v0c();
    virtual s32 v10();
    virtual s32 v14();
    virtual s32 v18();
    virtual s32 v1c();
    virtual s32 v20();
    virtual s32 v24();
    virtual s32 v28();
    virtual s32 v2c();
    virtual s32 v30();
    virtual s32 v34();
    virtual s32 v38();
    virtual s32 v3c();
    virtual s32 v40();
    virtual s32 v44();
    virtual s32 v48();
    virtual s32 v4c();
    virtual s32 v50();
    virtual s32 v54();
    virtual s32 v58();
    virtual s32 v5c();
    virtual u8 *v60();
};

extern "C" {
f32 ScriptSlotGetFloat_334890(E8 *arg0);
s32 ScriptSlotGetInt_3348b0(E8 *arg0);
void sceVu0CopyVector(void *arg0, void *arg1);
extern VG *D_004826E0;
}

extern "C" s32 ScriptCmdEffectElemSetVel_330d90(E8 *arg0, s32 arg1)
{
    Vec4 sp50;
    s32 i;
    s32 n;
    s32 end;
    u8 *o;

    if (arg1 != 4 && arg1 != 5) return 0;
    i = ScriptSlotGetInt_3348b0(arg0++);
    o = D_004826E0->v60();
    if (o == 0) return 1;
    sp50.x = ScriptSlotGetFloat_334890(arg0++);
    sp50.y = ScriptSlotGetFloat_334890(arg0++);
    sp50.z = ScriptSlotGetFloat_334890(arg0++);
    *(s32 *)&sp50.w = 0;
    n = 1;
    if (arg1 == 5) n = ScriptSlotGetInt_3348b0(arg0);
    for (end = n + i; i < end; i++) {
        sceVu0CopyVector(o + i * 0xC0 + 0x60, &sp50);
    }
    return 1;
}
