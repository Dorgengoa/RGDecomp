/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_AiScriptVmBuildCmdTable_2c1780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s32 a;
    s32 b;
} Ent;

extern s32 D_004DBB10[];
extern Ent D_004511E0[];
/*rgp*/

s32 AiScriptVmBuildCmdTable_2c1780(void *p)
{
    s32 i;
    s32 m;
    s32 k;
    s32 id;
    s32 idx;

    for (i = 0; i < 0x3E8; i++) {
        D_004DBB10[i] = 0;
    }
    for (k = 0; ; k++) {
        id = D_004511E0[k].a;
        if (id == 0) {
            break;
        }
        for (m = 0; m < k; m++) {
            if (D_004511E0[k].b == D_004511E0[m].b) {
                for (; (rg_spin_halt(0x002C17EC), 1);) {
                }
            }
        }
        idx = D_004511E0[k].b;
        if (idx >= 0 && idx < 0x3E8) {
            D_004DBB10[idx] = id;
        }
    }
    return (ScriptVmSetCmdTable_176ae0(p, D_004DBB10, 0x3E8), (s32)0);
}
