#include "types.h"
/* insect 0x0051C540 -- 104 bytes, 26 instructions.
 *
 * o->f00 is stored, then RE-LOADED after func_14D830 (insect-load-across-store:
 * mwcc will not move the load past the call).  func_100710 takes FIVE
 * arguments -- the fifth is $8 under the PS2 EABI.
 */

typedef struct Obj {
    s32   f00;                      /* +0x00 */
    void *f04;                      /* +0x04 */
} Obj;

extern void  func_14D830(s32 h);
extern void *func_14E1B0(s32 a, s32 b);
extern void *func_100710(void *p, s32 a, s32 b, s32 c, s32 d);
extern void  func_131B60(void *p, s32 c, s32 n);

void insect_InsectBattleLogAllocLines_51c540(Obj *o, s32 h)
{
    void *p;

    o->f00 = h;
    if (h != 0) {
        func_14D830(h);
        p = func_100710(func_14E1B0(0x1C30, o->f00), 0, 0, 0x5A, 0x50);
        o->f04 = p;
        func_131B60(p, 0, 0x1C20);
    }
}
