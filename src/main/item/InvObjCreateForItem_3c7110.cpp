#include "types.h"

class EntDef {
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25();
    virtual EntDef *v70(s16);
};

class Actor {
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10();
    virtual void v34();
    virtual bool v38(s32, s32, s32);
};

struct Mgr {
    s8 _0[0x168];
    void *pool;
};

extern "C" {
void *PoolAllocElem_36ab00(void *, s32, s32);
void PoolFreeElemByPtr_36aa80(void *, Actor *);
s32 InvAllocUniqueId_3c4f10(Mgr *);
void ItemObtainedFlagSetMaybe_3cbfc0(s32, s32, s32);
void InvObjVirtualReset_3d5120(void *);
s32 ItemDefIsKindCId4B1_40e2e0(EntDef *);
s32 ItemDefIsKindCId4B0_40e310(EntDef *);
s32 ItemDefIsInsect_40e340(EntDef *);
s32 ItemDefIsSpecialWeapon_40e370(EntDef *);
s32 ItemDefIsWeapon_40e400(EntDef *);
extern u8 D_00471FE0[];
extern u8 D_00476040[];
extern u8 D_004758D0[];
extern u8 D_004759F0[];
extern u8 D_00475B10[];
extern u8 D_00475E00[];
extern u8 D_00475CE0[];
extern u8 D_00475F20[];
extern s32 D_00465AF0[];
extern u8 *D_00483890;
extern u8 *D_00483894;
Actor *InvObjCreateForItem_3c7110(Mgr *m, s32 id, s32 arg2);
}

struct EF3 { u8 pad[0x17]; u8 lo : 6; u8 f : 1; u8 hi : 1; };
static inline void *poolNew(void *pool, s32 size) {
    if (pool != 0) {
        return PoolAllocElem_36ab00(pool, size, 0);
    }
    return 0;
}

#define VT(o) (*(void **)(o))

static inline void *newA(void *pool, s32 size, u8 *vt) {
    void *o = poolNew(pool, size);
    if (o != 0) {
        VT(o) = D_00471FE0;
        VT(o) = D_00476040;
        InvObjVirtualReset_3d5120(o);
        VT(o) = vt;
        InvObjVirtualReset_3d5120(o);
    }
    return o;
}
static inline void *newB(void *pool, s32 size, u8 *vt1, u8 *vt2) {
    void *o = poolNew(pool, size);
    if (o != 0) {
        VT(o) = D_00471FE0;
        VT(o) = D_00476040;
        InvObjVirtualReset_3d5120(o);
        VT(o) = vt1;
        InvObjVirtualReset_3d5120(o);
        VT(o) = vt2;
        InvObjVirtualReset_3d5120(o);
    }
    return o;
}
static inline void *newC(void *pool, s32 size) {
    void *o = poolNew(pool, size);
    if (o != 0) {
        VT(o) = D_00471FE0;
        VT(o) = D_00476040;
        InvObjVirtualReset_3d5120(o);
    }
    return o;
}

Actor *InvObjCreateForItem_3c7110(Mgr *m, s32 id, s32 arg2) {
    EntDef *e;
    void *o;
    s32 r;
    bool ok;

    if (id < 0 || arg2 < 0) {
        return 0;
    }
    if (m->pool == 0) {
        return 0;
    }
    if (D_00483894 == 0) {
        return 0;
    }
    e = (*(EntDef **)(*(u8 **)(D_00483894 + 0x40) + 8))->v70(id);
    if (e == 0) {
        return 0;
    }
    if (ItemDefIsKindCId4B1_40e2e0(e)) {
        o = newA(m->pool, 0x1C, D_004758D0);
    } else if (ItemDefIsKindCId4B0_40e310(e)) {
        o = newA(m->pool, 0x1C, D_004759F0);
    } else if (ItemDefIsInsect_40e340(e)) {
        o = newA(m->pool, 0x1C, D_00475B10);
    } else if (ItemDefIsSpecialWeapon_40e370(e)) {
        o = newB(m->pool, 0x28, D_00475E00, D_00475CE0);
    } else if (ItemDefIsWeapon_40e400(e)) {
        o = newA(m->pool, 0x20, D_00475E00);
    } else if (((EF3 *)e)->f) {
        o = newA(m->pool, 0x18, D_00475F20);
    } else {
        o = newC(m->pool, 0x14);
    }
    if (o == 0) {
        return 0;
    }
    r = InvAllocUniqueId_3c4f10(m);
    if (r >= 0) {
        ok = ((Actor *)o)->v38(r, arg2, id);
    } else {
        ok = false;
    }
    if (!ok) {
        ((Actor *)o)->v34();
        PoolFreeElemByPtr_36aa80(m->pool, (Actor *)o);
        return 0;
    }
    if (arg2 >= 0 && arg2 <= D_00465AF0[0]) {
        ItemObtainedFlagSetMaybe_3cbfc0(*(s32 *)(D_00483890 + 0x10), id, 1);
    }
    return (Actor *)o;
}
