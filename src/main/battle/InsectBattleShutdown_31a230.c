#include "types.h"

typedef struct Obj_FUN_0031a230 Obj_FUN_0031a230;

extern s32 D_00482AF0;
extern s32 D_00482AF4;
extern s32 D_00482AF8;
extern Obj_FUN_0031a230 *InsectBattleGet_31a8d0(void);
extern void func_50A270(Obj_FUN_0031a230 *o);
extern void InsectDataStackRelease_31a790(void);
extern void CameraPopModeCurrent_309b70(void);
extern void SoundBankFree_1b9c00(s32 n);

void InsectBattleShutdown_31a230(void)
{
    Obj_FUN_0031a230 *o;

    o = InsectBattleGet_31a8d0();
    if (o != 0) {
        func_50A270(o);
        InsectDataStackRelease_31a790();
        CameraPopModeCurrent_309b70();
        D_00482AF0 = 0;
        D_00482AF4 = 0;
        D_00482AF8 = 0;
        SoundBankFree_1b9c00(5);
    }
}
