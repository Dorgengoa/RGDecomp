#include "types.h"
/* insect 0x004EFF10 -- 132 bytes, 33 instructions.  The script-runner context
 * global D_00484F58 (at _gp-0x218, inside the gp window, so it must stay a
 * plain extern) is RE-READ after every call, so each use is written off the
 * global and not off a hoisted local. */

typedef struct Ctx {
    void *m00;                      /* +0x00 */
    void *m04;                      /* +0x04 */
    s32   m08;                      /* +0x08 */
    u8    pad0C[0x10 - 0xC];
    s32   m10;                      /* +0x10 */
} Ctx;

extern Ctx *D_00484F58;

extern void  func_14D830(void *h);
extern s32   func_15F780(void *p);
extern void *func_14E230(s32 n, void *h);

s32 insect_InsectFormationParseFormNum_4eff10(void *p)
{
    if (D_00484F58->m04 == 0) {
        return 0;
    }
    func_14D830(D_00484F58->m04);
    D_00484F58->m08 = func_15F780(p);
    if (D_00484F58->m08 <= 0) {
        return 0;
    }
    D_00484F58->m00 = func_14E230(5, D_00484F58->m04);
    D_00484F58->m10 = 0;
    return 1;
}
