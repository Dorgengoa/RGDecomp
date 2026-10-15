#include "types.h"

typedef struct Obj_FUN_0031a700 Obj_FUN_0031a700;

extern void InsectBattleGetMemStack_31a8c0(void);
extern Obj_FUN_0031a700 *InsectBattleGet_31a8d0(void);
extern void InsectBattleShutdown_31a230(void);
extern void func_50E640(Obj_FUN_0031a700 *o);
extern void CameraPopModeCurrent_309b70(void);

void InsectBattleReset_31a700(void)
{
    Obj_FUN_0031a700 *o;

    InsectBattleGetMemStack_31a8c0();
    o = InsectBattleGet_31a8d0();
    if (o == 0) {
        InsectBattleShutdown_31a230();
    } else {
        func_50E640(o);
        CameraPopModeCurrent_309b70();
    }
}
