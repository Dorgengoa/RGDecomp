#include "types.h"
/* normal 0x00519710 -- leaves the shop's browse mode: drops the held item,
 * re-arms the 0x75A2 cursor and returns to phase 3.  Pass-33 LIST rank:
 * 60 bytes, 15 instructions, ZERO branches, 4 calls -- a registration LIST.
 *
 * `D_0048480C = 0;` is written BEFORE func_37B460 in the source, which is what
 * sinks its `sb` into that call's delay slot. */

extern s8 D_0048480C;             /* gp - 0x964 */

extern void func_37B460(s32 id);
extern void func_37B800(s32 a);
extern void func_37B9E0(s32 a);
extern void normal_TransSaveShowMsg_519ff0(s32 phase);

extern s32 normal_TransSaveCardScanEnterCb_519710(void);

s32 normal_TransSaveCardScanEnterCb_519710(void)
{
    func_37B800(-1);
    D_0048480C = 0;
    func_37B460(0x75A2);
    func_37B9E0(0);
    normal_TransSaveShowMsg_519ff0(3);
    return 1;
}
