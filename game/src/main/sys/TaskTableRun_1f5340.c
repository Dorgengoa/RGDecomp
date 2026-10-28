/* rgp:protos */
#define RGP_SELF_TaskTableRun_1f5340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { s32 unk0; void (*unk4)(void); s32 pad[2]; } E;
/*rgp*/
/*rgp*/
/*rgp*/

s32 TaskTableRun_1f5340(E *arg0) {
    E *p;

    p = arg0;
    SetTaskListChanged_1f56b0(0);
    if (p == 0) {
        return 0;
    }
    while (p->unk0 != 0) {
        if (p->unk4 != 0) {
            if (((unsigned char)TaskTestFlag_1f57a0(p, 0)) != 0) {
                p->unk4();
                if (((unsigned char)GetTaskListChanged_1f56c0()) != 0) {
                    return 1;
                }
            }
        }
        p++;
    }
    return 0;
}
