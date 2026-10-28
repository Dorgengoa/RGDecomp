/* rgp:protos */
#line 1
/* PARKED s17b: m2c cannot decompile this one at all ("jr instruction... but
   the corresponding jump table is not provided" -- rgd.py decomp fails
   outright). Manual read of the listing shows a real jtbl_00465F60 20-arm
   jump table keyed on `$17` (a 0-20 running index), where each arm does a
   `dsll32/dsrl32` bit-test on a byte loaded from a vtable-returned struct
   (`andi $2,$4,1<<n` pattern via shift-pair, not a literal andi) and either
   falls through to a shared `.L003B6990`/`.L003B69D0` tail or returns early.
   0 round trips spent past reading the jump table shape -- writing this by
   hand (jump table + 20 bit-test arms + the vtable calls feeding $17/$18
   before it) is a much bigger unit than the other 49 in this lane; leaving
   it fully unattempted so the throughput budget goes to the smaller units.
   A future session should start from `asm/matchings/main/CharaCanPerformAction_3b67f0.s`
   directly (not m2c) and build the jump table's target labels first. */
/* s49m: MATCH (jtbl, rodata_check) */
#include "types.h"

struct Flags {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
};

struct Item {
    u8 pad0[0xC];
    Flags f;
};

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v68(s32 a0) { return VCM(s32, (void *, s32), 0x68, a0); }  /* +0x68 */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vBC(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xBC, rgp_fwd1, rgp_fwd2, rgp_fwd3); }  /* +0xBC */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v19C(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }  /* +0x19C */
    u8 pad4[0x190];
    s16 m194;
};

struct List {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct Item * v70(s64 a0) { return VCM(struct Item *, (void *, s64), 0x70, a0); }  /* +0x70 */
};

struct Mgr2 {
    u8 pad0[8];
    List *m8;
};

struct Mgr {
    u8 pad0[0x58];
    Mgr2 *m58;
};

extern "C" Mgr *D_0048381C;
extern "C" s32 D_00465920[4];

extern "C" s32 CharaCanPerformAction_3b67f0(Obj *o, s32 kind, int rgp_a2, int rgp_a3)
{
    s32 i;
    List *lst;
    Item *it;
    Flags *f;

    if (D_0048381C == 0) {
        return 0;
    }
    if (!o->vBC((int)(long)(kind), (int)(long)(rgp_a2), (int)(long)(rgp_a3))) {
        return 0;
    }
    if (!o->v68(kind)) {
        return 0;
    }
    for (i = 2; i < 0x30; i++) {
        if (!o->v19C(i)) {
            continue;
        }
        lst = D_0048381C->m58->m8;
        if (lst != 0) {
            it = lst->v70((s16)i);
        } else {
            it = 0;
        }
        if (it == 0) {
            continue;
        }
        f = &it->f;
        if (!f->b1) {
            return 0;
        }
        switch (kind) {
        case 1:
            if (!f->b0) {
                return 0;
            }
            break;
        case 2:
            if (!f->b2) {
                return 0;
            }
            break;
        case 3:
            if (!f->b3) {
                return 0;
            }
            break;
        case 10:
            if (!f->b4) {
                return 0;
            }
        case 11:
            if (!f->b5) {
                return 0;
            }
            break;
        case 14:
            if (!f->b7) {
                return 0;
            }
            break;
        case 15:
            if (!f->b6) {
                return 0;
            }
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 12:
        case 13:
        case 16:
        case 17:
        case 18:
        case 19:
            break;
        }
    }
    if (kind == 7) {
        if (o->m194 <= D_00465920[0]) {
            return 0;
        }
    }
    return 1;
}
