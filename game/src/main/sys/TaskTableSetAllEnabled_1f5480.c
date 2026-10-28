/* rgp:protos */
#define RGP_SELF_TaskTableSetAllEnabled_1f5480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent_FUN_001f5480 {
    s32 f00;
    u8 pad004[0xC];
} Ent_FUN_001f5480;

/*rgp*/

void TaskTableSetAllEnabled_1f5480(Ent_FUN_001f5480 *p, s32 flag)
{
    if (p == 0) {
        return;
    }
    if (flag != 0) {
        while (p->f00 != 0) {
            TaskSetFlag_1f5750(p, 1, 0);
            p++;
        }
    } else {
        while (p->f00 != 0) {
            TaskSetFlag_1f5750(p, 0, 0);
            p++;
        }
    }
}
