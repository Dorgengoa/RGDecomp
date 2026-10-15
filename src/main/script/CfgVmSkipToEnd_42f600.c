#include "types.h"

struct T42F600 { u8 pad000[0x420]; void *f420; };

extern s32 CfgVmStep_42f6e0(struct T42F600 *p, s32 a);

void *CfgVmSkipToEnd_42f600(struct T42F600 *p)
{
    void *last;

    do {
        last = p->f420;
    } while (CfgVmStep_42f6e0(p, 0) != 0);
    return last;
}
