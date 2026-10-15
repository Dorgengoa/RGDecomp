#include "types.h"
/* SEVEN integer arguments -- the EE ABI passes them in $4-$11. */
typedef struct P1B6540 { s32 m00; s32 m04; s32 m08; s32 m0C; s32 m10; s32 m14; } P1B6540;
extern void sceSdRemote_1229e8(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
void SoundThreadCmdSdRemote_1b6540(P1B6540 *p)
{
    sceSdRemote_1229e8(1, p->m00, p->m04, p->m08, p->m0C, p->m10, p->m14);
}
