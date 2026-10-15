#include "types.h"
/* insect 0x00512B10 -- 21 instructions.  Both incoming integer parameters are
 * forwarded untouched to insect_InsectMsgGet_512b70, whose result is the second
 * argument of insect_InsectMsgTextWidth_512ab0 -- a NESTED call expression, which is what
 * keeps $6 alive in $16 across the first call. */

extern s32 insect_InsectMsgTextWidth_512ab0(void *h, s32 n, s32 v);
extern s32 insect_InsectMsgGet_512b70(void *h, s32 id);

s32 insect_InsectMsgCenterX_512b10(void *h, s32 id, s32 w)
{
    return (w - insect_InsectMsgTextWidth_512ab0(h, insect_InsectMsgGet_512b70(h, id), 2)) / 2;
}
