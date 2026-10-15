#include "types.h"

extern void StateBlockReset_3cd670(void);
extern s32 StateTablesLoad_421080(s32, s32, s32, s32, void *);
extern void *D_004838C0;
extern s32 D_004838C4;

s32 StateBlockSetup_3cd5f0(void *self, s32 arg1, s32 arg2, void *arg3)
{
    s32 t;

    if (arg1 == 0 || arg3 == NULL) {
        return 0;
    }
    D_004838C0 = arg3;
    D_004838C4 = *(s32 *)((u8 *)arg3 + 8);
    StateBlockReset_3cd670();
    t = *(s32 *)((u8 *)self + 4);
    if (t != 0) {
        StateTablesLoad_421080(t, arg1, arg2, D_004838C4, self);
    }
    return 1;
}
