/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v60() { return VCM0(s32, 0x60); }
    s32 v64() { return VCM0(s32, 0x64); }
    
    
    s32 v70(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
    
    
    
    
    
    
    
    s32 v90(s32 a0) { return VCM(s32, (void *, s32), 0x90, a0); }
    s32 v94(s32 a0) { return VCM(s32, (void *, s32), 0x94, a0); }
    
    
    
    
    u8 vA8(int rgp_fwd1 = 0) { return VCM(u8, (void *, int), 0xA8, rgp_fwd1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vE8() { return VCM0(s32, 0xE8); }
};

typedef struct Info {
    s16 x0;
    s8 x2;
    u8 pad3[5];
    s16 x8;
} Info;

typedef struct Unit {
    Obj o;
    u8 pad4[0xC];
    Info *info;
} Unit;

typedef struct Cls {
    u8 pad0[0xA];
    u8 xA;
} Cls;

typedef struct Holder {
    u8 pad0[0xC];
    Obj *obj;
} Holder;

typedef struct Mgr {
    u8 pad0[0x90];
    Holder *h;
} Mgr;

typedef struct Sys {
    u8 pad0[0x10];
    s32 x10;
    s32 x14;
} Sys;

typedef struct Gr {
    u8 pad0[4];
    u8 x4;
} Gr;

extern "C" {
Obj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 CharaIsInParty_3ae1d0(Obj *);
s16 *WeaponCombineLookup_3c4280(s32, Info *, u8, Info *, s32, s32 *, u8 *, u8 *, s32 *, s32, s32, s32);
Obj *InvFindByInvId_3c87d0(s32, s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
s32 RecTableBinSearch_407bb0(s32, s32, u8);
s32 ListFindByKey_407ee0(s32, s32);
Gr *ItemDefGetWeaponData_40e110(s16 *);
extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern Sys *D_00483890;
extern Mgr *D_00483894;
}

#define INFO(p) (((Unit *)(p))->info)

extern "C" s32 WeaponCombineCheck_3c3e30(s32 arg0, Obj *unit, u8 *outA, u8 *outB, s32 *outC) {
    Info *info;
    s32 kind;
    s32 type;
    s32 id;
    u8 v;
    s32 i;
    s32 last;
    Obj *found;
    Obj *p;
    s32 id2;
    Info *info2;
    s32 kind2;
    s32 v2;
    s32 type2;
    s32 sum;
    s32 a;
    s32 w;
    s16 *r;
    Gr *g;
    Obj *h;

    if (D_00483890 == 0 || D_00483894 == 0) {
        return 0;
    }
    if (unit == 0) {
        return 0;
    }
    *outA = 0;
    *outB = 0;
    *outC = 0;
    info = INFO(unit);
    kind = info->x8;
    type = info->x2;
    id = info->x0;
    v = unit->vA8((int)(long)(unit));
    found = 0;
    i = D_00465A08[0];
    last = D_00465A10[0];
    for (; i <= last; i++) {
        p = InvFindByInvId_3c87d0(arg0, i, 0);
        if (p != 0 && (((Cls *)p)->xA & 1)) {
            found = p;
            break;
        }
    }
    id2 = -1;
    info2 = 0;
    kind2 = -1;
    v2 = 0;
    type2 = -1;
    if (found != 0) {
        info2 = INFO(found);
        kind2 = info2->x8;
        id2 = info2->x0;
        type2 = info2->x2;
        v2 = found->vA8();
    }
    if (found == 0) {
        if (type == 7) {
            return -2;
        }
        if (type == 0) {
            goto body;
        }
        if (type == 1) {
            goto body;
        }
        return -1;
    }
    if ((u32)type <= 1) {
        if (kind != kind2) {
            return -7;
        }
        if (type != type2) {
            return -7;
        }
    } else if (type != 7) {
        return -1;
    }
body:
    if (type == 7) {
        sum = 0;
        i = 0;
        do {
            a = found->v94(i);
            sum += a - found->v90(i);
            i++;
        } while (i < 5);
        if (sum > 0) {
            return 6;
        }
        return -10;
    }
        a = unit->v60();
        if (a < unit->v64()) {
            return -4;
        }
        w = 0;
        r = WeaponCombineLookup_3c4280(arg0, info, v, info2, v2, &w, outA, outB, outC, 0, 0, 0);
        if (r == 0) {
            if (RecTableBinSearch_407bb0(ListFindByKey_407ee0(D_00483894->h->obj->v70(kind), type), id, v) == 0) {
                return -6;
            }
            if (found != 0) {
                return -8;
            }
        }
        if (r == 0) {
            goto ret1;
        }
        g = ItemDefGetWeaponData_40e110(r);
        if (g == 0) {
            return 0;
        }
        h = CharaMgrPoolFindByDataId_3a8a70(D_00483890->x14, kind, 1, 1, 0, 0, 0);
        if (h == 0) {
            return 0;
        }
        if (CharaIsInParty_3ae1d0(h) != 0 && h->vE8() < (g->x4 & 0x7F)) {
            return 2;
        }
        if (*r == 0x3EC3 && StateFlagTest_3ccd70(D_00483890->x10, 0x4AF) != 0) {
            return -9;
        }
        if (*outC < 0) {
            return 4;
        }
        {
            s32 t = *r;
            if (id == t && v == *outB) {
                goto ret5;
            }
            if (id2 == t && (u8)v2 == *outB) {
ret5:
                return 5;
            }
        }
ret1:
        return 1;
}
