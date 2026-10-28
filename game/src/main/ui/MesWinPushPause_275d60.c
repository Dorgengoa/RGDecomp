/* rgp:protos */
#define RGP_SELF_MesWinPushPause_275d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Big_FUN_00275d60 {
    u8 pad0[0x18C4];
    s16 arr1[0x10];   /* +0x18C4 */
    s32 arr2[0x10];   /* +0x18E4 */
    s16 cnt;          /* +0x1924 */
} Big_FUN_00275d60;

void MesWinPushPause_275d60(Big_FUN_00275d60 *arg0, s16 arg1, s32 arg2)
{
    if (arg0->cnt < 0x10) {
        arg0->arr1[arg0->cnt] = arg1;
        arg0->arr2[arg0->cnt] += arg2;
        arg0->cnt = arg0->cnt + 1;
    }
}
