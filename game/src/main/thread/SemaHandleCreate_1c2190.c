/* rgp:protos */
#define RGP_SELF_SemaHandleCreate_1c2190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Sema1C2190 { s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; };
struct T1C2190 { s32 f00; };

extern s32 CreateSema(struct Sema1C2190 *s);

void SemaHandleCreate_1c2190(struct T1C2190 *p)
{
    struct Sema1C2190 s __attribute__((aligned(16)));

    if (p->f00 > 0) return;
    s.f08 = 1;
    s.f04 = 1;
    s.f14 = 0;
    p->f00 = CreateSema(&s);
}
