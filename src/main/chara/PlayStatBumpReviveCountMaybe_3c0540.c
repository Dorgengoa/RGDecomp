#include "types.h"

/* Head of a 5-member clone group (116 B each): PlayStatBumpReviveCountMaybe_3c0540 / PlayStatBumpMemberChallengeStartedMaybe_3a1940 /
   Members differ in ONE token,
   the base offset of the counter table (0x49C4/0x8E0/0x6A0/0x420/0x2E0).

   Bump one cell of a [.][10] u16 counter table.  Retail strength-reduces the
   row stride to `sll 2 / addu / sll 2`, i.e. ((2^2 + 1) * 2^2) = 20 = 10 * 2,
   which is what fixes the row width at 10 and agrees with the `i >= 10` bound.
   The guard is the shared-return `||` pair, so the second test's taken
   condition is the strict `i < 10` and its compare lands in a GPR, not $at. */

typedef struct Src3a1 {
    u8  pad000[0x10];
    s32 m10;                    /* +0x10 */
} Src3a1;

typedef struct Tbl3a1 {
    u8  pad000[0x49C4];
    u16 counts[1][10];          /* +0x49C4 */
} Tbl3a1;

extern Src3a1 *D_00483890;
extern s32 StateGetChapterIndexMaybe_3cd500(s32 a);

s32 PlayStatBumpReviveCountMaybe_3c0540(Tbl3a1 *o, s32 i)
{
    s32 r;

    if (i < 0 || i >= 10) {
        return 0;
    }
    r = StateGetChapterIndexMaybe_3cd500(D_00483890->m10);
    o->counts[r][i]++;
    return 1;
}
