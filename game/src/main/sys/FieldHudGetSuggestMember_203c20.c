/* rgp:hwaccess */ #include "port/hwaccess.h"
/* rgp:hwaccess */ extern unsigned char D_00527020[];
#line 1
/* rgp:protos */
#define RGP_SELF_FieldHudGetSuggestMember_203c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s88m de-asm: -1 unless the s16 at 0x5273C2 is set, else the s16 at D_005273B8
 * (the object FieldHudGetSuggestMemberPtr_203c60 returns).  The if/else assigning one result gives
 * retail's unfolded null test of the symbol address. */
extern s16 D_005273B8[];

s32 FieldHudGetSuggestMember_203c20(void)
{
    s16 *p;
    s32 r;

    if ((*(s16 *)((unsigned char *)D_00527020 + 0x3A2)) != 0 && (p = D_005273B8) != 0) r = *p; else r = -1;
    return r;
}
