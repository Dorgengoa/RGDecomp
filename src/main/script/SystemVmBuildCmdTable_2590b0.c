#include "types.h"

typedef struct Ent {
    s32 a;
    s32 b;
} Ent;

extern s32 D_004BE5B0[];
extern Ent D_0044D6F0[];
extern s32 ScriptVmSetCmdTable_176ae0(void *p, s32 *a, s32 n);

s32 SystemVmBuildCmdTable_2590b0(void *p)
{
    s32 i;
    s32 m;
    s32 k;
    s32 id;
    s32 idx;

    for (i = 0; i < 0x6D6; i++) {
        D_004BE5B0[i] = 0;
    }
    for (k = 0; ; k++) {
        id = D_0044D6F0[k].a;
        if (id == 0) {
            break;
        }
        for (m = 0; m < k; m++) {
            if (D_0044D6F0[k].b == D_0044D6F0[m].b) {
                for (;;) {
                }
            }
        }
        idx = D_0044D6F0[k].b;
        if (idx >= 0 && idx < 0x6D6) {
            D_004BE5B0[idx] = id;
        }
    }
    return ScriptVmSetCmdTable_176ae0(p, D_004BE5B0, 0x6D6);
}
