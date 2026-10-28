/* rgp:protos */
#define RGP_SELF_TaskEntryOfDebugItem_208c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T208C00 { u8 pad000[0x30]; void **f30; };

/*rgp*/

s32 TaskEntryOfDebugItem_208c00(struct T208C00 *p)
{
    void **base;
    void **q;
    void *v;

    base = p->f30;
    if (base == 0) return 0;
    q = base;
    while ((v = *q) != 0) {
        if (p == v) {
            return TaskTableGetEntry_27c2e0(q - base);
        }
        q++;
    }
    return 0;
}
