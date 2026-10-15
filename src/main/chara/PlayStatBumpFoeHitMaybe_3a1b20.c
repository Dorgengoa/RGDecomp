#include "types.h"

/* Member of the 5-clone group headed by PlayStatBumpMemberChallengeClearedMaybe_3a18c0 (116 B each).
   This member differs from the head in the base offset of the counter
   table.  The reading is written up in PlayStatBumpMemberChallengeClearedMaybe_3a18c0.c. */

typedef struct Src3a1 {
    u8  pad000[0x10];
    s32 m10;                    /* +0x10 */
} Src3a1;

typedef struct Tbl3a1 {
    u8  pad000[0x420];
    u16 counts[1][10];          /* +0x420 */
} Tbl3a1;

extern Src3a1 *D_004837C0;
extern s32 StateGetChapterIndexMaybe_3cd500(s32 a);

s32 PlayStatBumpFoeHitMaybe_3a1b20(Tbl3a1 *o, s32 i)
{
    s32 r;

    if (i < 0 || i >= 10) {
        return 0;
    }
    r = StateGetChapterIndexMaybe_3cd500(D_004837C0->m10);
    o->counts[r][i]++;
    return 1;
}
