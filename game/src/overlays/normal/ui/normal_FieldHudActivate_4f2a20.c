/* rgp:protos */
#define RGP_SELF_normal_FieldHudActivate_4f2a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F2A20 -- open: reset, blank the 16 slot widgets (0x2E..0x3D),
 * clear the 0x398 sub-object and mark the panel live. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x398 - 0x37A];
    u8  f398[4];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudActivate_4f2a20(Obj *p, void * rgp_a1);

void normal_FieldHudActivate_4f2a20(Obj *p, void *rgp_a1)
{
    s32 i;

    normal_FieldHudEnemyListAllocMaybe_4f2870(p, (void *)rgp_a1);
    for (i = 0; i < 16; i++) {
        UiSetWidgetAlpha_2907a0(p, (u16)(i + 0x2E), 0.0f);
    }
    AiAllySuggestRecReset_3a80e0(&p->f398);
    p->f378 = 1;
}
