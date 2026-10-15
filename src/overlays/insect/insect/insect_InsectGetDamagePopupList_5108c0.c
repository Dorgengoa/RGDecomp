#include "types.h"
/* insect 0x005108C0 -- 8 bytes.  The ADDRESS of the gp global at _gp-0x1F0
 * (0x00484F80).  It must stay a plain, small extern so the reference keeps
 * %gp_rel and compiles to the bare `addiu $2,$28,-0x1F0`. */

extern void *D_00484F80;

void *insect_InsectGetDamagePopupList_5108c0(void)
{
    return &D_00484F80;
}
