#include "types.h"
#pragma opt_rebuildconditionals off

class Obj {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual u8 v19C();
    virtual s32 v1A0();
};

extern "C" {
s32 InsectRecSlotIndexOf_3cfa70(s32, Obj *);
s32 InsectItemSatietyUnderCap_3d1510(Obj *);
s32 ItemIsKindDId514_3d4530(s32);
s32 ItemIsKindDId515_3d4570(s32);
s32 ItemIsInsectFood_3d45b0(s32);
extern s32 D_004838E8;
}

extern "C" s32 InsectItemUsable_3cf910(s32 arg0, s32 arg1, Obj *arg2, Obj *arg3)
{
    if (D_004838E8 == 0) {
        return 0;
    }
    if (arg1 == 0 || arg2 == NULL) {
        return 0;
    }
    if (InsectRecSlotIndexOf_3cfa70(arg0, arg2) < 0) {
        return 0;
    }
    if (!(u8)InsectItemSatietyUnderCap_3d1510(arg2)) {
        return 0;
    }
    if (ItemIsKindDId515_3d4570(arg1) != 0) {
        if (arg3 == NULL) {
            return 0;
        }
        if (arg2->v1A0() == 0 || arg3->v1A0() == 0) {
            return 0;
        }
        if (arg2->v19C() != arg3->v19C()) {
            goto one;
        }
        return 0;
    }
    if (ItemIsKindDId514_3d4530(arg1) != 0) {
        if (arg3 != NULL) {
            goto one;
        }
        return 0;
    }
    if (ItemIsInsectFood_3d45b0(arg1) != 0) {
        goto one;
    }
    return 0;
one:
    return 1;
}
