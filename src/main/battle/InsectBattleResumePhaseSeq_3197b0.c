#include "types.h"

typedef struct Obj_FUN_003197b0 Obj_FUN_003197b0;

extern s32 GetLoadedOverlayId_1c3200(void);
extern Obj_FUN_003197b0 *InsectBattleGet_31a8d0(void);
extern void func_50DAD0(Obj_FUN_003197b0 *o, s32 n);

void InsectBattleResumePhaseSeq_3197b0(void)
{
    Obj_FUN_003197b0 *o;

    if (GetLoadedOverlayId_1c3200() == 5) {
        o = InsectBattleGet_31a8d0();
        if (o != 0) {
            func_50DAD0(o, 7);
        }
    }
}
