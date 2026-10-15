#include "types.h"
/* insect 0x0050E310 -- 84 bytes, 21 instructions. */

typedef struct Obj {
    u8 pad00[0x558];
    u8 f558[4];                     /* +0x558 */
} Obj;

extern u8    D_00524220[];
extern void *insect_InsectSeqGet_5108d0(void);
extern void  insect_InsectSeqInit_4ea550(void *p);
extern void  insect_InsectSeqSetHeap_4ea530(void *p, void *q);
extern void  insect_InsectSeqSetHandlerTable_4ea490(void *p, void *q);

void insect_InsectBattleSeqSetup_50e310(Obj *o)
{
    void *p;

    p = insect_InsectSeqGet_5108d0();
    insect_InsectSeqInit_4ea550(p);
    insect_InsectSeqSetHeap_4ea530(p, o->f558);
    insect_InsectSeqSetHandlerTable_4ea490(p, D_00524220);
}
