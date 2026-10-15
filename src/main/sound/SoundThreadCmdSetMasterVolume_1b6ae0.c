#include "types.h"
typedef struct P1B6AE0 { s32 m00; s32 m04; } P1B6AE0;
extern void SoundIopSendCmdG0S2_1656b8(s32 a, s32 b, s32 c, s32 d);
void SoundThreadCmdSetMasterVolume_1b6ae0(P1B6AE0 *p) { SoundIopSendCmdG0S2_1656b8(3, 0x80, p->m00, p->m04); }
