#include "types.h"
/* normal 0x005247D0 -- opens the shop's stream: takes the 0x32D slot, asks for
 * the file, and tears the reader down again if the request was refused.
 * Pass-33 LIST rank: 116 bytes, 29 instructions, ONE conditional branch,
 * 5 calls.  `bne` is a PLAIN branch, so `D_004807B8 = r;` in its delay slot
 * runs on both paths and the guard is only the early `return 1`. */

extern s32   D_004802C0;          /* gp - 0x4EB0 */
extern s32   D_004807B8;          /* gp - 0x49B8 */
extern s32   D_004807BC;          /* gp - 0x49B4 */

extern void  func_158AC0(void *h, s32 id);
extern void *func_15DE40(void);
extern void  func_1CD670(void *h);
extern s32   func_1CD870(void *h, s32 id, s32 a);
extern void *func_1F59D0(void);

extern s32 normal_InsectEntryMenuResRequest_5247d0(void);

s32 normal_InsectEntryMenuResRequest_5247d0(void)
{
    void *q;
    s32   r;

    func_158AC0(func_15DE40(), 0x32D);
    q = func_1F59D0();
    D_004807B8 = -1;
    D_004807BC = 0;
    r = func_1CD870(q, D_004802C0, 0);
    D_004807B8 = r;
    if (r == -1) {
        return 1;
    }
    func_1CD670(q);
    return 0;
}
