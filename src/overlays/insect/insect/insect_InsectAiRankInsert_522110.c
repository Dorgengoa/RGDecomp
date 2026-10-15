#include "types.h"
/* insect 0x00522110 -- 488 bytes, 122 instructions.
 *
 * Insert `cur` into a 10-slot row of a[idx], keeping the row ordered by one of
 * five keys.  All five compares branch INTO their block with a `beql`, so this
 * is a real `switch` and the source case order is the compare chain REVERSED
 * (insect-dispatch-branch-polarity): 0,1,2,3,4,default.
 *
 * The empty-slot store at .L005222A8 RECOMPUTES the address (`addu $3,$22,$21`)
 * while every arm's store goes through the CSE'd `$16`, so the early store is
 * written as the array expression and the arms through a named pointer.
 */

typedef struct Ent {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x1A - 0x19];
    s16 f1A;                        /* +0x1A */
    u8  pad1C[0x26 - 0x1C];
    u8  f26;                        /* +0x26 */
    u8  pad27[0x28 - 0x27];
    u8  f28;                        /* +0x28 */
    u8  pad29[0x38 - 0x29];
    s8  f38;                        /* +0x38 */
} Ent;

typedef struct Owner {
    u8  pad00[0x8DC];
    Ent *f8DC[1][10];               /* +0x8DC */
} Owner;

extern f32 insect_InsectPieceGetHpRatio_512e70(Ent *e);
extern s32 insect_InsectAiRandChance_522b60(Owner *o, s32 k);

void insect_InsectAiRankInsert_522110(Owner *a, Ent *b, s32 mode, s32 idx, s32 v)
{
    Ent *ent;
    Ent *cur;
    s32 i;
    Ent **p;
    f32 lim;

    lim = (f32)v / 100.0f;
    cur = b;
    if (b == 0) {
        return;
    }
    for (i = 0; i < 10; i++) {
        p = &a->f8DC[idx][i];
        ent = *p;
        if (ent != 0) {
        switch (mode) {
        case 0:
            if (ent->f18 > cur->f18) {
                continue;
            }
            *p = cur;
            cur = ent;
            break;
        case 1:
            if (ent->f1A > cur->f1A) {
                continue;
            }
            *p = cur;
            cur = ent;
            break;
        case 2:
            if (ent->f26 > cur->f26) {
                continue;
            }
            *p = cur;
            cur = ent;
            break;
        case 3:
            if (ent->f28 > cur->f28) {
                continue;
            }
            *p = cur;
            cur = ent;
            break;
        case 4:
            if (ent->f38 != 0xB) {
                if (cur->f38 == 0xB) {
                    *p = cur;
                    cur = ent;
                    break;
                }
            }
            if (insect_InsectPieceGetHpRatio_512e70(ent) <= lim) {
                *p = cur;
                cur = ent;
            }
            break;
        default:
            if (insect_InsectAiRandChance_522b60(a, 0x3C) != 0) {
                *p = cur;
                cur = ent;
            }
            break;
        }
        } else {
            a->f8DC[idx][i] = cur;
            return;
        }
    }
}
