#include "types.h"

typedef struct E { s32 unk0; void (*unk4)(void); s32 pad[2]; } E;
extern void SetTaskListChanged_1f56b0(s32);
extern s32 GetTaskListChanged_1f56c0(void);
extern s32 TaskTestFlag_1f57a0(E *, s32);

s32 TaskTableRun_1f5340(E *arg0) {
    E *p;

    p = arg0;
    SetTaskListChanged_1f56b0(0);
    if (p == 0) {
        return 0;
    }
    while (p->unk0 != 0) {
        if (p->unk4 != 0) {
            if (TaskTestFlag_1f57a0(p, 0) != 0) {
                p->unk4();
                if (GetTaskListChanged_1f56c0() != 0) {
                    return 1;
                }
            }
        }
        p++;
    }
    return 0;
}
