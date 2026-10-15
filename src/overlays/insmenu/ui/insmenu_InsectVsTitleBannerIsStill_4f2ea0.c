#include "types.h"
/* insmenu 0x004F2EA0 -- `sltu $2, $0, $2 / xori $2, $2, 0x1` is a bool built
 * from an inequality and negated in ONE expression.  s32 return, not u8: a u8
 * return would add `andi $2, $2, 0xFF` retail does not have. */
extern const u8 D_004FA180[];
extern s32 func_290D30(const void *a, s32 b);
s32 insmenu_InsectVsTitleBannerIsStill_4f2ea0(void)
{
    return !(func_290D30(D_004FA180, 0x39) != 0);
}
