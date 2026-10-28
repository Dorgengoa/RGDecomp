/* rgp:protos */
#define RGP_SELF_normal_FieldHudAttackChainOpen_4f6bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F6BF0 -- rebuilds the nine-slot row of the sub-object at +0x14:
 * the first `n` slots are enabled, the rest disabled.  `sd` into the returned
 * record's +0x8 is a 64-bit member, so `n` widens with dsll32/dsra32 ,0. */
typedef struct Rec {
    u8  pad000[0x8];
    s64 f08;
} Rec;

typedef struct N {
    u8  pad000[0x14];
    u8  f014[0x3C8];
    s16 f3DC;
    s16 f3DE;
    s32 f3E0;
    s16 f3E4;
} N;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudAttackChainOpen_4f6bf0(N *p, s32 n)
{
    Rec *r;
    u16  id;
    s32  i;

    UiSetWidgetVisible_290010(p->f014, 1, 1, -1);
    UiSetWidgetVisible_290010(p->f014, 2, 1, -1);
    UiSetWidgetVisible_290010(p->f014, 3, 0, -1);
    UiSetWidgetVisible_290010(p->f014, 4, 0, -1);
    UiSetWidgetPos_290f60(p->f014, 2, -0x2B, -0x1C);
    UiSetWidgetAlpha_2907a0(p->f014, 2, 0.0f);
    id = 5;
    for (i = 0; i < 9; i++) {
        if (i < n) {
            UiSetWidgetVisible_290010(p->f014, id, 1, -1);
        } else {
            UiSetWidgetVisible_290010(p->f014, id, 0, -1);
        }
        id++;
    }
    r = ((Rec *)UiGetWidgetSubItem_28f2b0(p->f014, 2, 1));
    if (r != NULL) {
        r->f08 = n;
    }
    p->f3DC = 1;
    p->f3E0 = 0;
    p->f3DE = n;
    p->f3E4 = 0;
}
