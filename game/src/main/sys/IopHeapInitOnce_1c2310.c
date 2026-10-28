/* rgp:protos */
#define RGP_SELF_IopHeapInitOnce_1c2310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 CreateSema(void *arg0);
extern void sceSifInitIopHeap(void);
extern s32 D_00481510;
extern s32 D_00481514;

s32 IopHeapInitOnce_1c2310(void)
{
    s32 buf[6] __attribute__((aligned(16)));
    s32 temp_2;

    if (D_00481510 != 0) {
        return 0;
    }
    buf[2] = 1;
    buf[1] = 1;
    buf[5] = 0;
    temp_2 = CreateSema(&buf[0]);
    D_00481514 = temp_2;
    if (temp_2 < 0) {
        return 0;
    }
    sceSifInitIopHeap();
    D_00481510 = 1;
    return 1;
}
