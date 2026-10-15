#include "types.h"

extern void NavMgrPoolReset_2d1980(void *);
extern void NavMgrPoolDtor_2d1a20(void *, s32);
extern void UskMemoryRefDtor_42d020(void *);
extern void OperatorDelete_100840(void *);

void *NavMgrDtor_2d19a0(void *p, s32 flags)
{
    if (p != 0) {
        if ((u8 *)p + 4 != 0) {
            NavMgrPoolReset_2d1980((u8 *)p + 4);
            NavMgrPoolDtor_2d1a20((void *)((s32)p + 4), 0);
        }
        if (p != 0) {
            UskMemoryRefDtor_42d020(p);
        }
        if ((s16)flags > 0) {
            OperatorDelete_100840(p);
        }
    }
    return p;
}
