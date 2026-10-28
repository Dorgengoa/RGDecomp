/* rgp:protos */
#define RGP_SELF_MapObjFindByName_188ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(const char *, const char *);

void *MapObjFindByName_188ed0(void *param_1, char *param_2)
{
    u8 *base = (u8 *)param_1;
    s32 count = *(s32 *)(base + 0x504);
    void **arr = *(void ***)(base + 0x508);
    s32 i;
    void *entry;

    for (i = 0; i < count; i++)
    {
        entry = arr[i];
        if (entry != 0 && strcmp(param_2, (char *)entry + 0x6c) == 0)
        {
            return entry;
        }
    }
    return 0;
}
