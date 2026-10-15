#include "types.h"
/* normal 0x004F76D0 -- calls the 0x33C040 helper on its argument and returns
 * the argument. */

extern void func_33C040(void *p);

extern void *normal_FieldHudGlowListCtor_4f76d0(void *p);

void *normal_FieldHudGlowListCtor_4f76d0(void *p)
{
    func_33C040(p);
    return p;
}
