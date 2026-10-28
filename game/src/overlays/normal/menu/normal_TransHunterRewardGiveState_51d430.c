/* rgp:protos */
#define RGP_SELF_normal_TransHunterRewardGiveState_51d430 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051D430 -- the shop line's per-frame typewriter tick.  The
 * `addiu $2,-1` / `sltiu $1,$2,2` guard is `(u32)(m - 1) < 2`, NOT a compiled
 * switch (a switch costs four more words for the same body).  The inline
 * entry-at-index helper is the same one normal_FUN_0051D320 carries.
 * `lh`/`addiu 1`/`sh` then `dsll32/dsra32 ..,16` on D_004848F0 is the s16
 * global re-tested straight after its own store -- store forwarding, not a
 * reload, so the increment and the compare are two source statements. */

typedef struct Ent {
    u8    pad00[2];
    s16   f02;
    s16   f04;
    s16   f06;
    u8    pad08[0x14 - 0x08];
} Ent;                                      /* 0x14 */

typedef struct Tbl {
    u8    pad00[0x7C];
    s16   f7C;
    u8    pad7E[0x8C - 0x7E];
    Ent  *f8C;
} Tbl;

typedef struct Obj  { u8 pad00[0x10]; Tbl *f10; } Obj;
typedef struct Grp  { u8 pad00[0x94]; Obj *f94; } Grp;
typedef struct Root { u8 pad00[0x08]; Grp *f08; u8 pad0C[0x18 - 0x0C]; void *f18; } Root;

extern u8 D_004B2570;

extern s16   D_0048075C;          /* gp - 0x4A14 */
extern s16   D_00480784;          /* gp - 0x49EC */
extern s16   D_004848F0;          /* gp - 0x880  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484720;          /* gp - 0xA50  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* THE ENTRY-AT-INDEX LOOKUP IS A TERNARY OVER A `&&`, measured against eight
 * other spellings in one sweep (static helper inlined or not, goto-early,
 * nested if, if/else-if/else, `&&` as a statement if, `||` inverted): every
 * other arm came out ONE WORD SHORT because it tail-merges the two null
 * results.  The `&&` ternary is the only one that keeps them apart and puts
 * the j<0 null LAST, falling into the join.
 * THE TWO ASSIGNMENTS IN THE `!= 0` ARM ARE IN REVERSE EMISSION ORDER: `id`
 * is written FIRST in the source and mwcc emits `n`'s load first, which is
 * what puts `n` in $19 and `id` in $17.  Measured: 24 declaration-order
 * permutations bottom out at 6 bad words (only 4 distinct objects -- decl
 * order cannot separate `n` from `id` here), and swapping THAT ONE PAIR of
 * statements closes it.  Swapping the `== 0` arm's pair as well is inert. */

s32 normal_TransHunterRewardGiveState_51d430(void)
{
    Root *h;
    s32   n;
    s32   j;
    s32   id;
    Tbl  *t;
    Ent  *e;
    s32   k;

    if ((u32)(MenuGridCursorInput_28e170(D_00484720, &D_004B2570, 0, 0) - 1) < 2) {
        StateMachineSetState_28ede0(D_0048470C, 0x1C, 0);
        h = ((Root *)GetGameData_1fede0());
        k = D_00480784 - 1;
        t = h->f08->f94->f10;
        e = (k >= 0 && k < t->f7C) ? &t->f8C[k] : 0;
        if (D_004848F0 != 0) {
            id = e->f02;
            n = e->f04;
        } else {
            n = e->f06;
            id = 0x40FE;
        }
        for (j = 0; j < n; j++) {
            InvAddItemRepeat_3c47b0(h->f18, id, 0, 1);
        }
        D_004848F0 = D_004848F0 + 1;
        if (D_004848F0 == 2) {
            D_004848F0 = 0;
            D_00480784 = D_00480784 - 1;
        }
    }
    return 1;
}
