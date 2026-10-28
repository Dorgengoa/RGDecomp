/* rgp:protos */
#define RGP_SELF_TrailRibbonIsVisible_32c850 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P32C850 { u8 pad000[0x10]; s32 m10; u8 pad014[0x4]; u32 m18; } P32C850;
s32 TrailRibbonIsVisible_32c850(P32C850 *p)
{
    return p->m10 != 0 && !((p->m18 & 0x80000000) != 0);
}
