/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTakeCancelFlag_4ea0d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EA0D0 -- read the widget flag, clear it, and report whether it
 * was 1.  `xori $3, $3, 0x1` followed by `sltiu $2, $3, 0x1` is mwcc's
 * equality-with-a-constant idiom, not a bool negation. */

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x14];
    s16 f14;
};

extern u8 insmenu_D_004FA1A0[];
/*rgp*/

s32 insmenu_InsectVsTakeCancelFlag_4ea0d0(void)
{
    Widget *w;
    s16 t;

    w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x7532));
    t = w->f14;
    w->f14 = 0;
    return t == 1;
}
