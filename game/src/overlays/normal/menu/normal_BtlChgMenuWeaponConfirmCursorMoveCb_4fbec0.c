/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponConfirmCursorMoveCb_4fbec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FBEC0 -- swap the two icon slots of widget 0x4A on the s16 at
 * +0x10.  The `dsll32/dsra32 ..,16` pairs are explicit (s16) casts off s32
 * locals, not s16 locals. */

typedef struct Rec { u8 pad00[0x10]; s16 f10; } Rec;

extern void *D_0048449C;          /* gp - 0xCD4 */

/*rgp*/

s32 normal_BtlChgMenuWeaponConfirmCursorMoveCb_4fbec0(Rec *r)
{
    s32 a;
    s32 b;

    if (r->f10 == 0) {
        a = 0x4C;
        b = 0x18;
    } else {
        a = 0x18;
        b = 0x4C;
    }
    UiSetSpriteU_28f930(D_0048449C, 0x4A, (s16)a, 0);
    UiSetSpriteU_28f930(D_0048449C, 0x4A, (s16)b, 1);
    return 1;
}
