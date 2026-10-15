#include "types.h"
#pragma divbyzerocheck on
#pragma optimization_level 3

extern "C" {
typedef struct Def { s32 id; u8 pad4[8]; s16 *pC; } Def;
typedef struct Ent {
    Def *def;
    s16 h4;
    u8 flag : 1;
    u8 fpad : 7;
    u8 pad7;
    s16 state;
    s16 timer;
    s16 hC;
    u8 padE[0x12];
} Ent;
typedef struct Slot {
    s32 id;
    Def *a;
    Ent *e;
} Slot;
typedef struct Hd { u8 pad[4]; s16 kind; u8 pad6[0x2A]; s16 no; } Hd;
typedef struct Ctx { u8 pad[0x18]; Hd *hd; } Ctx;
typedef struct Rec { s32 x0; s16 *p4; } Rec;
extern Rec *PlanetAreaMatrixLookupByProgress_3ed840(void *, s32);
extern void HandleEntryInit_3f40a0(Ent *);
extern void HandleEntryRelease_3f12f0(void *, Ent *, s32);
extern void NavRemoveGraphById_30a3b0(s32);
extern void EventObjMgrRemoveByIdFwdThunk_2fd970(s32);
extern s32 HandleEntryFindFreeSlot_3f1500(void *);
extern void HandleEntryRequest_3f14b0(void *, Ent *);
extern const s32 D_004644C8[4];
extern s32 D_004644D0[4];
extern const s32 D_004644D8[4];
}

class Tbl {
public:
    virtual Def *v0(s32);
    virtual Def *v1(s32);
    virtual Def *v2(s32);
    virtual Def *v3(s32);
    virtual Def *v4(s32);
    virtual Def *v5(s32);
    virtual Def *v6(s32);
    virtual Def *v7(s32);
    virtual Def *v8(s32);
    virtual Def *v9(s32);
    virtual Def *v10(s32);
    virtual Def *v11(s32);
    virtual Def *v12(s32);
    virtual Def *v13(s32);
    virtual Def *v14(s32);
    virtual Def *v15(s32);
    virtual Def *v16(s32);
    virtual Def *v17(s32);
    virtual Def *v18(s32);
    virtual Def *v19(s32);
    virtual Def *v20(s32);
    virtual Def *v21(s32);
    virtual Def *v22(s32);
    virtual Def *v23(s32);
    virtual Def *v24(s32);
    virtual Def *v25(s32);
    virtual Def *v26(s32);
};
typedef struct Sub { u8 pad[0x18]; Tbl *tbl; } Sub;
typedef struct Obj {
    Ctx *ctx;
    u8 pad4[0x1C];
    Ent *ents;
    u8 pad24[0x10];
    Sub *p34;
} Obj;

extern "C" s32 WorldDataAreaEntriesUpdateMaybe_3f0cc0(Obj *o, s32 id, s32 cnt, s32 *ids)
{
    Ent * E_S3;
    s32 C3_S3;
    Slot sl[16];
    u8 done[16];
    Hd *h;
    u16 skip;
    s32 excl;
    s32 no;
    s32 kind;
    Slot *p;
    s32 n;
    Ent *e;
    s32 j;
    s32 pass;
    s32 m;
    s32 v;
    s32 *d;
    bool ok;
    s32 st;
    s32 pending;
    s32 i;
    u16 found;
    Slot *q;
    s32 k;
    s32 t;
    s32 lim;
    s32 r;
    Rec *rc;
    s16 *d2;
    s16 *q2;
    Ent *pe;
    s32 did;
    s32 c3;
    s32 c4;
    s32 c5;
    Ent *e3;
    Ent *e4;
    Ent *e5;
    Slot *p4;
    Slot *p5;

    i = 0;
    k = 0;
    j = 0;
    e = 0;
    if (o->ctx == 0 || o->ents == 0) return 0;
    h = o->ctx->hd;
    kind = *(volatile s16 *)&h->kind;
    no = h->no;
    skip = 0;
    excl = -1;
    if (kind == 0xA) {
        if (no >= 0x5208 && no < 0x526D) {
            skip = 1;
            excl = 0x226C9;
        }
        if (no >= 0x4E21 && no < 0x4E85) {
            excl = 0x226C9;
        }
    }
    p = sl;
    n = 0;
    if (id >= 0 && !skip && id != excl) {
        p->id = id;
        p->a = 0;
        e = o->ents;
        p->e = 0;
        for (m = 0; m < D_004644C8[0]; m++, e++) {
            d = (s32 *)e->def;
            if (d != 0 && *d == p->id) {
                p->a = e->def;
                p->e = e;
                break;
            }
        }
        p++;
        n++;
    }
    if (ids != 0) {
        for (j = 0; j < cnt; j++) done[j] = 0;
        lim = D_004644C8[0];
        for (pass = 1; pass <= 3; pass++) {
            for (j = 0; j < cnt; j++) {
                if (done[j]) continue;
                v = ids[j];
                if (v == id || v < 0 || skip || v == excl) {
                    done[j] = 1;
                    continue;
                }
                e = o->ents;
                for (m = 0; m < lim; m++, e++) {
                    d = (s32 *)e->def;
                    if (d == 0) {
                        if (pass == 1) continue;
                        if (pass == 2) continue;
                        if (pass == 3) {
                            p->id = v;
                            n++;
                            p->a = 0;
                            p->e = 0;
                            done[j] = 1;
                            p++;
                            goto next;
                        }
                    }
                    if (*d == v) {
                        st = e->state;
                        ok = 0;
                        if (st == 3) goto o34;
                        if (st == 4) {
                        o34:
                            if (pass == 1) ok = 1;
                        } else if (st != 0 && st != -1 && pass == 2) {
                            ok = true;
                        }
                        if (ok) {
                            p->id = v;
                            n++;
                            done[j] = 1;
                            p->a = e->def;
                            p->e = e;
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
        pe = p->e;
        if ((*(volatile __typeof__(p->id) *)&(p->id)) >= 0 && pe == 0) {
            p->a = o->p34->tbl->v26(p->id);
            pending++;
        } else if (pe != 0 && pe->state == 0) {
            pending++;
        }
    }
    E_S3 = o->ents;
    for (C3_S3 = 0; C3_S3 < D_004644C8[0]; C3_S3++, E_S3++) {
        st = E_S3->state;
        if (st == 3 || st == 4 || st == 1) {
            found = 0;
            for (q = sl, k = 0; k < n; k++, q++) {
                if (q->e == E_S3) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                if (st == 3) goto f34;
                if (st == 4) {
                f34:
                    E_S3->state = 3;
                    E_S3->timer = -1;
                }
            } else if (st == 3) {
                E_S3->state = 4;
                E_S3->timer = D_004644D8[0];
            } else if (st == 1) {
                HandleEntryInit_3f40a0(E_S3);
            } else if (--E_S3->timer <= 0) {
                did = 0;
                if (E_S3->def != 0) did = E_S3->def->id;
                HandleEntryRelease_3f12f0(o, E_S3, 1);
                NavRemoveGraphById_30a3b0(did);
                EventObjMgrRemoveByIdFwdThunk_2fd970(did);
                HandleEntryInit_3f40a0(E_S3);
            }
        }
    }
    lim = D_004644C8[0];
    p = sl;
    for (i = 0; i < n; i++, p++) {
        if (pending <= 0) break;
        if (p->a == 0) continue;
        if (p->e != 0) continue;
        e = o->ents;
        for (m = 0; m < lim; m++, e++) {
            st = e->state;
            if (st == 0) goto a0;
            if (st == -1) {
            a0:
                HandleEntryInit_3f40a0(e);
                e->def = p->a;
                e->state = 1;
                d2 = e->def->pC;
                if (d2 != 0) {
                    rc = PlanetAreaMatrixLookupByProgress_3ed840(o->ctx, *d2);
                    q2 = 0;
                    if (rc != 0) q2 = rc->p4;
                    if (q2 != 0) e->h4 = *q2;
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
    t = D_004644D0[0];
    p = sl;
    for (k = 0; k < n; k++, p++) {
        e = p->e;
        if (e == 0) continue;
        if (e->state != 1) continue;
        if (e->def != 0) {
            r = HandleEntryFindFreeSlot_3f1500(o);
            if (r >= 0 && r < t) {
                e->hC = r;
                HandleEntryRequest_3f14b0(o, e);
            }
        } else {
            HandleEntryRelease_3f12f0(o, e, 1);
        }
    }
    return 1;
}
