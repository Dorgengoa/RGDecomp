/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPortBobCb_4f6460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6460 (76 bytes) -- run the caption's hold-off counter down one
 * frame and re-place the caption, unless the menu is suppressed.
 *
 * ★ Both gp counters are `lb`, i.e. SIGNED bytes: the guard is `n > 0` and the
 * store is the decrement.
 * ★ `lh $4, 0x12($4)` appears twice because it is the join's first instruction
 * duplicated into the `blezl`'s delay slot, not two reads. */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x12];
    s16 field12;
};

extern s8 D_00484388;           /* gp - 0xDE8 */
extern s8 D_0048438C;           /* gp - 0xDE4 */

/*rgp*/

s32 insmenu_InsectVsLoadPortBobCb_4f6460(Panel *p)
{
    s8 hold;

    if (D_00484388 != 0) {
        return 1;
    }
    hold = D_0048438C;
    if (hold > 0) {
        D_0048438C = hold - 1;
    }
    insmenu_InsectVsLoadPortCursorBob_4f68d0(p->field12, 0, 1);
    return 1;
}
