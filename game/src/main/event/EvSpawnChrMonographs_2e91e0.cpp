/* rgp:protos */
#line 1
#include "types.h"

class Eff {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER;
    
    void v10(s32 a0) { VCM(void, (void *, s32), 0x10, a0); }
};

struct Ent {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    f32 f10;
};

extern "C" {
extern s32 *ModelGetFrame_1511f0(void *arg0, s32 arg1);
extern Ent *ObjFindNthAttachPoint_1addc0(void *arg0, s32 arg1, s32 arg2);
extern void *ObjRecGetLiveObject_1c4a90(void *arg0, s32 arg1);
extern void *GetCurrentScene_1f5be0(void);
extern s32 EvMonographChrName_2e93f0(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern Eff *EventObjMgrCreateMonograph_2ea050(s32 arg0, s32 arg1, s32 arg2, void *arg3);
extern void ObjTypeMonographSetTargetCharaMaybe_372950(Eff *, s32, f32, f32, s32);
extern void ObjTypeMonographInitByName_372c30(void *arg0, void *arg1, s32 arg2, void *arg3, void *arg4, void *arg5);
extern void ObjTypeMonographCtor_372d20(void *arg0);
extern f32 D_0045B080[4];
extern u8 D_004619E8[];
extern f32 D_0047D1DC;
}

extern "C" s32 EvSpawnChrMonographs_2e91e0(s32 arg0, s32 arg1, f32 base, f32 step)
{
    u8 sp1B0[0x40] __attribute__((aligned(16)));
    u8 spA0[0x110] __attribute__((aligned(16)));
    void *obj;
    s32 i;
    s32 *id;
    f32 scale;
    Eff *eff;
    Ent *e;
    s32 n;

    obj = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), arg1);
    if (obj == 0) {
        return 0;
    }
    i = 0;
    n = 0;
    { f32 a = *(volatile f32 *)&D_0045B080[0]; scale = D_0047D1DC * a; }
    while ((e = ObjFindNthAttachPoint_1addc0(obj, 0xA0, i)) != 0) {
        i++;
        if (e->fC == 0) continue;
        id = ModelGetFrame_1511f0(obj, e->f0);
        if (id == 0) continue;
        if (EvMonographChrName_2e93f0(arg0, sp1B0, arg1, *id) == 0) continue;
        ObjTypeMonographCtor_372d20(spA0);
        ObjTypeMonographInitByName_372c30(spA0, sp1B0, 0, D_004619E8, D_004619E8, D_004619E8);
        eff = EventObjMgrCreateMonograph_2ea050(arg0, 0, 0, spA0);
        if (eff == 0) continue;
        ObjTypeMonographSetTargetCharaMaybe_372950(eff, arg1, e->f10 * scale - 17.5f, base + step * (f32)n, *id);
        eff->v10(0);
        n++;
    }
    return i > 0;
}
