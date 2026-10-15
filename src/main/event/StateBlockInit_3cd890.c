#include "types.h"

extern void StateBlockReset_3cd670(void *);

extern s32 D_004838C0;
extern s32 D_004838C4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m4;
};

void StateBlockInit_3cd890(struct Obj0 *p0)
{
    D_004838C0 = 0;
    D_004838C4 = 0;
    p0->m4 = 0;
    StateBlockReset_3cd670(p0);
}
