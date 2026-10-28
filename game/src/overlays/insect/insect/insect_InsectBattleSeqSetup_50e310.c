/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSeqSetup_50e310 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E310 -- 84 bytes, 21 instructions. */

typedef struct Obj {
    u8 pad00[0x558];
    u8 f558[4];                     /* +0x558 */
} Obj;

extern u8    insect_D_00524220[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleSeqSetup_50e310(Obj *o)
{
    void *p;

    p = insect_InsectSeqGet_5108d0();
    insect_InsectSeqInit_4ea550(p);
    insect_InsectSeqSetHeap_4ea530(p, o->f558);
    insect_InsectSeqSetHandlerTable_4ea490(p, insect_D_00524220);
}
