/* rgp:protos */
#define RGP_SELF_EvMapObjCtor_367040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00471EC0[];   /* %hi/%lo -> incomplete array */

void *EvMapObjCtor_367040(u8 *o)
{
    u8 *p;

    EvObjCtor_2f9f00(o);
    *(s32 **)(o + 0xDC) = D_00471EC0;
    p = o + 0xE0;
    do {
        EvMapObjPointReset_3644f0(p);
        p += 0x40;
    } while (p < o + 0x1A0);
    EvMapObjPartInit_364240(o + 0xE0);
    EvMapObjResetMaybe_366f20(o);
    return o;
}
