#include "types.h"
typedef struct Elem Elem;
typedef struct Set Set;
typedef struct Ctx Ctx;
typedef struct Iter Iter;
typedef struct Rec Rec;

struct Elem { u8 pad[0x38]; };
struct Set {
    u8 hdr[8];
    Elem a[64];
    u8 pad[8];
};
struct Ctx {
    Set s;
    s16 xE10;
    u8 padE12[0xA];
    s32 xE1C;
    s32 xE20;
    s32 xE24;
    s32 xE28;
    s16 xE2C[4];
};
struct Iter { s32 x0; s32 x4; };
struct Rec {
    u8 pad0[4];
    s8 *name;
    s16 x8;
    u8 padA[2];
    s32 xC;
};


extern void VariantInit_36ff00(Elem *);
extern void VariantPoolReset_3e01f0(Set *);
extern s32 VariantIsZero_36ed10(s32);
extern Rec *IterNext_370040(Iter *);
extern void IterReset_3700f0(Iter *);
extern void IterInit_370170(Iter *, s8 *);
extern s32 ScriptExecOpStream_3dffa0(Set *, s16, s32, s16 *);
extern s16 CharaSysGetEncounterEntryIdMaybe_3a36f0(void *);
extern s16 CharaSysGetEncounterIdMaybe_3a36d0(void *);
extern s16 CharaSysGetEncounterSpawnParamMaybe_3a36a0(void *);
extern s32 StrNotEqual_1f5300(s8 *, s8 *);


Rec *BtlEffSetRowFindMatchingRec_3fb3c0(s8 *arg0, s8 *arg1, s32 arg2, u8 *arg3) {
    Iter it;
    Ctx ctx;
    Set tmp;
    void *o;
    s32 pass;
    u8 ok;
    Elem *q;
    Elem *p;
    Rec *r;
    u8 ne;
    s32 h;
    s16 id;

    p = ctx.s.a;
    do {
        VariantInit_36ff00(p);
        p++;
    } while (p < &ctx.s.a[64]);
    VariantPoolReset_3e01f0(&ctx.s);
    ctx.xE20 = arg2;
    ctx.xE10 = 0;
    ctx.xE1C = 0;
    id = -1;
    ctx.xE2C[0] = id;
    ctx.xE2C[1] = id;
    ctx.xE2C[2] = id;
    ctx.xE2C[3] = id;
    ctx.xE24 = 0;
    ctx.xE28 = 0;
    if (arg3 != NULL) {
        o = *(void **)(*(u8 **)(arg3 + 0x20) + 0x238);
        id = (o != NULL) ? *(s16 *)((u8 *)o + 0xC) : id;
        ctx.xE2C[0] = id;
        ctx.xE2C[1] = CharaSysGetEncounterEntryIdMaybe_3a36f0(*(void **)(arg3 + 0x20));
        ctx.xE2C[2] = CharaSysGetEncounterIdMaybe_3a36d0(*(void **)(arg3 + 0x20));
        ctx.xE2C[3] = CharaSysGetEncounterSpawnParamMaybe_3a36a0(*(void **)(arg3 + 0x20));
    }
    if (arg0 != NULL) {
        arg0 += 4;
    }
    IterInit_370170(&it, arg0);
    for (pass = 1; pass <= 2; pass++) {
        IterReset_3700f0(&it);
        while (r = IterNext_370040(&it), r != NULL) {
            ok = 0;
            if (pass == 1) {
                if (r->name != NULL) {
                    ne = r->name[0] != arg1[0] || StrNotEqual_1f5300(r->name + 1, arg1 + 1) != 0;
                    if (!ne) {
                        ok = 1;
                    }
                }
            } else if (r->name == NULL) {
                ok = 1;
            }
            if (ok) {
                if (r->x8 > 0 && r->xC != 0) {
                    q = tmp.a;
                    do {
                        VariantInit_36ff00(q);
                        q++;
                    } while (q < &tmp.a[64]);
                    VariantPoolReset_3e01f0(&tmp);
                    h = ScriptExecOpStream_3dffa0(&tmp, r->x8, r->xC, &ctx.xE10);
                    if (h == 0) {
                        ok = 0;
                    } else if (VariantIsZero_36ed10(h) != 0) {
                        ok = 0;
                    }
                }
                if (ok) {
                    return r;
                }
            }
        }
    }
    return 0;
}
