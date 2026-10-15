#include "types.h"
/* normal 0x00506000 -- `not $2,$2 / sltu $2,$0,$2` is `!= -1`. */
extern s32 normal_BtlChgPageGetStateId_5061a0(void *p);

s32 normal_BtlChgPageIsActive_506000(void *p)
{
    return normal_BtlChgPageGetStateId_5061a0(p) != -1;
}
