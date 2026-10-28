/* rgp:protos */
#line 1
#include "types.h"

class Obj002f8c20 {
public:
    u8 pad0[0xA0];
    u8 unkA0[0xD0 - 0xA0];
    s32 unkD0;
    u8 padD4[0xDC - 0xD4];
public:
    VC_VPTR_MEMBER;
    
    
    s32 f14() { return VCM0(s32, 0x14); }
    
    
    
    
    void f28() { VCM0(void, 0x28); }
    s16 unkE0;
    f32 unkE4;
};

struct Obj002E7050_002F8C20 {
    u8 pad0[0x32];
    s16 unk32;
    u8 pad34[0x64 - 0x34];
    f32 unk64;
};

extern "C" {
s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
s32 MapDataIsLoadedOrUnloading_1e7980(s32);
s32 MapDataIsLoaded_1e79d0(s32);
s32 GetMapMgr_201a90();
Obj002E7050_002F8C20 *TargetRefGetMapObj_2e7050(void *);
s32 EvObjGetAreaId_2f8f30(Obj002f8c20 *);
s32 EvObjAreaFadeIsAreaLoaded_2f8f40(Obj002f8c20 *);
}

extern "C" void EvObjAreaFadeUpdate_2f8c20(Obj002f8c20 *arg0)
{
    bool flag;
    s32 b;
    s32 d;
    s32 r;
    s32 v;
    Obj002E7050_002F8C20 *o;

    d = arg0->unkD0;
    if (!(d & 0x8000)) {
        return;
    }
    flag = false;
    b = ((d & 0x80000000) != 0) ^ 1;
    if (b) {
        if (arg0->f14() != 0) {
            r = MapSlotsFindBlockById_1e49b0(GetMapMgr_201a90(), ((short)EvObjGetAreaId_2f8f30(arg0)), 0);
            if (r == 0 || ((unsigned char)MapDataIsLoadedOrUnloading_1e7980(r)) == 0) {
                flag = true;
            } else if (((unsigned char)MapDataIsLoaded_1e79d0(r)) != 0) {
                arg0->unkE0 = 1;
            } else {
                arg0->unkE0 = 0;
            }
            switch (((short)EvObjAreaFadeIsAreaLoaded_2f8f40(arg0))) {
            case 0:
                arg0->unkE4 = arg0->unkE4 + 0.03125f;
                break;
            case 1:
                arg0->unkE4 = arg0->unkE4 - 0.03125f;
                break;
            }
            if (arg0->unkE4 < 0.0f) {
                arg0->unkE4 = 0.0f;
            }
            if (!(arg0->unkE4 <= 1.0f)) {
                arg0->unkE4 = 1.0f;
            }
        } else {
            flag = true;
        }
    } else {
        flag = true;
    }
    if (flag) {
        arg0->f28();
    }
    if (arg0->f14() != 0) {
        o = TargetRefGetMapObj_2e7050(arg0->unkA0);
        v = 1;
        if (arg0->unkE4 <= 0.0f) {
            v = 0;
        }
        o->unk32 = (s16)((v & 0xFF) != 0);
        o->unk64 = arg0->unkE4;
    }
}
