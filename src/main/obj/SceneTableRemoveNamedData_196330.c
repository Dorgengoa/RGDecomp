/* s41 agent10: MATCH (inlined find helper). */
#include "types.h"

extern s32 strcmp(const char *a, const char *b);

static inline u8 *find00196330(void *arg0, s32 arg1)
{
    s32 val;
    u8 *rec;
    s32 i;
    u8 bad;

    for (i = 0; i < *(s32 *)((u8 *)arg0 + 0x210); i++) {
        rec = (u8 *)arg0 + i * 8 + 0x214;
        val = *(s32 *)rec;
        bad = ((val != 0) ^ 1);
        if (bad) {
            continue;
        }
        if (val != 0) {
            if (strcmp((const char *)val, (const char *)arg1) == 0) {
                return rec;
            }
        }
    }
    return NULL;
}

void SceneTableRemoveNamedData_196330(void *arg0, s32 arg1) {
    u8 *result;

    result = find00196330(arg0, arg1);
    if (result != NULL) {
        *(s32 *)result = 0;
        *(s32 *)(result + 4) = 0;
    }
}
