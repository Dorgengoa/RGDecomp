/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_SystemVmBuildCmdTable_2590b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s32 a;
    s32 b;
} Ent;

extern s32 D_004BE5B0[];
extern Ent D_0044D6F0[];
/*rgp*/

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
                for (; (rg_spin_halt(0x0025911C), 1);) {
                }
            }
        }
        idx = D_0044D6F0[k].b;
        if (idx >= 0 && idx < 0x6D6) {
            D_004BE5B0[idx] = id;
        }
    }
    return (ScriptVmSetCmdTable_176ae0(p, D_004BE5B0, 0x6D6), (s32)0);
}
