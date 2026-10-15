#include "types.h"

extern s32 D_0047E028;
extern s32 D_0047E02C;
extern s32 D_0048120C;

extern s32 DeleteSema(s32 id);

s32 FileSysShutdown_181890(void)
{
    if (D_0047E028 >= 0) {
        DeleteSema(D_0047E028);
    }
    if (D_0047E02C >= 0) {
        DeleteSema(D_0047E02C);
    }
    D_0048120C = 0;
    return 1;
}
