/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogAllocLines_51c540 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
extern void  memset(void *p, s32 c, s32 n);

void insect_InsectBattleLogAllocLines_51c540(Obj *o, s32 h)
{
    void *p;

    o->f00 = h;
    if (h != 0) {
        MemStackReset_14d830(h);
        p = ConstructNewArray_100710(MemStackNew_14e1b0(0x1C30, o->f00), 0, 0, 0x5A, 0x50);
        o->f04 = p;
        memset(p, 0, 0x1C20);
    }
}
