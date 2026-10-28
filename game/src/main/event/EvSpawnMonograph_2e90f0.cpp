/* rgp:protos */
#line 1
#include "types.h"
extern "C" {
extern s32 EvMonographFncName_2e93a0(s32 xa0, void *arg0, s32 arg1, s32 arg2);
extern void *EventObjMgrCreateMonograph_2ea050(s32 arg0, s32 arg1, s32 arg2, void *arg3);
extern void ObjTypeMonographPlaceOnMapNode_372870(void *, f32, f32, s32, s32);
extern void ObjTypeMonographInitByName_372c30(void *arg0, void *arg1, s32 arg2, void *arg3, void *arg4, void *arg5);
extern void ObjTypeMonographCtor_372d20(void *arg0);
extern u8 D_004619E8[0x400];
}

class VC_2e {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER;
    
    void f(s32 a0) { VCM(void, (void *, s32), 0x10, a0); }
};

extern "C" void *EvSpawnMonograph_2e90f0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1)
{
    u8 sp160[0x40] __attribute__((aligned(16)));
    u8 sp50[0x110] __attribute__((aligned(16)));
    VC_2e *temp_2;

    if (!(EvMonographFncName_2e93a0((s32)arg0, sp160, arg1, arg2) != 0)) {
        return NULL;
    }
    ObjTypeMonographCtor_372d20(sp50);
    ObjTypeMonographInitByName_372c30(sp50, sp160, 0, D_004619E8, D_004619E8, D_004619E8);
    temp_2 = (VC_2e *)EventObjMgrCreateMonograph_2ea050(arg0, 0, 0, sp50);
    if (temp_2 == NULL) {
        return NULL;
    }
    ObjTypeMonographPlaceOnMapNode_372870(temp_2, fparg0, fparg1, arg1, arg2);
    temp_2->f(0);
    return temp_2;
}
