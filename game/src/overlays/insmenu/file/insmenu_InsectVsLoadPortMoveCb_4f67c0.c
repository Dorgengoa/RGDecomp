/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPortMoveCb_4f67c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F67C0 -- two calls on the object, then arm the gp state byte. */

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0x12];
    s16 f12;
};

extern u8 D_0048438C;       /* gp - 0xDE4 */
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadPortMoveCb_4f67c0(Obj *o)
{
    SaveSetPort_37b7c0(o->f12);
    insmenu_InsectVsLoadPortCursorBob_4f68d0(o->f12, 0, 1);
    D_0048438C = 5;
    return 1;
}
