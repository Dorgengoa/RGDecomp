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
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual s32 v68(s32);  /* +0x68 */
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual s32 vBC();  /* +0xBC */
    virtual void v046();
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void v059();
    virtual void v060();
    virtual void v061();
    virtual void v062();
    virtual void v063();
    virtual void v064();
    virtual void v065();
    virtual void v066();
    virtual void v067();
    virtual void v068();
    virtual void v069();
    virtual void v070();
    virtual void v071();
    virtual void v072();
    virtual void v073();
    virtual void v074();
    virtual void v075();
    virtual void v076();
    virtual void v077();
    virtual void v078();
    virtual void v079();
    virtual void v080();
    virtual void v081();
    virtual void v082();
    virtual void v083();
    virtual void v084();
    virtual void v085();
    virtual void v086();
    virtual void v087();
    virtual void v088();
    virtual void v089();
    virtual void v090();
    virtual void v091();
    virtual void v092();
    virtual void v093();
    virtual void v094();
    virtual void v095();
    virtual void v096();
    virtual void v097();
    virtual void v098();
    virtual void v099();
    virtual void v100();
    virtual s32 v19C(s32);  /* +0x19C */
    u8 pad4[0x190];
    s16 m194;
};

struct List {
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual struct Item *v70(s64);  /* +0x70 */
};

struct Mgr2 {
    u8 pad0[8];
    List *m8;
};

struct Mgr {
    u8 pad0[0x58];
    Mgr2 *m58;
};

extern Mgr *D_0048381C;
extern s32 D_00465920[4];

extern "C" s32 CharaCanPerformAction_3b67f0(Obj *o, s32 kind)
{
    s32 i;
    List *lst;
    Item *it;
    Flags *f;

    if (D_0048381C == 0) {
        return 0;
    }
    if (!o->vBC()) {
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
