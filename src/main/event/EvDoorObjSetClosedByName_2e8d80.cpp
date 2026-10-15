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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void f30(void *);
    virtual void f34(void *);
};


extern "C" s32 EvDoorObjSetClosedByName_2e8d80(void)
{
    s32 u_0;
    s32 u_1;
    u8 sp28[8];
    VO *obj;
    s8 flag;

    obj = (VO *)EventObjMgrFindObjByName_2e9920(u_0, u_1, 9);
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
