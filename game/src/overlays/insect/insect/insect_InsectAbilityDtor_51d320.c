/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityDtor_51d320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051D320 -- 68 bytes.  `dsll32/dsra32 ..,16` on a register
 * parameter is an explicit (s16) cast of an s32 local. */

/*rgp*/

void *insect_InsectAbilityDtor_51d320(void *p, s32 n)
{
    if (p != 0) {
        if ((s16)n > 0) {
            OperatorDelete_100840((void *)p);
        }
    }
    return p;
}
