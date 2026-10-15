#include "types.h"

typedef struct T_FUN_00341f60 {
    u8 pad000[0x8];
    s16 f08;
    u8 pad00A[0x2];
    s16 f0C;
} T_FUN_00341f60;

typedef struct E_FUN_00341f60 {
    u8 pad000[0x20];
    T_FUN_00341f60 *f20;
} E_FUN_00341f60;

typedef struct H_FUN_00341f60 H_FUN_00341f60;

extern H_FUN_00341f60 *D_00482360;
extern H_FUN_00341f60 *D_0048235C;
extern E_FUN_00341f60 *UiFindWidget_290460(H_FUN_00341f60 *h, s32 k);
extern void StateMachineSetState_28ede0(H_FUN_00341f60 *h, s32 a, s32 b);

s32 MenuRevelationBackState_341f60(s32 unused, s32 flag)
{
    E_FUN_00341f60 *e;
    T_FUN_00341f60 *t;

    if (flag != 0) {
        e = UiFindWidget_290460(D_00482360, 0x18C);
        if (e == 0) {
            return 0;
        }
        t = e->f20;
        if (t == 0) {
            return 0;
        }
        t->f08 = 0x78;
        t->f0C = 8;
    }
    StateMachineSetState_28ede0(D_0048235C, 0x6E, 0);
    return 1;
}
