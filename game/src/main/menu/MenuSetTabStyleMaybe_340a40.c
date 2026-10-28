/* rgp:protos */
#define RGP_SELF_MenuSetTabStyleMaybe_340a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_00462780[3][8];
extern s16 D_004627B0[3][8];
extern s16 D_004627E0[];

s32 MenuSetTabStyleMaybe_340a40(u8 *arg0, s32 arg1, s32 arg2)
{
    s32 k;
    u8 *p;
    s16 *q;

    if (((s32)GetGameData_1fede0()) == 0) {
        return 1;
    }
    if (arg2 == 0) {
        k = 0;
    } else if (arg2 == 7) {
        k = 2;
    } else {
        k = 1;
    }
    p = ((u8 *)UiFindWidget_290460(*(s32 *)(arg0 + 0x5C), arg1));
    if (p == 0) {
        return 0;
    }
    q = *(s16 **)(p + 0x20);
    if (q == 0) {
        return 0;
    }
    q[0x10] = D_00462780[k][0];
    q[0x11] = D_00462780[k][1];
    q[0x12] = D_00462780[k][2];
    q[0x13] = D_00462780[k][3];
    q[0x14] = D_00462780[k][4];
    q[0x15] = D_00462780[k][5];
    q[0x16] = D_00462780[k][6];
    q[0x17] = D_00462780[k][7];
    q[0x20] = D_004627B0[k][0];
    q[0x21] = D_004627B0[k][1];
    q[0x22] = D_004627B0[k][2];
    q[0x23] = D_004627B0[k][3];
    q[0x24] = D_004627B0[k][4];
    q[0x25] = D_004627B0[k][5];
    q[0x26] = D_004627B0[k][6];
    q[0x27] = D_004627B0[k][7];
    if (k == 0) {
        p = ((u8 *)UiFindWidget_290460(*(s32 *)(arg0 + 0x5C), 0x18A));
        if (p == 0) {
            return 0;
        }
        q = *(s16 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        q[0x17] = 0;
        q[0x13] = 0;
        q[0x16] = 0;
        q[0x12] = 0;
    } else {
        p = ((u8 *)UiFindWidget_290460(*(s32 *)(arg0 + 0x5C), 0x18A));
        if (p == 0) {
            return 0;
        }
        q = *(s16 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        q[0x17] = 0xE;
        q[0x13] = 0xE;
        q[0x16] = 0xE;
        q[0x12] = 0xE;
    }
    if (k == 2) {
        p = ((u8 *)UiFindWidget_290460(*(s32 *)(arg0 + 0x5C), 0x18A));
        if (p == 0) {
            return 0;
        }
        q = *(s16 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        q[0x67] = 0;
        q[0x63] = 0;
        q[0x66] = 0;
        q[0x62] = 0;
    } else {
        p = ((u8 *)UiFindWidget_290460(*(s32 *)(arg0 + 0x5C), 0x18A));
        if (p == 0) {
            return 0;
        }
        q = *(s16 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        q[0x67] = 0xE;
        q[0x63] = 0xE;
        q[0x66] = 0xE;
        q[0x62] = 0xE;
    }
    UiSetWidgetPos_290f60(*(s32 *)(arg0 + 0x5C), arg1, D_004627E0[arg2], 0x10);
    return 0;
}
