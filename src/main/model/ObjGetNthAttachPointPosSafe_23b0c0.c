#include "types.h"

extern s32 ObjGetNthAttachPointPos_1ade20(void *p);

s32 ObjGetNthAttachPointPosSafe_23b0c0(void *p)
{
    if (p == 0) goto fail;
    return ObjGetNthAttachPointPos_1ade20(p);
fail:
    return 0;
}
