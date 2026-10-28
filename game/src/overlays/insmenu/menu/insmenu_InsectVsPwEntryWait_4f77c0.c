/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPwEntryWait_4f77c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F77C0 (72 bytes) -- raise the "screen busy" event when the
 * current screen says it is, and hand the second argument straight back. */

typedef struct Screen Screen;
struct Screen {
    u8  pad0000[0xE6];
    s16 field00E6;
};

extern Screen *D_00484104;      /* gp - 0x106C */
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */

/*rgp*/

s32 insmenu_InsectVsPwEntryWait_4f77c0(s32 a, s32 b)
{
    Screen *scr;

    scr = D_00484104;
    if (scr != 0 && scr->field00E6 != 0) {
        StateMachineSetState_28ede0(&D_004842E8, 0x88CB, 0);
    }
    return b;
}
