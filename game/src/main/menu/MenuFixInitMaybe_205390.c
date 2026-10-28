/* rgp:protos */
#define RGP_SELF_MenuFixInitMaybe_205390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *, s32, s32);
extern void strcpy(u8 *, u8 *);
extern u32 strlen(u8 *);
extern u8 D_0045C430[];
extern s32 D_00481B94;
extern s32 D_00481B98;
extern s32 D_00481B9C;
extern u8 D_00481BA0[4];
extern s32 D_00481BA8;
extern s32 D_00481BAC;
extern s32 D_00481BC0;
extern s32 D_00481BC4;
extern s32 D_00481BC8;
extern s32 D_00481BCC;
extern s32 D_00481BD0;
extern s32 D_00481BD4;
extern s32 D_00481BD8;
extern s32 D_00481BDC;
extern s32 D_00481BE0;
extern s32 D_00481BE4;
extern s32 D_00481BE8;
extern s32 D_00481BEC;
extern s32 D_00481BF0;
extern s32 D_00481BF4;
extern s32 D_00481BF8;
extern s32 D_00481BFC;
extern s32 D_00481C58;
extern s32 D_00481C5C;
extern u8 D_004BB950[];
extern u8 D_004BBB60[];
extern u8 D_004BBBC0[];
extern u8 D_004BBC80[];
extern u8 D_004BBCE0[];
extern u8 D_004BBD40[];
extern u8 D_004BBDA0[];
extern u8 D_004BBE00[];
extern u8 D_004BBE60[];
extern u8 D_004BBEC0[];
extern u8 D_004BBF20[];
extern u8 D_004BBF80[];
extern u8 D_004BBFE0[];
extern u8 D_004BC470[];
extern u8 D_004BC6C0[];

void MenuFixInitMaybe_205390(s32 arg0)
{
    D_00481BA8 = 0;
    D_00481BAC = 0;
    D_00481C58 = 0;
    D_00481C5C = 0;
    MemStackClear_14dff0(D_004BBB60);
    MemStackClear_14dff0(D_004BBBC0);
    MemStackClear_14dff0(D_004BBC80);
    MemStackClear_14dff0(D_004BBCE0);
    MemStackClear_14dff0(D_004BBD40);
    MemStackClear_14dff0(D_004BBDA0);
    MemStackClear_14dff0(D_004BBE00);
    MemStackClear_14dff0(D_004BBE60);
    MemStackClear_14dff0(D_004BBEC0);
    MemStackClear_14dff0(D_004BBF20);
    MemStackClear_14dff0(D_004BBF80);
    MemStackClear_14dff0(D_004BBFE0);
    MemStackClear_14dff0(D_004BB950);
    D_00481BC0 = -1;
    D_00481B94 = 0x3F800000;
    D_00481BC4 = -1;
    D_00481BC8 = -1;
    D_00481BD0 = -1;
    D_00481BD8 = -1;
    D_00481BE0 = -1;
    D_00481BE4 = -1;
    D_00481BE8 = -1;
    D_00481BF8 = -1;
    D_00481BFC = -1;
    D_00481B9C = -1;
    D_00481BCC = 0;
    D_00481BD4 = 0;
    D_00481BDC = 0;
    D_00481BEC = 0;
    D_00481BF0 = 0;
    D_00481BF4 = 0;
    D_00481B98 = 0;
    HpGaugeReset_31e1e0(D_004BC470);
    HpGaugeReset_31e1e0(D_004BC6C0);
    if (arg0 != 0) {
        MemStackInit_14d810(D_004BBB60, MemStackAllocAligned64_14da10(arg0, 0xA500), 0xA500);
        if (strlen(D_0045C430) < 0x10U) {
            strcpy(D_004BBB60, D_0045C430);
        }
        MemStackReset_14d830(D_004BBB60);
        memset(D_00481BA0, 0, 4);
    }
}
