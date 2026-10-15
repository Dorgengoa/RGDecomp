#include "types.h"

extern u8 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdRowCheckNop_408a50(void)
{
    s16 t;
    s32 r;

    t = *(s16 *)(D_004830F8 + 0x7C);
    if (t > 0) goto chk;
    return 1;
chk:
    if (D_004830FC - 1 >= t) goto one;
    r = 1;
    goto end;
one:
    r = 1;
end:
    return r;
}
