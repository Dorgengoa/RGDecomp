/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSeqPlay_1b6ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1B6AB0 { s32 m00; s32 m04; } P1B6AB0;
/*rgp*/
void SoundThreadCmdSeqPlay_1b6ab0(P1B6AB0 *p) { SoundIopSendCmdG2S2_165c70(p->m00, 0, 0, p->m04); }
