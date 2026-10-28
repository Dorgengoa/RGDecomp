/* rgp:protos */
#define RGP_SELF_SoundStreamSlotOpenLoop_1bce80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u8 D_004814F0;
extern u8 D_004A25F0[0x400];

s32 SoundStreamSlotOpenLoop_1bce80(s32 arg0, void *rgp_a1)
{
    u8 *var_6;
    s32 x;

    if (arg0 < 0 || arg0 >= 4) {
        var_6 = NULL;
    } else {
        var_6 = D_004A25F0 + (arg0 * 0x128);
    }
    if ((var_6 == NULL) || (*(s32 *)(&D_004814F0 + (arg0 * 4)) == 0)) {
        var_6 = NULL;
    }
    if (var_6 == NULL) {
        return -1;
    }
    return ((unsigned char)SoundStreamSlotQueueOpen_1be8a0(var_6, (void *)rgp_a1, 1)) & 0xFF;
}
