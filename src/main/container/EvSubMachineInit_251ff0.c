#include "types.h"

/* The index maths (sll 2 / addu / sll 4) is a *0x50 element stride. */

struct Elem {
    u8 pad000[0x50];
};

struct Obj0 {
    struct Elem *m00;
    s32 m04;
};

extern void EvtSubMachineReset_251f60(struct Obj0 *);
extern void EventSubNodeReset_2520d0(struct Elem *);

void EvSubMachineInit_251ff0(struct Obj0 *p0, struct Elem *p1, s32 p2)
{
    s32 i;

    p0->m00 = p1;
    p0->m04 = p2;
    EvtSubMachineReset_251f60(p0);
    if (p0->m00 != 0 && p0->m04 > 0) {
        for (i = 0; i < p0->m04; i++) {
            EventSubNodeReset_2520d0(&p0->m00[i]);
        }
    }
}
