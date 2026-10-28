/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSetMasterVolume_1b6ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1B6AE0 { s32 m00; s32 m04; } P1B6AE0;
/*rgp*/
void SoundThreadCmdSetMasterVolume_1b6ae0(P1B6AE0 *p) { SoundIopSendCmdG0S2_1656b8(3, 0x80, p->m00, p->m04); }
