/* rgp:protos */
#define RGP_SELF_normal_TransSavePortMoveCb_519750 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519750 -- reads one s16 member twice, hands it to two callees,
 * publishes a byte state to the gp global at 0x00484808 and returns 1. */
typedef struct N {
    u8  pad000[0x12];
    s16 f12;
} N;

extern u8 D_00484808;

/*rgp*/
/*rgp*/

s32 normal_TransSavePortMoveCb_519750(N *p)
{
    SaveSetPort_37b7c0(p->f12);
    normal_TransSavePortCursorBob_5187c0(p->f12, 0, 1);
    D_00484808 = 5;
    return 1;
}
