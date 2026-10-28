/* rgp:protos */
#define RGP_SELF_TreasureBoxRunAreaScript_278cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
/*rgp*/

extern char D_004D77B0[];
extern u8   D_0045F920[];
extern u8   D_0045F930[];
extern u8   D_0045F940[];
extern s8   D_0047E9A8;
extern s8   D_0048217C;

void TreasureBoxRunAreaScript_278cb0(void *self)
{
    s32 id;
    void *g;
    u8 *ctx;
    void *w;
    void *r;

    ctx = (u8 *)GetGameData_1fede0();
    id = *(s16 *)(*(u8 **)(ctx + 0x18) + 6);
    g = GetMapMgr_201a90();
    r = MapFindAreaSlotById_1e4cb0(g, id);
    if (r == 0) {
        return;
    }
    w = MapAreaGetScript_1dced0(r);
    if (w == 0) {
        return;
    }
    MemStackReset_14d830(D_004D77B0);
    SystemVmLoadScript_250ac0(w, 0, D_004D77B0);
    if (SystemVmCall_250a50(0x190, self, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) == 0) {
        SetFieldControlActive_27bd30(1);
        D_0048217C = 3;
    } else {
        void *p;
        s32 id2;
        void *g2;
        D_0047E9A8 = 0;
        *(s16 *)((u8 *)self + 0x58B4) = 0;
        *(s16 *)((u8 *)self + 0x58B6) = 0;
        D_0048217C = 4;
        SetFieldControlActive_27bd30(0);
        TaskSetEnabled_27c2a0(1, D_0045F920);
        TaskSetEnabled_27c2a0(1, D_0045F930);
        TaskSetEnabled_27c2a0(1, D_0045F940);
        id2 = *(s16 *)(*(u8 **)(ctx + 0x18) + 0x18E);
        g2 = GetActionMgr_1fdb50();
        p = ActionMgrFindById_233b50(g2, id2);
        if (p != 0) {
            *(s32 *)((u8 *)p + 0xA44) |= 0x10000000;
            *(s32 *)((u8 *)p + 0xA44) |= 0x08000000;
        }
    }
}
