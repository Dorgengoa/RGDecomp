#include "types.h"
typedef struct P1B6AB0 { s32 m00; s32 m04; } P1B6AB0;
extern void SoundIopSendCmdG2S2_165c70(s32 a, s32 b, s32 c, s32 d);
void SoundThreadCmdSeqPlay_1b6ab0(P1B6AB0 *p) { SoundIopSendCmdG2S2_165c70(p->m00, 0, 0, p->m04); }
