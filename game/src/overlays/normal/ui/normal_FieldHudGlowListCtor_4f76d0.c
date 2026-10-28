/* rgp:protos */
#define RGP_SELF_normal_FieldHudGlowListCtor_4f76d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F76D0 -- calls the 0x33C040 helper on its argument and returns
 * the argument. */

/*rgp*/

extern void *normal_FieldHudGlowListCtor_4f76d0(void *p);

void *normal_FieldHudGlowListCtor_4f76d0(void *p)
{
    UiGlowSpriteListReset_33c040(p);
    return p;
}
