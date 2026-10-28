/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSpuTransferMaybe_1b6b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1B6B20 { s32 m00; s32 m04; s32 m08; s32 m0C; s32 m10; } P1B6B20;
/*rgp*/
void SoundThreadCmdSpuTransferMaybe_1b6b20(P1B6B20 *p) { SoundIopSendCmdG0SA_165778(p->m04, p->m08, p->m0C, p->m10); }
