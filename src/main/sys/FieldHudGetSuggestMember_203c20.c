#include "types.h"

/* s88m de-asm: -1 unless the s16 at 0x5273C2 is set, else the s16 at D_005273B8
 * (the object FieldHudGetSuggestMemberPtr_203c60 returns).  The if/else assigning one result gives
 * retail's unfolded null test of the symbol address. */
extern s16 D_005273B8[];

s32 FieldHudGetSuggestMember_203c20(void)
{
    s16 *p;
    s32 r;

    if (*(s16 *)0x5273C2 != 0 && (p = D_005273B8) != 0) r = *p; else r = -1;
    return r;
}
