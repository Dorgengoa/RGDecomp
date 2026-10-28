/* rgp:protos */
#define RGP_SELF_iSetAlarm 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void func_076160(s32);

void iSetAlarm(s32 id)
{
    func_076160(id & 0xFFFF);
    { /* [port] vu0asm: asm block -> VU0 model */
/* sync */
}
}
