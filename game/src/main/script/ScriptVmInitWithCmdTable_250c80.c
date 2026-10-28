/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_ScriptVmInitWithCmdTable_250c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct {
    s32 unk0;
    s32 unk4;
} Elem;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    Elem *unk14;
    s32 *unk18;
    s32 unk1C;
} Obj;

/*rgp*/
/*rgp*/
void memset(void *, s32, s32);

void ScriptVmInitWithCmdTable_250c80(s32 arg0, Obj *arg1) {
    s32 i;
    s32 j;
    s32 k;
    s32 v;

    ScriptVmInit_176af0(arg0, arg1->unk0, arg1->unk4, arg1->unk8, arg1->unkC, arg1->unk10);
    if (arg1->unk18 == NULL) {
        return;
    }
    if (arg1->unk14 != NULL) {
        memset(arg1->unk18, 0, arg1->unk1C * 4);
        for (i = 0; i < arg1->unk1C; i++) {
            v = arg1->unk14[i].unk0;
            if (v == 0) {
                break;
            }
            for (j = 0; j < i; j++) {
                if (arg1->unk14[i].unk4 == arg1->unk14[j].unk4) {
                    for (; (rg_spin_halt(0x00250D18), 1);) {
                    }
                }
            }
            k = arg1->unk14[i].unk4;
            if (k >= 0 && k < arg1->unk1C) {
                arg1->unk18[k] = v;
            }
        }
    }
    ScriptVmSetCmdTable_176ae0(arg0, arg1->unk18, arg1->unk1C);
}
