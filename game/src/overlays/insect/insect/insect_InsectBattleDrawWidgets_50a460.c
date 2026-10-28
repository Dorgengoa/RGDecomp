/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawWidgets_50a460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050A460 -- 188 bytes, 47 instructions, 11 calls. */

typedef struct Obj {
    u8   pad00[0x878];
    s32  f878;                      /* +0x878 */
    s32  f87C;                      /* +0x87C */
    s32  f880;                      /* +0x880 */
    u8   pad884[0x5080 - 0x884];
    u8   f5080;                     /* +0x5080 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleDrawWidgets_50a460(Obj *o)
{
    if (insect_InsectBattleTestFlag_50da40(o, 0x16) == 0) {
        return;
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x17) != 0) {
        UiDrawWidgets_291910(o->f878);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x1C) == 0) {
        insect_InsectBattleLogDraw_51b8d0(&o->f5080);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x2C) != 0) {
        insect_InsectBattleDrawDimOverlay_4f52a0(o);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x18) != 0) {
        UiDrawWidgets_291910(o->f87C);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x19) != 0) {
        UiDrawWidgets_291910(o->f880);
    }
}
