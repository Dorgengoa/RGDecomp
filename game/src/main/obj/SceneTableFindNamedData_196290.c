/* rgp:protos */
#define RGP_SELF_SceneTableFindNamedData_196290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(const char *, const char *);

void *SceneTableFindNamedData_196290(void *param_1, char *param_2)
{
    u8 *base = (u8 *)param_1;
    s32 i;
    u8 *elem;
    char *field;
    u8 skip;

    for (i = 0; i < *(s32 *)(base + 0x210); i++)
    {
        elem = base + i * 8;
        field = *(char **)(elem + 0x214);
        skip = !((u32)field > 0);
        if (skip)
        {
            continue;
        }
        if (field != 0)
        {
            if (strcmp(field, param_2) == 0)
            {
                return elem + 0x214;
            }
        }
    }
    return 0;
}
