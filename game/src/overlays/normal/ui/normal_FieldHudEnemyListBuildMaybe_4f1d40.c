/* rgp:protos */
#define RGP_SELF_normal_FieldHudEnemyListBuildMaybe_4f1d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F1D40 -- relabels the party/menu name row.  Walks the roster at
 * `func_1FEDE0()->f20->f238 + 0x128` and, for each live entry, sprintf's the
 * entry's name into `p->f438[i]`, appends a rank digit when the entry's level
 * is 2 or more, wraps the result through the bank string 6, and finally points
 * the matching widget `p->f3F0[i]->f04` at the buffer.
 *
 * normal_D_00525010 is 30 bytes: "0\0\0" "1\0\0" ... "9\0\0", i.e. `s8 [10][3]`, and it
 * is COPIED to a stack local (the `lb/lb/sb/sb` loop that runs 15 times, two
 * bytes per iteration, before the first call).  That loop is WRITTEN OUT, not a
 * struct assignment: the merged factory_FactoryHelpOpen_4f1f80 carries the identical
 * shape and its C is
 *     sp = D_x; dp = t; for (i = N; i > 0; i--) { dp[0]=sp[0]; dp[1]=sp[1];
 *                                                 sp += 2; dp += 2; }
 * A struct assignment instead gets 16-byte alignment and mwcc copies it with
 * `lq`/`ld`/`lwc1`/`lh`.  normal_D_00526350 is "%s" and normal_D_00526358 is "%s%s%s".
 *
 *
 * SESSION 21, drafted from nothing and closed.  SIX levers, in the order they
 * were found; each one alone reads as a different kind of failure:
 *  1. THE COPY LOOP IS WRITTEN OUT, not a struct assignment.  A struct copy
 *     gets 16-byte alignment and mwcc uses `lq`/`ld`/`lwc1`/`lh`; the merged
 *     factory_FactoryHelpOpen_4f1f80 carries retail's exact `lb/lb/sb/sb` shape and its C
 *     is the explicit two-at-a-time pointer loop above.  (First build: 75 bad.)
 *  2. `s32 n`, NOT `s16 n` -- the `lh` already sign-extends, and an s16 local
 *     costs `dsll32/dsra32 ,16` at the compare (levers.d/normal-s16-cast-sign-extension).
 *  3. THE TERNARY for `l`, not `l = 0; if (x) l = ...;` -- retail's
 *     `beql $3,$0 / daddu $19,$0,$0` puts the zero in the ANNULLED slot, which
 *     the if-statement form does not reach.
 *  4. `(u32)i` AT SITE ONE ONLY.  Without it mwcc CSEs `p + i*4` into a SIXTH
 *     callee-saved register spanning all three sprintf sites, where retail
 *     RECOMPUTES `sll/addu` at the first two and only keeps it at the third --
 *     [[normal-cse-cost-split]]'s class, and this is a spelling that BEATS it.
 *     !! The split is PER SITE: `(u32)i` at site 2 or 3 instead gives the right
 *     length but 83/81 bad.  Casting the ADDRESS rather than the INDEX
 *     (`((u8**)((s32)p + 0x438))[i]`) goes LONGER -- 4 arms, all worse.
 *  5. THE COPY LOOP NEEDS ITS OWN COUNTER `j`.  Sharing `i` with the main loop
 *     costs the loop counter its priority: ours allocated p=$16,n=$17,l=$18,
 *     i=$19 where retail has i=$16,p=$17,n=$18,l=$19 -- the whole set rotated,
 *     26 bad words of pure register permutation.  A separate counter took it to
 *     2 in one arm.  !! DECLARATION ORDER IS INERT HERE: 8 orders, 2 objects.
 *  6. `if (n > 1)`, NOT `if (n >= 2)` -- the STRICT operator puts the compare
 *     in `$at` ([[at-compare-class]]).  The last 2 words.
 *
 * `sll $3,$16,3` sits in the loop-closing `bnel`'s ANNULLED slot and feeds the
 * `addu $3,$19,$3` at the loop top -- the ordinary branch-likely induction
 * hoist, not an extra statement. */

typedef struct Cell {
    u8    pad00[4];
    void *f04;
} Cell;

typedef struct Str {
    u8          pad00[4];
    const char *f04;
} Str;

typedef struct Item {
    Str *f00;
    s16  f04;
    u8   pad06[2];
} Item;                            /* 8 bytes */

typedef struct List {
    u8   pad00[2];
    s16  f02;
    Item f04[1];
} List;

typedef struct Src {
    u8    pad000[0x238];
    u8   *f238;
} Src;

typedef struct Own {
    u8   pad00[0x20];
    Src *f20;
} Own;

typedef struct Page {
    u8    pad000[0x3F0];
    Cell *f3F0[5];
    u8    pad404[0x434 - 0x404];
    s32   f434;
    u8   *f438[0x10];
    u8    pad478[0x47A - 0x478];
    s16   f47A;
} Page;

extern s8   normal_D_00525010[];
extern char normal_D_00526350[];
extern char normal_D_00526358[];
extern void      *D_00481BBC;      /* gp - 0x35B4 */

/*rgp*/
extern void  Sprintf_1343b8(void *dst, const char *fmt, ...);
/*rgp*/

void normal_FieldHudEnemyListBuildMaybe_4f1d40(Page *p)
{
    s8       d[30] __attribute__((aligned(16)));
    const s8 *sp;
    s8       *dp;
    Own      *o;
    List     *l;
    Str      *q;
    s32       i;
    s32       n;
    s32       j;

    sp = normal_D_00525010;
    dp = d;
    for (j = 0xF; j > 0; j--) {
        dp[0] = sp[0];
        dp[1] = sp[1];
        sp += 2;
        dp += 2;
    }
    o = ((Own *)GetGameData_1fede0());
    if (o == 0) {
        return;
    }
    l = (o->f20->f238 != 0) ? (List *)(o->f20->f238 + 0x128) : 0;
    if (l == 0) {
        return;
    }
    for (i = 0; i < l->f02; i++) {
        n = l->f04[i].f04;
        q = l->f04[i].f00;
        if (q == 0) {
            continue;
        }
        Sprintf_1343b8(p->f438[(u32)i], normal_D_00526350, q->f04);
        if (n > 1) {
            Sprintf_1343b8(p->f438[i], normal_D_00526358, p->f438[i],
                        ((char *)MsgTableLookup_28aa30(D_00481BBC, 8)), &d[n * 3]);
        }
        Sprintf_1343b8(p->f438[i], ((char *)MsgTableLookup_28aa30(D_00481BBC, 6)), p->f438[i]);
        p->f3F0[i]->f04 = p->f438[i];
    }
    p->f47A = l->f02;
}
