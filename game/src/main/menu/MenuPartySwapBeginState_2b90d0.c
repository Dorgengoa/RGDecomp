/* rgp:protos */
#define RGP_SELF_MenuPartySwapBeginState_2b90d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct G {
    u8 pad[0x18];
    s32 m18;
} G;

typedef struct W {
    u8 pad[0x14];
    u16 m14;
    u16 m16;
} W;


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u16 D_004614C0[];
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s32 D_004823D8;
extern s16 D_0048253C;
extern s16 D_0048253E;
extern s16 D_00482554;
extern s16 D_0048255C;
extern s16 D_0048256C;

#define BIT2(p) ((u64)((s64)(*(u8 *)((u8 *)(p) + 0x234)) << 0x3D) >> 0x3F)

s32 MenuPartySwapBeginState_2b90d0(void)
{
    s8 *t;
    G *g;
    void *u;
    W *w;
    void *x;

    t = MenuGetCursorPos_29fae0(D_00482370);
    if (MenuPartyFadeSequenceStep_2b9240(0x183, 0x11B, D_004614C0[t[1]]) & 0xFF) {
        g = ((G *)GetGameData_1fede0());
        u = PartyGetSlotChara_3c2fb0(g->m18, t[0] + t[1] * PartyCountMembers_3c2010(g->m18, 1, 1));
        if (u == NULL) {
            return 0;
        }
        if (BIT2(u) != 0) {
            UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, 0x7D0), 0);
            D_00482554 = 0x4B;
            D_0048255C = 0;
            StateMachineSetState_28ede0(D_0048235C, 0x4D, 0);
        } else {
            w = ((W *)UiEntryListFindByTag_28ea40(D_00482364, 0x12));
            x = PartyGetReserveChara_3c1d20(g->m18, 0);
            w->m14 = 0;
            D_0048253C = 0;
            w->m16 = 0;
            D_0048253E = 1;
            if ((x != NULL) && (t[1] == 0) && (BIT2(x) == 0)) {
                w->m16 = 1;
                D_0048253E = 0;
            }
            D_0048256C = 0;
            StateMachineSetState_28ede0(D_0048235C, 0x52, 0);
        }
    }
    return 1;
}
