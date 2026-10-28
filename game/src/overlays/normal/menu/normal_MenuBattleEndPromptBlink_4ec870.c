/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndPromptBlink_4ec870 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EC870 -- the 0x47 sub-widget's two-sided FADE step on an object
 * passed in `$4` (one argument; `$5` is never read).  Frame -0x20 is entirely
 * the callee-saved save area (`sq $16` at 0x00 + `sd $31` at 0x10); there is no
 * stack object.  The widget lives at p+0x14 and the guard byte at p+0x114.
 *
 * func_290770's result is compared twice, so it is a named local.  The `<= 0.0f`
 * arm ends in `b .L004EC900`, i.e. if/ELSE; the else arm's `c.lt.s` + `bc1t`
 * PAST the call makes it `>= 1.0f`.  `mtc1 $0,$f12` for the compare's 0.0f is
 * REUSED as the second call's third argument -- do not spell that argument any
 * other way.
 */

typedef struct Obj {
    u8 pad000[0x14];
    u8 f014[0x114 - 0x14];
    u8 f114;
} Obj;

extern f32 D_0047D5D0;            /* gp - 0x7BA0 */
extern f32 D_0047D924;            /* gp - 0x784C */

/*rgp*/
/*rgp*/

void normal_MenuBattleEndPromptBlink_4ec870(Obj *p)
{
    f32 t;

    if (p->f114 != 0) {
        t = UiGetWidgetAlpha_290770(p->f014, 0x47);
        if (t <= 0.0f) {
            UiFadeWidgetAlpha_290690(p->f014, 0x47, 1.0f, D_0047D5D0, -1.0f);
        } else if (t >= 1.0f) {
            UiFadeWidgetAlpha_290690(p->f014, 0x47, 0.0f, D_0047D924, -1.0f);
        }
    }
}
