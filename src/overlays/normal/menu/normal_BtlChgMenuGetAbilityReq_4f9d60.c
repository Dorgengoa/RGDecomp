#include "types.h"
/* normal 0x004F9D60 -- `j normal_BtlChgPageGetAbilityReq_5052d0 / lw $5, -0xD1C($28)`: a tail call
 * whose second argument is a gp pointer global loaded in the delay slot.
 * One of the 55 unnamed functions. */
extern void *D_00484454;
extern void normal_BtlChgPageGetAbilityReq_5052d0(void *out, void *src);

void normal_BtlChgMenuGetAbilityReq_4f9d60(void *out)
{
    normal_BtlChgPageGetAbilityReq_5052d0(out, D_00484454);
}
