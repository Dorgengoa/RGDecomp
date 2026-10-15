#include "types.h"

/* MAIN MenuResLoad_299400 -- the same two-arm init loop as the settled seed
   src/wf/main/MenuMainResLoad_299080.c, over D_004DB260 instead of D_004823F8:
   `((i<<3)-i)<<3` is the *0x38 element stride, the special case is `i == 1`
   and the compare constant is rematerialised in the loop-back delay slot.
   D_0047EBA8 is declared SHORTER THAN THE TRUTH so it stays in small data
   (`addiu $2,$28,%gp_rel(D_0047EBA8)`), the seed's measured spelling. */

typedef struct Elem299400 { u8 pad00[0x38]; } Elem299400;

extern void *GetDrawCtxNameTable_15de40(void);
extern void LoadHandleArrayReset_28b160(void *, s16);
extern void LoadHandleRequestAlloc_28b3e0(void *, void *, s32, s32, void *, s32);
extern void LoadHandleRequestFile_28b550(void *, s32, s32, s32);
extern void LoaderQueueSeparatorGlobal_28afd0(void);

extern Elem299400 D_004DB260[];
extern s32 D_004823FC;
extern void *D_00482338;
extern s32 D_0047EBA8[2];

s32 MenuResLoad_299400(void)
{
    s32 i;

    GetDrawCtxNameTable_15de40();
    LoadHandleArrayReset_28b160(D_004DB260, 2);
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            LoadHandleRequestAlloc_28b3e0(&D_004DB260[i], &D_004823FC, D_0047EBA8[i], 0,
                         D_00482338, 0);
        } else {
            LoadHandleRequestFile_28b550(&D_004DB260[i], D_0047EBA8[i], 0, 0);
        }
    }
    LoaderQueueSeparatorGlobal_28afd0();
    return 0;
}
