/* rgp:protos */
#define RGP_SELF_SoundStreamLockAcquire_1bfb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S1BFB40 { u8 pad000[0x7C]; s32 f7C; u8 f80; };
struct T1BFB40 { struct S1BFB40 *f00; };

extern s32 WaitSema(s32 sema);

struct S1BFB40 *SoundStreamLockAcquire_1bfb40(struct T1BFB40 *p)
{
    struct S1BFB40 *q;

    q = p->f00;
    if (q != 0) {
        if (q->f80 == 0) {
            if (*(volatile s32 *)&q->f7C > 0) {
                WaitSema(q->f7C);
            }
        }
        q->f80 = 1;
    }
    return p->f00;
}
