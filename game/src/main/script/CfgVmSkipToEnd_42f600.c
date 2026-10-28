/* rgp:protos */
#define RGP_SELF_CfgVmSkipToEnd_42f600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T42F600 { u8 pad000[0x420]; void *f420; };

/*rgp*/

void *CfgVmSkipToEnd_42f600(struct T42F600 *p)
{
    void *last;

    do {
        last = p->f420;
    } while (((s32)CfgVmStep_42f6e0(p, 0)) != 0);
    return last;
}
