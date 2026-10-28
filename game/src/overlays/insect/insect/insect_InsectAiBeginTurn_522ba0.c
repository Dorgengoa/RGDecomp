/* rgp:protos */
#define RGP_SELF_insect_InsectAiBeginTurn_522ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522BA0 -- 144 bytes, 36 instructions, 2 calls.  Two separate
 * five-element fill loops; each re-materialises its own counter and its own
 * -1, so they are two statements and not one loop over a 2x5 grid. */

typedef struct Obj {
    s32 m00[5];                     /* +0x00 */
    s32 m14[5];                     /* +0x14 */
    u8  pad28[0x48 - 0x28];
    s32 m48;                        /* +0x48 */
    s32 m4C;                        /* +0x4C */
    u8  pad50[0x64 - 0x50];
    s32 m64;                        /* +0x64 */
    s32 m68;                        /* +0x68 */
} Obj;

/*rgp*/
/*rgp*/

void insect_InsectAiBeginTurn_522ba0(Obj *o)
{
    s32 i;

    o->m48 = 0;
    o->m4C = 0;
    for (i = 0; i < 5; i++) {
        o->m00[i] = -1;
    }
    for (i = 0; i < 5; i++) {
        o->m14[i] = -1;
    }
    insect_InsectAiPushState_5229e0(o, 1);
    insect_InsectAiPushStep_522930(o, 0);
    o->m64 = 0;
    o->m68 = 0;
}
