#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x14];
    s32 unk1C;
} T41e7e0_arg1;

class V41e7e0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    bool v5(s32 a0, s32 a1, void * a2) { return (vc_u8)VCM(vc_u32, (void *, s32, s32, void *), 0x1C, a0, a1, a2) != 0; }
};

class C41e7e0 : public V41e7e0 {
public:
    u8 pad4[4];
    s32 unk8;
    u8 padC[4];
    s32 unk10;
    u8 pad14[0x80];
    T41e7e0_arg1 *unk94;
};

extern "C" void Sprintf_1343b8(void *, s32, s32, s32);
extern "C" s32 ZoneDataSelectNameMaybe_3eff20(s32, s32);

extern "C" bool WorldSubsysZoneEntryBind_41e7e0(C41e7e0 *arg0, T41e7e0_arg1 *arg1, s32 arg2)
{
    u8 sp40[0x80] __attribute__((aligned(16)));
    s32 t;
    bool r;

    if (arg0->unk10 == 0 || arg1 == 0) {
        return 0;
    }
    if (arg1->unk0 == 0) {
        return 0;
    }
    if (arg1->unk1C == 0) {
        return 0;
    }
    t = ZoneDataSelectNameMaybe_3eff20(arg1->unk0, arg1->unk4);
    if (t == 0) {
        return 0;
    }
    if (arg0->unk8 == 0) {
        return 0;
    }
    Sprintf_1343b8(sp40, arg0->unk8, t, t);
    arg0->unk94 = 0;
    r = arg0->v5(arg1->unk1C, arg2, sp40);
    if (r) {
        arg0->unk94 = arg1;
    }
    return r;
}
