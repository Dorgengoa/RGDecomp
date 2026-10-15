#include "types.h"
typedef struct P1B6B20 { s32 m00; s32 m04; s32 m08; s32 m0C; s32 m10; } P1B6B20;
extern void SoundIopSendCmdG0SA_165778(s32 a, s32 b, s32 c, s32 d);
void SoundThreadCmdSpuTransferMaybe_1b6b20(P1B6B20 *p) { SoundIopSendCmdG0SA_165778(p->m04, p->m08, p->m0C, p->m10); }
