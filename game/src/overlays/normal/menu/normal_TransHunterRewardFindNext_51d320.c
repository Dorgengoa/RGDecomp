/* rgp:protos */
#define RGP_SELF_normal_TransHunterRewardFindNext_51d320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051D320 -- scans the shop line list DOWNWARD from D_00480784 to
 * D_0048075C looking for the first row whose f04 count is positive.  The
 * "entry at index" helper is INLINE: the `bltz` / `slt` pair against f7C is a
 * two-sided range guard whose failing arms both produce a NULL pointer, and
 * the sll/addu/sll is the 0x14 element pitch.  `lh $3,0x4($3)` off that NULL
 * is retail's own behaviour, so the source dereferences unguarded. */

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
typedef struct Root { u8 pad00[0x08]; Grp *f08; } Root;

extern s16 D_0048075C;            /* gp - 0x4A14 */
extern s16 D_00480784;            /* gp - 0x49EC */

/*rgp*/

/* THE ENTRY-AT-INDEX LOOKUP IS A TERNARY OVER A `&&`, measured against eight
 * other spellings in one sweep (static helper inlined or not, goto-early,
 * nested if, if/else-if/else, `&&` as a statement if, `||` inverted): every
 * other arm came out ONE WORD SHORT because it tail-merges the two null
 * results.  The `&&` ternary is the only one that keeps them apart and puts
 * the j<0 null LAST, falling into the join. */

s32 normal_TransHunterRewardFindNext_51d320(void)
{
    Root *h;
    Tbl  *t;
    Ent  *e;
    s32   i;
    s32   j;

    h = ((Root *)GetGameData_1fede0());
    if (D_0048075C <= D_00480784) {
        for (i = D_00480784; i >= D_0048075C; i--) {
            j = i - 1;
            t = h->f08->f94->f10;
            e = (j >= 0 && j < t->f7C) ? &t->f8C[j] : 0;
            if (e->f04 > 0) {
                return i;
            }
        }
    }
    return 0;
}
