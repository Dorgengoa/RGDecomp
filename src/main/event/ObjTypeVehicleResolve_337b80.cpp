#include "types.h"

extern "C" s32 TargetRefResolve_2e5ed0(s32, s32);
extern "C" s32 TargetRefGetMapObj_2e7050(void *);
extern "C" s32 EvObjResolveTarget_2f9a60(void);
extern "C" s32 TargetRefPairResolve_338590(s32, s32);

class Obj {
    u8 pad000[0xD0];
public:
    s32 unkD0;          /* 0xD0 */
private:
    u8 padD4[0x8];      /* 0xD4-0xDC */
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual s32 slot0C();  /* vtable ptr lives at 0xDC-0xE0 */
private:
    u8 pad0E0[0x30];    /* 0xE0-0x110 */
public:
    s32 unk110;         /* 0x110 */
    s16 unk114;         /* 0x114 */
};

extern "C" s32 ObjTypeVehicleResolve_337b80(Obj *arg0)
{
    s32 var_19;
    s32 temp_18;
    s32 var_17;
    s32 var_2;
    u8 *base;

    base = (u8 *) arg0;
    EvObjResolveTarget_2f9a60();
    TargetRefResolve_2e5ed0((s32)(base + 0xE0), 0);
    var_19 = arg0->unk110;
    temp_18 = TargetRefGetMapObj_2e7050(base + 0xA0);
    var_17 = 0;
    while (var_17 < arg0->unk114) {
        TargetRefPairResolve_338590(var_19, temp_18);
        var_17 += 1;
        var_19 += 0x64;
    }
    if (!(arg0->slot0C() & 0xFF)) {
        var_2 = arg0->unkD0 & 0xFDFFFFFF;
    } else {
        var_2 = arg0->unkD0 | 0x02000000;
    }
    arg0->unkD0 = var_2;
    return 1;
}
