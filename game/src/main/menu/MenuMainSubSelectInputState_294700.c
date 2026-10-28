/* rgp:protos */
#define RGP_SELF_MenuMainSubSelectInputState_294700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x26];
    s16 x26;
} Cfg;

typedef struct {
    u8 pad0[0xC];
    Cfg *xC;
    u8 pad10[8];
    s32 x18;
} Glob;

typedef struct {
    u8 pad0[0x12];
    s16 x12;
    u8 pad14[2];
    s16 x16;
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00482350;
extern s16 D_00482394;
extern s16 D_004823A0;
extern u8 D_004B2570[0x400];
extern u8 D_004DB1F0[0x400];

s32 MenuMainSubSelectInputState_294700(s32 arg0, s32 arg1)
{
    Glob *g;
    Ent *e;
    s32 r;

    g = ((Glob *)GetGameData_1fede0());
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004DB1F0, 2, 0);
        e = ((Ent *)UiEntryListFindByTag_28ea40(D_004DB1F0, 2));
        e->x16 = D_00482394;
    }
    r = MenuGridCursorInput_28e170(D_004DB1F0, D_004B2570, 4, 0);
    e = ((Ent *)UiEntryListGetCurrentData_28ec60(D_004DB1F0));
    if (r == 1) {
        D_00482394 = e->x12;
        if (g->xC->x26 == 1) {
            PartyMenuCursorSet_3c0710(g->x18, 0x16, (int)(D_00482394));
        }
        if (IsTgsDemoBuild_207f20() != 0) {
            if (e->x12 == 0) {
                D_004823A0 = e->x12 + 1;
                StateMachineSetState_28ede0(&D_00482350, 7, 0);
            }
        } else {
            D_004823A0 = e->x12 + 1;
            StateMachineSetState_28ede0(&D_00482350, 7, 0);
        }
    } else if (r == 2) {
        D_004823A0 = 0;
        D_00482394 = e->x12;
        if (g->xC->x26 == 1) {
            PartyMenuCursorSet_3c0710(g->x18, 0x16, (int)(D_00482394));
        }
        StateMachineSetState_28ede0(&D_00482350, 7, 0);
    }
    return 1;
}
