/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveConfirmMoveCb_4f6ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6ED0 (96 bytes, 24 instructions, 2 calls) -- push one row's
 * two display fields.  The second call's last argument is the recorded
 * "bool built from an inequality and negated in one expression" idiom:
 * `sltu $2,$0,$2 / xori $2,$2,1 / andi 0xFF` is `u8 b = !(x != 0);`, and the
 * `andi` is the u8 local promoting to the callee's s32 parameter.
 */

typedef struct Row Row;
struct Row {
    u8 pad00[0x10];
    s16 field010;
};

extern u8 insmenu_D_004FA180[];

/*rgp*/

s32 insmenu_InsectVsSaveConfirmMoveCb_4f6ed0(Row *o)
{
    u8 b;

    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x7A, o->field010);
    b = !(o->field010 != 0);
    UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x46, b);
    return 1;
}
