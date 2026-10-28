/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_MapScriptCmdTableBuild_1e9af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s32 a;
    s32 b;
} Ent;

extern s32 D_004B3460[];
extern Ent D_0044B570[];
/*rgp*/

s32 MapScriptCmdTableBuild_1e9af0(void *p)
{
    s32 i;
    s32 m;
    s32 k;
    s32 id;
    s32 idx;

    for (i = 0; i < 0x12C; i++) {
        D_004B3460[i] = 0;
    }
    for (k = 0; ; k++) {
        id = D_0044B570[k].a;
        if (id == 0) {
            break;
        }
        for (m = 0; m < k; m++) {
            if (D_0044B570[k].b == D_0044B570[m].b) {
                for (; (rg_spin_halt(0x001E9B5C), 1);) {
                }
            }
        }
        idx = D_0044B570[k].b;
        if (idx >= 0 && idx < 0x12C) {
            D_004B3460[idx] = id;
        }
    }
    return (ScriptVmSetCmdTable_176ae0(p, D_004B3460, 0x12C), (s32)0);
}
