/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
#pragma opt_common_subs off

typedef void (*FnVt)(void *, void *);

extern "C" {
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern void *EventObjMgrFindObjByName_2e9920(s32 xa0, s32 xa1, s32);
extern void EvDoorObjSetClosed_303bb0(void *, s32);
}

class VO {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void f30(void * a0) { VCM(void, (void *, void *), 0x30, a0); }
    void f34(void * a0) { VCM(void, (void *, void *), 0x34, a0); }
};


extern "C" s32 EvDoorObjSetClosedByName_2e8d80(int rgp_a0, int rgp_a1)
{
    s32 u_0;
    s32 u_1;
    u8 sp28[8];
    VO *obj;
    s8 flag;

    obj = (VO *)EventObjMgrFindObjByName_2e9920((s32)rgp_a0, (s32)rgp_a1, 9);
    if (obj == NULL) {
        return 0;
    }
    EvDoorObjSetClosed_303bb0(obj, 1);
    *(f32 *)(sp28 + 0) = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    if ((flag = GetGameMode_1f59c0() != 6) != 0) {
        flag = GetGameMode_1f59c0() != 7;
    }
    *(s8 *)(sp28 + 4) = flag;
    obj->f30(sp28);
    obj->f34(sp28);
    return 1;
}
