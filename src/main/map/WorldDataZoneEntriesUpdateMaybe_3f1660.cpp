#include "types.h"
extern "C" {
#pragma divbyzerocheck on

typedef struct Def { s16 id; u8 pad2[0xE]; s16 *p10; } Def;
typedef struct Ent {
    Def *def;
    s32 x4;
    s16 h8;
    u8 flag : 1;
    u8 fpad : 7;
    u8 padB;
    s16 state;
    s16 timer;
    s16 h10;
    u8 pad12[0x16];
} Ent;
typedef struct Slot {
    s16 id;
    Def *a;
    s32 b;
    Ent *e;
} Slot;
typedef struct Sub { u8 pad[0x14]; s32 x14; } Sub;
typedef struct Obj {
    s32 ctx;
    u8 pad4[0x14];
    Ent *ents;
    u8 pad1C[0x18];
    Sub *p34;
} Obj;
typedef struct Rec { s32 x0; s16 *p4; } Rec;

extern Def *GroupTableFindEntry_415e00(s32, s16, s16);
extern s32 ZonePhaseLookupByProgress_3ed4d0(s32, s16, s32);
extern Rec *PlanetAreaMatrixLookupByProgress_3ed840(s32, s32);
extern void HandleEntryInit_3f4160(Ent *);
extern void HandleEntryRelease_3f1d80(Obj *, Ent *, s32);
extern s32 HandleEntryFindFreeSlot_3f22f0(Obj *);
extern void HandleEntryRequest_3f22a0(Obj *, Ent *);
extern const s32 D_004644A0[4];
extern s32 D_004644A8[4];
extern const s32 D_004644B8[4];

}
#pragma optimization_level 3
extern "C" s32 WorldDataZoneEntriesUpdateMaybe_3f1660(Obj *o, s32 id, s32 cnt, s32 *ids)
{
    bool found;
            s32 arg_h1;

    Slot sl[16];
    u8 done[16];
    s32 lim;
  s32 k_w181;
    Slot *q;
    Ent *e;
    s32 n;
    s16 *d;
    s32 id2;
    u8 ok;
    s32 r;
    s32 i;
    s32 t;
    Ent *pe;
    s32 st;
    s16 *q2;
    s16 *d2;
    Rec *rc;
    s32 v;
    s32 pending;
    Slot *p;
  s32 i_w146;
    s32 pass;
    s32 j0;
    s32 j1;
    s32 lim0;
    s32 j;
    s32 m;
    s32 k;

    if (o->ctx == 0 || (e = o->ents) == 0) return 0;
    p = sl;
    n = 0;
    if (id >= 0) {
        p->id = id;
        p->a = 0;
        p->b = 0;
        p->e = 0;
        for (j1 = 0; j1 < D_004644A0[0]; j1++, e++) {
            d = (s16 *)e->def;
            if (d != 0 && *d == p->id) {
                p->a = e->def;
                p->b = e->x4;
                p->e = e;
                break;
            }
        }
        p++;
        n++;
    }
    if (ids != 0) {
        for (m = 0; m < cnt; m++) done[m] = 0;
        lim0 = D_004644A0[0];
        for (pass = 1; pass <= 3; pass++) {
            for (j = 0; j < cnt; j++) {
                if (done[j]) continue;
                v = ids[j];
                if (v == id || v < 0) {
                    done[j] = 1;
                    continue;
                }
                e = o->ents;
                for (m = 0; m < lim0; m++, e++) {
                    d = (s16 *)e->def;
                    if (d == 0) {
                        if (pass == 1) continue;
                        if (pass == 2) continue;
                        if (pass == 3) {
                            p->id = v;
                            n++;
                            p->a = 0;
                            p->b = 0;
                            p->e = 0;
                            done[j] = 1;
                            p++;
                            goto next;
                        }
                    }
                    if (*d == v) {
                        st = e->state;
                        ok = false;
                        if (st == 3) goto o34;
                        if (st == 4) {
                        o34:
                            if (pass == 1) ok = (s32)1;
                        } else if (st != 0 && st != -1 && pass == 2) {
                            ok = true;
                        }
                        if (ok) {
                            n++;
                            p->id = v;
                            p->a = e->def;
                            p->b = e->x4;
                            p->e = e;
                            done[j] = 1;
                            p++;
                        }
                        break;
                    }
                }
            next:
                if (n >= 16) break;
            }
        }
    }
    pending = 0;
    p = sl;
    for (i = 0; i < n; i++, p++) {
        id2 = p->id;
        pe = p->e;
        if (id2 >= 0 && pe == 0) {
            p->a = GroupTableFindEntry_415e00(o->p34->x14, (s16)id2 / 100, id2);
            arg_h1 = p->id;
            p->b = ZonePhaseLookupByProgress_3ed4d0(o->ctx, arg_h1, -1);
            pending++;
        } else if (pe != 0 && pe->state == 0) {
            pending++;
        }
    }
    e = o->ents;
    for (m = 0; m < D_004644A0[0]; m++, e++) {
        st = e->state;
        if (st == 3 || st == 4 || st == 1) {
            found = false;
            for (q = sl, k = 0; k < n; k++, q++) {
                if (q->e == e) {
                    found = true;
                    break;
                }
            }
            if (found) {
                if (st == 3) goto f34;
                if (st == 4) {
                f34:
                    e->state = 3;
                    e->timer = -1;
                }
            } else if (st == 3) {
                e->state = 4;
                e->timer = D_004644B8[0];
            } else if (st == 1) {
                HandleEntryInit_3f4160(e);
            } else if (--e->timer <= 0) {
                HandleEntryRelease_3f1d80(o, e, 1);
                HandleEntryInit_3f4160(e);
            }
        }
    }
    lim = D_004644A0[0];
    p = sl;
    for (i_w146 = 0; i_w146 < n; i_w146++, p++) {
        if (pending <= 0) break;
        if (p->a == 0) continue;
        if (p->e != 0) continue;
        e = o->ents;
        for (m = 0; m < lim; m++, e++) {
            st = e->state;
            if (st == 0) goto a0;
            if (st == -1) {
            a0:
                HandleEntryInit_3f4160(e);
                e->def = p->a;
                e->x4 = p->b;
                e->state = 1;
                e->h8 = -1;
                e->flag = 0;
                d2 = e->def->p10;
                if (d2 != 0) {
                    rc = PlanetAreaMatrixLookupByProgress_3ed840(o->ctx, *d2);
                    q2 = 0;
                    if (rc != 0) q2 = rc->p4;
                    if (q2 != 0) e->h8 = *q2;
                    if (*d2 == 1) e->flag = 1;
                    else e->flag = 0;
                }
                p->e = e;
                pending--;
                goto brk;
            }
        }
    brk:;
    }
    t = D_004644A8[0];
    p = sl;
    for (k_w181 = 0; k_w181 < n; k_w181++, p++) {
        e = p->e;
        if (e == 0) continue;
        if (e->state != 1) continue;
        if (e->def != 0) {
            r = HandleEntryFindFreeSlot_3f22f0(o);
            if (r >= 0 && r < t) {
                e->h10 = r;
                HandleEntryRequest_3f22a0(o, e);
            }
        } else {
            HandleEntryRelease_3f1d80(o, e, 1);
        }
    }
    return 1;
}
