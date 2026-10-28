/* rgp:protos */
#define RGP_SELF_ObjGetNthAttachPointPosSafe_23b0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 ObjGetNthAttachPointPosSafe_23b0c0(void *p, int rgp_a1, int rgp_a2, void *rgp_a3)
{
    if (p == 0) goto fail;
    return ((s32)ObjGetNthAttachPointPos_1ade20(p, (int)rgp_a1, (int)rgp_a2, (void *)rgp_a3));
fail:
    return 0;
}
