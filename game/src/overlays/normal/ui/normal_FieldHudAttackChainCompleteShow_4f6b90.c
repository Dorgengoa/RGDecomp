/* rgp:protos */
#define RGP_SELF_normal_FieldHudAttackChainCompleteShow_4f6b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F6B90 -- two initialisers on the sub-object at +0x14, then two
 * constant stores at the tail of the parent. */
typedef struct N {
    u8  pad000[0x14];
    u8  f014[0x3C8];
    s16 f3DC;
    u8  pad3DE[0x2];
    s32 f3E0;
} N;

/*rgp*/
/*rgp*/

void normal_FieldHudAttackChainCompleteShow_4f6b90(N *p)
{
    UiSetWidgetVisible_290010(p->f014, 4, 1, -1);
    UiSetWidgetPos_290f60(p->f014, 4, -0x3E, -0x60);
    p->f3E0 = 0;
    p->f3DC = 0x21;
}
