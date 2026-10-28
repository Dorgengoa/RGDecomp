/* rgp:protos */
#define RGP_SELF_EffDefCmdBillboard_19ef40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EffDefCmdBillboard_19ef40(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    s32 v;

    if (*(void **)(o + 0x28) == 0) {
        return 0;
    }
    v = VariantGetInt_15f780(args);
    *(s32 *)(*(u8 **)(o + 0x28) + 0x3C) = v;
    return 1;
}
