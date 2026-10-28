/* rgp:protos */
#define RGP_SELF_BtlEffSetRowFindMatchingRec_3fb3c0 1
#include "port/game_protos.h"
#line 1
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


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


Rec *BtlEffSetRowFindMatchingRec_3fb3c0(s8 *arg0, s8 *arg1, s32 arg2, u8 *arg3) {
    Iter it __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[(0x0 - __builtin_offsetof(Ctx, s)) + sizeof(Ctx)]; char m1[0xe0d]; char m2[0xe36]; })];
    Set tmp __attribute__((aligned(16)));
    void *o;
    s32 pass;
    u8 ok;
    Elem *q;
    Elem *p;
    Rec *r;
    u8 ne;
    s32 h;
    s16 id;

    p = (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).s.a;
    do {
        VariantInit_36ff00(p);
        p++;
    } while (p < &(*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).s.a[64]);
    VariantPoolReset_3e01f0(&(*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).s);
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE20 = arg2;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE10 = 0;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE1C = 0;
    id = -1;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[0] = id;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[1] = id;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[2] = id;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[3] = id;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE24 = 0;
    (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE28 = 0;
    if (arg3 != NULL) {
        o = *(void **)(*(u8 **)(arg3 + 0x20) + 0x238);
        id = (o != NULL) ? *(s16 *)((u8 *)o + 0xC) : id;
        (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[0] = id;
        (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[1] = CharaSysGetEncounterEntryIdMaybe_3a36f0(*(void **)(arg3 + 0x20));
        (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[2] = CharaSysGetEncounterIdMaybe_3a36d0(*(void **)(arg3 + 0x20));
        (*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE2C[3] = CharaSysGetEncounterSpawnParamMaybe_3a36a0(*(void **)(arg3 + 0x20));
    }
    if (arg0 != NULL) {
        arg0 += 4;
    }
    IterInit_370170(&it, arg0, 0, 0);
    for (pass = 1; pass <= 2; pass++) {
        IterReset_3700f0(&it);
        while (r = ((Rec *)IterNext_370040(&it)), r != NULL) {
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
                    h = ((s32)ScriptExecOpStream_3dffa0(&tmp, r->x8, r->xC, &(*(Ctx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Ctx, s)))).xE10));
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
