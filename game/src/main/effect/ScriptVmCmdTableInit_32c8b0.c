/* rgp:protos */
#define RGP_SELF_ScriptVmCmdTableInit_32c8b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pair_FUN_0032c8b0 {
    s32 a;
    s32 b;
} Pair_FUN_0032c8b0;

extern s32 D_004E8050[];
extern Pair_FUN_0032c8b0 D_00452800[];

void ScriptVmCmdTableInit_32c8b0(void)
{
    s32 i;
    s32 v;

    for (i = 0; i < 0x200; i++) {
        D_004E8050[i] = 0;
    }
    i = 0;
    while (1) {
        v = D_00452800[i].a;
        if (v == 0) {
            break;
        }
        D_004E8050[D_00452800[i].b] = v;
        i++;
    }
}
