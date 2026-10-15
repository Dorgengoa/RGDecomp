#include "types.h"

typedef struct Obj_FUN_00319dc0 Obj_FUN_00319dc0;

extern Obj_FUN_00319dc0 *InsectBattleGet_31a8d0(void);
extern void func_50A530(Obj_FUN_00319dc0 *o);
extern void func_50A460(Obj_FUN_00319dc0 *o);
extern s32 func_50DA40(Obj_FUN_00319dc0 *o, s32 n);
extern void func_4F5FC0(Obj_FUN_00319dc0 *o, s32 n);

void TaskDrawMenuInsect_319dc0(void)
{
    Obj_FUN_00319dc0 *o;

    o = InsectBattleGet_31a8d0();
    if (o == 0) {
        return;
    }
    func_50A530(o);
    func_50A460(o);
    if (func_50DA40(o, 0x1D) != 0) {
        func_4F5FC0(o, 1);
    }
    if (func_50DA40(o, 0x1C) != 0) {
        func_4F5FC0(o, 0);
    }
}
