#include "types.h"

/* The handle arg k is homed to its 0x80 stack cell at entry but never read back
   (sibling EffDefSetPaused_1a0a10/0a50 convention: a dead volatile copy declared last).
   none/h/res are memory handles (0x8C/0x88/0x84): decl order sets the cells. */
#pragma opt_scalarizeliveranges off
#pragma opt_dead_assignments off
#pragma peephole off


struct H1a0df0 {
    s32 id;

    bool valid() const {
        return id != 0;
    }
    bool isNull() const {
        return !valid();
    }

};

struct E1a0df0 {
    u8 pad0[0xC8];
    s32 xC8;
    s32 padCC;
    s32 xD0;
    struct B1a0df0 *xD4;
    u8 padD8[8];
    s32 xE0;
    s32 xE4;
};

struct B1a0df0 {
    u8 pad0[0x50];
    u8 b50;
    u8 pad51[3];
    struct B1a0df0 *x54;
    struct B1a0df0 *x58;
    u8 pad5C[0x1C];
    s32 x78;
};

struct O1a0df0 {
    u8 pad0[0xC];
    s32 wC;
    u8 pad10[0xB0 - 0x10];
    u8 xB0[0x34];
    u8 xE4[0x24];
    B1a0df0 *x108;
};

extern "C" void MemStackReturnToOwnerMaybe_14dad0(s32);
extern "C" s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern "C" void MemStackHeapFree_14dcb0(s32, s32);
extern "C" void EffDefLinkInstance_19a650(B1a0df0 *, E1a0df0 *);
extern "C" void EffInstResetRecords_19aba0(B1a0df0 *, E1a0df0 *);
extern "C" E1a0df0 *EffInstCreate_19b120(B1a0df0 *, s32);
extern "C" B1a0df0 **HandleTableGet_1a1d50(void *, s32);
extern "C" E1a0df0 **EffHdlAlloc_1a3110(void *, H1a0df0 *);

static inline B1a0df0 **find1a0df0(void *tbl, s32 k)
{
    return HandleTableGet_1a1d50(tbl, k);
}

extern "C" void EffTableCreateInstance_1a0df0(H1a0df0 *out, O1a0df0 *o, s32 k, s32 arg3)
{
    E1a0df0 **slot;
    B1a0df0 *obj;
    B1a0df0 **pp;
    s32 buf;
    E1a0df0 *e;
    u32 ctx;
    volatile H1a0df0 none __attribute__((aligned(16)));
    H1a0df0 h __attribute__((aligned(16)));
    volatile H1a0df0 res __attribute__((aligned(16)));
    volatile s32 kh;

    kh = k;
    none.id = 0;
    pp = find1a0df0(o->xB0, k);
    obj = (pp != 0) ? *pp : 0;
    if (obj == 0) {
        out->id = none.id;
        return;
    }
    if (obj->b50) {
        out->id = none.id;
        return;
    }
    ctx = o->wC;
    buf = MemStackHeapAlloc_14db10(ctx, 2, 0, 0x40);
    if (buf == 0) {
        out->id = none.id;
        return;
    }
    e = EffInstCreate_19b120(obj, ctx);
    if (e == 0) {
        MemStackReturnToOwnerMaybe_14dad0(ctx);
        MemStackHeapFree_14dcb0(ctx, buf);
        out->id = none.id;
        return;
    }
    MemStackReturnToOwnerMaybe_14dad0(ctx);
    h.id = 0;
    slot = EffHdlAlloc_1a3110(o->xE4, &h);
    if (!h.isNull()) {
        *slot = e;
    }
    {
        H1a0df0 t __attribute__((aligned(16)));
        t.id = h.id;
        res.id = t.id;
        if (t.isNull()) {
            MemStackHeapFree_14dcb0(ctx, buf);
            out->id = res.id;
            return;
        }
        e->xE4 = buf;
        e->xE0 = t.id;
    }
    e->xD4 = obj;
    EffDefLinkInstance_19a650(obj, e);
    if (obj->x58 == 0 && obj->x54 == 0 && obj != o->x108) {
        obj->x58 = o->x108;
        if (o->x108 != 0) {
            o->x108->x54 = obj;
        }
        o->x108 = obj;
    }
    EffInstResetRecords_19aba0(obj, e);
    e->xD0 = arg3;
    if (obj->x78 > 0) {
        e->xC8 |= 0x20;
    }
    out->id = res.id;
}
