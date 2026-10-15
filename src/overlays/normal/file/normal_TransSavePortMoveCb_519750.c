#include "types.h"
/* normal 0x00519750 -- reads one s16 member twice, hands it to two callees,
 * publishes a byte state to the gp global at 0x00484808 and returns 1. */
typedef struct N {
    u8  pad000[0x12];
    s16 f12;
} N;

extern u8 D_00484808;

extern void func_37B7C0(s16 id);
extern void normal_TransSavePortCursorBob_5187c0(s16 id, s32 a, s32 b);

s32 normal_TransSavePortMoveCb_519750(N *p)
{
    func_37B7C0(p->f12);
    normal_TransSavePortCursorBob_5187c0(p->f12, 0, 1);
    D_00484808 = 5;
    return 1;
}
