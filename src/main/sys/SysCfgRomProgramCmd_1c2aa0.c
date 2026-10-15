#include "types.h"

extern s32 strcmp(const char *, const char *);
extern s32 VariantGetInt_1c2bd0(void);
extern char D_0045B000[];
extern u32 D_0048155C;

s32 SysCfgRomProgramCmd_1c2aa0(void *param_1, s32 param_2)
{
    s32 v;
    s32 r;

    if (param_2 != 1)
    {
        return 0;
    }
    v = *(s32 *)param_1;
    if (v == 0)
    {
        if (strcmp(*(char **)((u8 *)param_1 + 4), D_0045B000) == 0)
        {
            D_0048155C = 2;
        }
    }
    else
    {
        r = VariantGetInt_1c2bd0();
        D_0048155C = 0 < (u32)r;
    }
    return 1;
}
