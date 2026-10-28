/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSetOutputMode_1b6b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
typedef struct P1B6B10 { s32 m00; } P1B6B10;
void SoundThreadCmdSetOutputMode_1b6b10(P1B6B10 *p) { SoundIopSendCmdG1S2_1659a8(0, 0x71, p->m00); }
