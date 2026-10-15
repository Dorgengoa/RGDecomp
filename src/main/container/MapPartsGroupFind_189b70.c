#include "types.h"

extern s32 strcmp(const char *, const char *);

s32 MapPartsGroupFind_189b70(void *param_1, char *param_2)
{
    u8 *base = (u8 *)param_1;
    s32 i;
    char *name;
    u8 skip;

    for (i = 0; i < *(s32 *)(base + 0x2A8); i++)
    {
        name = *(char **)(base + 0x2AC + i * 0x10);
        skip = !((u32)name > 0);
        if (skip)
        {
            continue;
        }
        if (strcmp(name, param_2) == 0)
        {
            return i;
        }
    }
    return -1;
}
