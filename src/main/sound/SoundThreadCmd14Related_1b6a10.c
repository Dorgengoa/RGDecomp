#include "types.h"
typedef struct P1B6A10 { s32 m00; s32 m04; s32 m08; } P1B6A10;
extern void SoundIopSendCmdG3S3_166020(s32 a, s32 b, s32 c);
void SoundThreadCmd14Related_1b6a10(P1B6A10 *p) { SoundIopSendCmdG3S3_166020(p->m00, p->m04, p->m08); }
