/* rgp:protos */
#define RGP_SELF_MenuItemCommandFadeState_2acf90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P_002acf90 {
    u8 pad0[0x11];
    s8 f11;
    u8 pad12[0x40 - 0x12];
    s8 f40;
    u8 pad41;
    s16 f42;
} P_002acf90;

typedef struct S_002acf90 {
    u8 pad0[0x18];
    s32 f18;
} S_002acf90;

extern P_002acf90 *D_00482374;
extern s32 D_00482364;
extern s32 D_0048235C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuItemCommandFadeState_2acf90(void)
{
    P_002acf90 *p;
    S_002acf90 *s;
    s32 k;
    s32 x;
    s32 r;
    if (MenuItemCmdFadeSequenceStep_2adce0(0x87) == 0) goto one;
    p = D_00482374;
    k = p->f42;
    if (k == 0) {
        s = ((S_002acf90 *)GetGameData_1fede0());
        x = ((s32)UiEntryListFindByTag_28ea40(D_00482364, 3));
        r = MenuGetItemAtCell_2a7000(D_00482374->f11, x + 4);
        if (r == 0) return 0;
        InvMergeStacksMaybe_3c57f0(s->f18, r, 0);
        StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    } else if (k == 1) {
        StateMachineSetState_28ede0(D_0048235C, 0x39, 0);
    } else if (k == 4) {
        p->f40 = 2;
        StateMachineSetState_28ede0(D_0048235C, 0x36, 0);
    }
one:
    return 1;
}
