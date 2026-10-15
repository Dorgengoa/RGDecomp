#include "types.h"
/* normal 0x00514A10 -- tail `j func_28C190`, the parameter moved to $6. */

extern const char D_005266D0[];
extern void *D_004846E8;          /* gp - 0xA88 */

extern s32 func_28C190(void *w, const char *name, void *p);

s32 normal_TransMenuWidgetListShow_514a10(void *p)
{
    return func_28C190(D_004846E8, D_005266D0, p);
}
