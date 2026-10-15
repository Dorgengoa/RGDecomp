#pragma opt_propagation off
#include "types.h"
typedef unsigned __int128 u128;

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;
typedef struct Ent { s32 m0; s32 m4; s32 m8; u8 pad[0x14]; } Ent;
typedef struct Slot { u8 pad[0x170]; } Slot;
typedef struct Item { s32 m0; s32 m4; } Item;
typedef struct Map { s32 n; s32 *a; s32 *b; } Map;
typedef struct Obj {
    u8 pad0[0x180];
    u128 m180;
    u128 m190;
    u128 m1A0;
    u8 pad1[0x204 - 0x1B0];
    s32 m204;
    Slot *m208;
    s32 m20C;
    Ent *m210;
    u8 pad2[0x270 - 0x214];
    u8 m270[0x430 - 0x270];
    Map m430;
} Obj;

extern Obj *D_0049D418[0x100];
extern s32 D_0049D398[0x100];
extern s32 D_0049D390[0x100];
extern s32 D_0049D434[0x100];
extern f32 D_0047E1C0;
extern f32 D_0047E1C4;
extern f32 D_0047E1C8;
extern f32 D_0047E1CC;

extern void FrameUnlink_149d00(Item *it);
extern void ModelSetScale_150ff0(Obj *o, Vec4 *v);
extern void ModelSetRot_151080(Obj *o, Vec4 *v);
extern void ModelSetPos_151110(Obj *o, Vec4 *v);
extern s32 ModelGetRootFrame_1511a0(void *o);
extern Item *ModelGetFrame_1511f0(void *o, s32 id);
extern s32 SlotGetInt_15f720(u64 *p);
extern void DynClothCfgParse_167350(Slot *s, s32 a, s32 b, s32 c, s32 d);
extern s32 ArchiveGetFileData_181dd0(s32 a, s32 b, s32 *out);

static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

static inline Ent *findEnt(Obj *o, s32 idx)
{
    Ent *e = o->m210;
    s32 n;
    s32 i;
    if (e == 0) {
        return 0;
    }
    n = -1;
    for (i = 0; i < o->m20C; i++, e++) {
        if (e->m8 == 1) {
            n++;
        }
        if (n == idx) {
            return e;
        }
    }
    return 0;
}

static inline Slot *getSlot(Obj *o, s32 idx)
{
    Slot *s = o->m208;
    if (s == 0 || o->m204 == 0) {
        return 0;
    }
    if (idx < 0 || idx >= o->m204) {
        return 0;
    }
    return &s[idx];
}

s32 InfoCfgClothCmd_1aa5f0(u64 *p, s32 count)
{
    s32 out;
    u128 sv0;
    u128 sv1;
    u128 sv2;
    Vec4 t0;
    Vec4 t1;
    Vec4 t2;
    Obj *o;
    s32 ctx;
    s32 k;
    s32 *cnt;
    s32 base;
    Ent *e;
    s32 i;
    Slot *s;

    o = D_0049D418[0];
    ctx = D_0049D398[0];
    if (o == 0 || ctx == 0) {
        return 0;
    }
    cnt = D_0049D434;
    k = D_0049D390[0];
    sv0 = o->m180;
    sv1 = o->m190;
    sv2 = o->m1A0;
    { Vec4 *pv = &t0; pv->x = D_0047E1C0; pv->y = D_0047E1C4; pv->z = D_0047E1C8; pv->w = D_0047E1CC; }
    t0.x = 0.0f;
    t0.y = 0.0f;
    t0.z = 0.0f;
    { Vec4 *pt = &t0; ModelSetPos_151110(o, pt); }
    clr(&t1, sizeof(t1));
    t1.x = 0.0f;
    t1.y = 0.0f;
    t1.z = 0.0f;
    ModelSetRot_151080(o, &t1);
    clr(&t2, sizeof(t2));
    t2.x = 1.0f;
    t2.y = 1.0f;
    t2.z = 1.0f;
    ModelSetScale_150ff0(o, &t2);
    base = ModelGetRootFrame_1511a0(o);
    e = findEnt(o, 0);
    if (e != 0) {
        base = (s32)ModelGetFrame_1511f0(o, e->m0);
    }
    for (i = 0; i < count; i++) {
        s32 id;
        s = getSlot(o, *cnt);
        if (s == 0) {
            return 0;
        }
        id = SlotGetInt_15f720(p++);
        if (id != 0) {
            s32 r = ArchiveGetFileData_181dd0(k, id, &out);
            if (r != 0) {
                DynClothCfgParse_167350(s, r, out, base, ctx);
                (*cnt)++;
            }
        }
    }
    ModelGetRootFrame_1511a0(o);
    ModelGetRootFrame_1511a0(o->m270);
    {
        Map *m = &o->m430;
        for (i = 0; i < m->n; i++) {
            Item *a = ModelGetFrame_1511f0(o, m->a[i]);
            Item *b;
            if (a == 0) {
                continue;
            }
            b = ModelGetFrame_1511f0(o->m270, m->b[i]);
            if (b != 0 && a->m4 == 0 && b->m4 != 0) {
                FrameUnlink_149d00(b);
            }
        }
    }
    ModelSetPos_151110(o, (Vec4 *)&sv0);
    ModelSetRot_151080(o, (Vec4 *)&sv1);
    ModelSetScale_150ff0(o, (Vec4 *)&sv2);
    return 1;
}
