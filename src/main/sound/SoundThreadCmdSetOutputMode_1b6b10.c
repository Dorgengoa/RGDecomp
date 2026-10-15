#include "types.h"
extern void SoundIopSendCmdG1S2_1659a8(s32 a, s32 b, s32 c);
typedef struct P1B6B10 { s32 m00; } P1B6B10;
void SoundThreadCmdSetOutputMode_1b6b10(P1B6B10 *p) { SoundIopSendCmdG1S2_1659a8(0, 0x71, p->m00); }
