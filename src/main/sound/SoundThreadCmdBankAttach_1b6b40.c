#include "types.h"
typedef struct P1B6B40 { s32 m00; s32 m04; s32 m08; } P1B6B40;
extern void SoundIopSendCmdG1S0_165828(s32 a, s32 b, s32 c, s32 d);
void SoundThreadCmdBankAttach_1b6b40(P1B6B40 *p) { SoundIopSendCmdG1S0_165828(5, p->m00, p->m04, p->m08); }
