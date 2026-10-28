/* rgp:protos */
#line 1
#include "types.h"

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 a() { return VCM0(s16, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 b() { return VCM0(s32, 0x33C); }
};

struct S3e2d80 {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 pad4[8];
    s32 unkC;
    s16 unk10;
    s32 unk14;
    VC *unk18;
    s16 unk1C;
    s32 unk20;
};
struct O3e2d80 { u8 pad0[0x6C]; s32 unk6C; };

extern "C" {
extern void ActionPacketClear_3e3e90(void *);
extern s32 GroupGetRecordById_41c2a0(s32, long long, long long, s32);
extern O3e2d80 *D_00483994;

S3e2d80 *ActionPacketInitCharaInteractMaybe_3e2d80(S3e2d80 *arg0, s32 arg1, VC *arg2, s32 arg3, s32 arg4) {
    s32 t;

    if (arg2 == 0) {
        return 0;
    }
    ActionPacketClear_3e3e90((void *)arg0);
    arg0->unk2 = 7;
    arg0->unk0 = 1;
    if (arg4 != 0) {
        arg0->unk3 = 0x27;
        arg0->unk0 = 2;
    } else {
        arg0->unk3 = 0x28;
        arg0->unk0 = 2;
    }
    arg0->unkC = arg1;
    t = GroupGetRecordById_41c2a0(D_00483994->unk6C, (long long)(arg3), (long long)(-1), 0);
    if (t == 0) {
        return 0;
    }
    arg0->unk10 = arg2->a();
    arg0->unk14 = arg2->b();
    arg0->unk18 = arg2;
    arg0->unk1C = arg3;
    arg0->unk20 = t;
    return arg0;
}
}
