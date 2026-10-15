#include "types.h"

typedef __int128 s128;

typedef struct {
    s32 n90;
    s32 *a94;
} Dummy;

typedef void (*Fn)(void *);

class A {
public:
    u8 pad0[0x110];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void Init();
    A() { Init(); }
};
class B : public A {
public:
    B() { Init(); }
};
inline void *operator new(unsigned int, void *p) { return p; }

typedef struct {
    u8 pad0[0x90];
    s32 cnt90;
    s32 *arr94;
    u8 pad98[0xEC - 0x98];
    s32 cntEC;
    void **arrF0;
} Tbl;

typedef struct {
    u8 pad0[0x10];
    s128 m[16];
    void **vt;
    s32 f114;
    s32 f118;
    f32 f11C;
    s128 v120;
    s128 v130;
    s32 f140;
} Obj;

extern "C" {
extern char *SlotGetInt_15f720(s64 *);
extern s32 VariantGetInt_15f780(s64 *);
extern void VariantReadVec3_15f6c0(s128 *, s64 *);
extern f32 VariantGetFloat_15f740(s64 *);
extern s32 strcmp(const char *, const char *);
extern Obj *MemStackNew_14e230(s32, s32);
extern void FrameCalcWorldMatrix_148ff0(s32, s128 *);
extern void MtxInverse_13cf40(s128 *, s128 *);
extern char D_00459080[];
extern char D_00459088[];
extern void *D_004701F0[];
extern void *D_00470220[];
extern f32 D_0047D278;
extern Tbl *D_00481154;
extern s32 D_00481158;
extern s32 D_00481174;
extern s32 D_00481180;
s32 DynCollisionCmd_1674e0(s64 *arg0, s32 arg1);
}

static inline Obj *newA(void)
{
    Obj *o = MemStackNew_14e230(0x140, D_00481158);
    if (o != 0) {
        o->vt = D_00470220;
        ((A *)o)->Init();
    }
    return o;
}

static inline Obj *newB(void)
{
    Obj *o = MemStackNew_14e230(0x150, D_00481158);
    if (o != 0) {
        o->vt = D_00470220;
        ((A *)o)->Init();
        o->vt = D_004701F0;
        ((A *)o)->Init();
    }
    return o;
}

s32 DynCollisionCmd_1674e0(s64 *arg0, s32 arg1) {
    char *name;
    Obj *obj;
    s32 a;
    s128 v0;
    s128 v1;
    s32 b;
    f32 f;
    s32 idx;
    Tbl *t;
    s32 ent;

    name = SlotGetInt_15f720(arg0++);
    if (name == 0) {
        return 0;
    }
    obj = 0;
    a = VariantGetInt_15f780(arg0++);
    VariantReadVec3_15f6c0(&v0, arg0);
    VariantReadVec3_15f6c0(&v1, arg0 + 3);
    arg0 += 6;
    b = VariantGetInt_15f780(arg0++);
    f = D_0047D278;
    if (arg1 >= 10) {
        f = VariantGetFloat_15f740(arg0);
    }
    if (strcmp(name, D_00459080) == 0) {
        obj = newA();
    } else if (strcmp(name, D_00459088) == 0) {
        obj = newB();
        if (obj != 0) {
            obj->f140 = b;
        }
    }
    if (obj == 0) {
        return 0;
    }
    obj->f118 = a;
    obj->v120 = v0;
    obj->v130 = v1;
    obj->f11C = f;
    obj->f114 = 0;
    if (D_00481180 > 0) {
        obj->f114 = 1 << (D_00481180 - 1);
    }
    t = D_00481154;
    idx = D_00481174++;
    if (idx >= 0 && idx < t->cntEC) {
        t->arrF0[idx] = obj;
    }
    idx = obj->f118;
    t = D_00481154;
    if (idx < 0 || idx >= t->cnt90) {
        ent = 0;
    } else {
        ent = t->arr94[idx];
    }
    if (ent != 0) {
        FrameCalcWorldMatrix_148ff0(ent, obj->m);
        MtxInverse_13cf40(&obj->m[4], obj->m);
        obj->m[8] = obj->m[0];
        obj->m[9] = obj->m[1];
        obj->m[10] = obj->m[2];
        obj->m[11] = obj->m[3];
        obj->m[12] = obj->m[4];
        obj->m[13] = obj->m[5];
        obj->m[14] = obj->m[6];
        obj->m[15] = obj->m[7];
    }
    return 1;
}
