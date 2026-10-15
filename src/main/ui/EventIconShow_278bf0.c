#include "types.h"

typedef struct Tail_00278bf0 {
    u8 pad[0x400];
    s32 unk400;
} Tail_00278bf0;

extern void EventIconTableReset_278b40(void *arg0);
extern void TaskSetEnabled_27c2a0(s32 a, const u8 *b);
extern u8 D_0045F910[];
extern Tail_00278bf0 *D_0047E9AC;

void EventIconShow_278bf0(void *self, s32 arg1)
{
    if (D_0047E9AC != 0) {
        EventIconTableReset_278b40(D_0047E9AC);
        D_0047E9AC->unk400 = arg1;
        TaskSetEnabled_27c2a0(1, D_0045F910);
    }
}
