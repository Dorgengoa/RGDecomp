/* rgp:protos */
#define RGP_SELF_CBlurTexRegisterWork_1791e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S001791e0 {
    u8 pad0[4];
    s32 unk4;
    char name0[0x20];
    char name1[0x20];
    char name2[0x20];
    s32 unk68;
    s32 unk6C;
    f32 unk70;
} S001791e0;

typedef struct Ctx791e0 {
    u8 pad0[0x3BA0];
    s32 unk3BA0;
} Ctx791e0;

extern void Sprintf_1343b8(char *, char *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_00459620[];
extern char D_00459638[];
extern char D_00459650[];
extern f32 D_0047D3B4 __attribute__((section(".sdata")));
extern s32 D_004811A8;

void CBlurTexRegisterWork_1791e0(S001791e0 *arg0, s32 arg1) {
    Ctx791e0 *c;
    s32 w;
    s32 h;
    s32 m;

    arg0->unk4 = arg1;
    c = ((Ctx791e0 *)GetDrawCtx_15de80());
    m = c->unk3BA0;
    Sprintf_1343b8(arg0->name0, D_00459620, D_004811A8);
    Sprintf_1343b8(arg0->name1, D_00459638, D_004811A8);
    Sprintf_1343b8(arg0->name2, D_00459650, D_004811A8);
    D_004811A8++;
    if (D_004811A8 > 9999) {
        D_004811A8 = 0;
    }
    w = DrawEnvGetWidth_1451e0(c);
    h = DrawEnvGetHeight_1451d0(c);
    arg0->unk6C = 0;
    NameTableAddEntry_159b70(m, 0x7FFF, arg0->name0, 0, 0x40, 0x40, 0x20, 0, 0, (int)(0));
    NameTableAddEntry_159b70(m, arg0->unk4, arg0->name1, 0, 0x40, 0x40, 0x20, 0, 0, (int)(0));
    NameTableAddEntry_159b70(m, arg0->unk4, arg0->name2, 0, w, h, 0x20, 0, 0, (int)(0));
    arg0->unk68 = 1;
    arg0->unk70 = D_0047D3B4;
}
