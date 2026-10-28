/* rgp:protos */
#define RGP_SELF_normal_FieldHudAllySuggestHide_4f09b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F09B0 -- one early exit on state 10, then the body guarded
 * POSITIVELY on the state being non-zero.  The orphan `addiu $2, $0, 1` at
 * 0x004F09DC is the branch-likely duplication of the flag constant. */
typedef struct N {
    u8  pad000[0x3A2];
    s16 f3A2;
    u8  pad3A4[0x8];
    s16 f3AC;
} N;

/*rgp*/

void normal_FieldHudAllySuggestHide_4f09b0(N *p)
{
    s16 st = p->f3A2;

    if (st == 10 || st == 0) {
        return;
    }
    p->f3AC = 1;
    UiSetWidgetVisible_290010(p, 0x5F, 0, -1);
    UiSetWidgetVisible_290010(p, 0x73, 0, -1);
}
