/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_VideoDecMain_1d5240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B3330[];
extern s32 D_004B3340[];

void VideoDecMain_1d5240(void *arg0) {
    ViBufReset_1d45b0((u8 *)arg0 + 0x48);
    VoBufReset_1d4ab0(D_004B3330);
    VideoDecDecodeBs_1d29e0(arg0);
    while ((D_004B3340[0] != 0) && (rg_spin_hint(0x001D5274), 1)) {
        ThreadYield_1d2b70();
    }
    VideoDecSetState_1d2b60(arg0, 3);
}
