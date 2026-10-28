/* rgp:protos */
#line 1
#include "types.h"

struct Key {
    u16 lo;
    u16 hi;
};

struct Handle {
    f32 v;
};

struct Str {
    u32 flags;
    u8 pad4[4];
    char *ptr;
};

struct Obj {
    VC_VPTR_MEMBER; u8 v0() { return VCM0(u8, 0x8); }
    s32 m4;
};

struct Dst {
    u8 pad0[0x18];
    u32 m18;
    Key m1C;
    s32 m20;
};

struct Ctx {
    u8 *m0;
    u8 pad4[0x24];
    Dst *m28;
    s32 m2C;
    u8 pad30[4];
    s32 m34;
    Obj *m38;
};

extern "C" {
s32 SlotGetInt_15f720(s32);
void EffHdlFindIdByName_1a3280(Handle *, u8 *, s32);
Obj **HandleTableGet_1a3200(u8 *, u32);
void *EffResGetNameMaybe_1a83d0(Obj *);
void StringCtorFromCStr_1a2110(Str *, void *);
void StringAppendCStr_1a20e0(Str *, char *);
void EffHdlFindIdByName_1a3600(u32 *, u8 *, char *);
void StringDtor_107b00(Str *, s32);
}
extern "C" char D_0045A4B8[];

extern "C" s32 EffDefCmdObjectMds_19c030(s32 a0, s32 a1, Ctx **a2)
{
    Handle k1 __attribute__((aligned(16)));
    Handle k2 __attribute__((aligned(16)));
    Key x __attribute__((aligned(16)));
    u32 t;
    Handle h __attribute__((aligned(16)));
    Key key __attribute__((aligned(16)));
    Str s __attribute__((aligned(16)));
    Ctx *c;
    s32 r;
    Obj **e;
    Obj *o;
    void *q;
    char *p;
    s32 lo;
    s32 hi;

    c = *a2;
    r = SlotGetInt_15f720(a0);
    if (r == 0) {
        return 0;
    }
    if (c->m34 != 0) {
        c->m38 = 0;
        EffHdlFindIdByName_1a3280(&k1, c->m0 + 0x14, r);
        e = HandleTableGet_1a3200(c->m0 + 0x14, *(u32 *)&k1);
        o = e ? *e : 0;
        if (o->v0() == 2) {
            c->m38 = o;
        }
        return 1;
    }
    if (c->m28 == 0) {
        return 0;
    }
    if (c->m2C == 0) {
        EffHdlFindIdByName_1a3280(&k2, c->m0 + 0x14, r);
        e = HandleTableGet_1a3200(c->m0 + 0x14, *(u32 *)&k2);
        o = e ? *e : 0;
        *(u32 *)&x = 0;
        if (o != 0) {
            q = EffResGetNameMaybe_1a83d0(o);
            if (q != 0) {
                StringCtorFromCStr_1a2110(&s, q);
                StringAppendCStr_1a20e0(&s, D_0045A4B8);
                p = (s.flags & 1) ? s.ptr : (char *)&s + 1;
                EffHdlFindIdByName_1a3600(&t, c->m0 + 0x48, p);
                *(u32 *)&x = t;
                StringDtor_107b00(&s, -1);
            }
            h = k2;
            c->m28->m18 = *(u32 *)&h;
            lo = x.lo;
            lo = (key.lo & 0xFFFF0000) | lo;
            hi = x.hi;
            hi = (key.hi & 0xFFFF0000) | hi;
            key.lo = lo;
            key.hi = hi;
            *(u32 *)&c->m28->m1C = *(u32 *)&key;
            c->m28->m20 = o->m4;
        }
    }
    return 1;
}
