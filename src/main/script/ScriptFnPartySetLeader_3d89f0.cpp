#include "types.h"

struct O3d89f0 {
    virtual void _v8();
    virtual void _vc();
    virtual void _v10();
    virtual void _v14();
    virtual void _v18();
    virtual void _v1c();
    virtual void _v20();
    virtual void _v24();
    virtual void _v28();
    virtual void _v2c();
    virtual void _v30();
    virtual void _v34();
    virtual void _v38();
    virtual void f3c();
    virtual void _v40();
    virtual void _v44();
    virtual void _v48();
    virtual void _v4c();
    virtual void _v50();
    virtual void _v54();
    virtual void _v58();
    virtual void _v5c();
    virtual void _v60();
    virtual void _v64();
    virtual void _v68();
    virtual void _v6c();
    virtual void _v70();
    virtual void _v74();
    virtual void _v78();
    virtual void _v7c();
    virtual void _v80();
    virtual void _v84();
    virtual void _v88();
    virtual void _v8c();
    virtual void _v90();
    virtual void _v94();
    virtual void _v98();
    virtual void _v9c();
    virtual void _va0();
    virtual void _va4();
    virtual void _va8();
    virtual void _vac();
    virtual void _vb0();
    virtual void _vb4();
    virtual void _vb8();
    virtual void _vbc();
    virtual s32 fc0();
    virtual void _vc4();
    virtual void _vc8();
    virtual void _vcc();
    virtual void _vd0();
    virtual void _vd4();
    virtual void _vd8();
    virtual void _vdc();
    virtual void _ve0();
    virtual void _ve4();
    virtual void _ve8();
    virtual void _vec();
    virtual void _vf0();
    virtual void ff4(s32);
};

extern "C" {
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS16_36fcc0(s32);
O3d89f0 *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 PartySetLeader_3c1600(s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
}

extern "C" void ScriptFnPartySetLeader_3d89f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    O3d89f0 *o;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    o = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)((u8 *)D_00483960 + 0x14), (s16)VariantGetS16_36fcc0(arg3), 1, 1, 0, 0, 0);
    if (o == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, PartySetLeader_3c1600(*(s32 *)((u8 *)D_00483960 + 0x18), *(s32 *)((u8 *)o + 0xC), 0) != 0, 1);
    if (o->fc0() != 0) {
        o->ff4(1);
        o->f3c();
    }
}
