#include "types.h"

extern s32 strcmp(const char *, const char *);

s32 TexAnimSeqFindByName_162e40(void *param_1, char *param_2)
{
    u8 *base = (u8 *)param_1;
    s32 i;
    char *name;

    if (param_2 == 0)
    {
        return -1;
    }
    for (i = 0; i < *(s32 *)base; i++)
    {
        name = *(char **)(base + i * 4 + 0x244);
        if (name != 0 && strcmp(name, param_2) == 0)
        {
            return i;
        }
    }
    return -1;
}
