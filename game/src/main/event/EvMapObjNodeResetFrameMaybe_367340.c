/* rgp:protos */
#define RGP_SELF_EvMapObjNodeResetFrameMaybe_367340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
/*rgp*/

void EvMapObjNodeResetFrameMaybe_367340(u8 *o)
{
    u8 m[0x40] __attribute__((aligned(16)));
    u8 *p;

    EvMapObjPartClear_3641f0(o);
    p = *(u8 **)(o + 0x144);
    if (p != 0) {
        if (*(s8 *)(p + 0x2C) == 0) {
            *(u128 *)(m + 0x00) = *(u128 *)(p + 0x60);
            *(u128 *)(m + 0x10) = *(u128 *)(p + 0x70);
            *(u128 *)(m + 0x20) = *(u128 *)(p + 0x80);
            *(u128 *)(m + 0x30) = *(u128 *)(p + 0x90);
        } else {
            Mat34To44_13e1f0(m, p + 0x30);
        }
        ModelFrameSetMatrix_14a190(*(void **)(o + 0x144), m);
    }
}
