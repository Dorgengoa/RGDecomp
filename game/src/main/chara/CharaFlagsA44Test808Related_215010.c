/* rgp:protos */
#define RGP_SELF_CharaFlagsA44Test808Related_215010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T215010 { u8 pad000[0xA44]; u32 fA44; };

u8 CharaFlagsA44Test808Related_215010(struct T215010 *p)
{
    u32 v;
    u8 r;

    v = p->fA44;
    r = 1;
    if (v & 8) goto end;
    if (v & 0x800) goto end;
    r = 0;
end:
    return r;
}
