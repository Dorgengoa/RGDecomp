#include "types.h"

struct V {
    VC_VPTR_MEMBER;
    
    
    
    
    bool v5(s32 a0, s32 a1, void * a2) { return (vc_u8)VCM(vc_u32, (void *, s32, s32, void *), 0x1C, a0, a1, a2) != 0; }
};

struct Arg1 {
    s32 x0;
    s32 x4;
    u8 pad8[0x14];
    s32 x1C;
};

struct Obj {
    void *vptr;
    u8 pad4[4];
    s32 x8;
    u8 padC[4];
    s32 x10;
    u8 pad14[0x66];
    u8 f0 : 1;
    u8 fr : 7;
    u8 pad7b[0x19];
    Arg1 *x94;
};

extern "C" void Sprintf_1343b8(void *, s32, s32, s32);
extern "C" s32 ZoneDataSelectNameMaybe_3eff20(s32, s32);

extern "C" bool WorldSubsysZoneEntryBind_41ecb0(Obj *arg0, Arg1 *arg1, s32 arg2)
{
    u8 buf[0x80] __attribute__((aligned(16)));
    s32 h;
    s32 w;
    bool r;

    if (arg0->x10 == 0 || arg1 == 0) {
        return 0;
    }
    if (arg1->x0 == 0) {
        return 0;
    }
    if (arg1->x4 == 0) {
        return 0;
    }
    if (arg1->x1C == 0) {
        return 0;
    }
    h = ZoneDataSelectNameMaybe_3eff20(arg1->x0, arg1->x4);
    if (h == 0) {
        return 0;
    }
    w = arg0->x8;
    if (w == 0) {
        return 0;
    }
    Sprintf_1343b8(buf, w, h, h);
    arg0->f0 = true;
    arg0->x94 = 0;
    r = ((V *)arg0)->v5(arg1->x1C, arg2, buf);
    if (r) {
        arg0->x94 = arg1;
    }
    arg0->f0 = false;
    return r;
}
