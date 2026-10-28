/* rgp:protos */
#define RGP_SELF_CfgVmCopyStringPoolMaybe_42f500 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
extern void memcpy(s32, s32, s32);
struct Obj1 { u8 pad000[0x8]; s32 m08; };
struct Obj0 { u8 pad000[0x410]; s32 m410; u8 pad414[0x4]; s32 m418; s32 m41C; };

s32 CfgVmCopyStringPoolMaybe_42f500(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj1 *o;
    s32 len;
    s32 r1;

    if (p1 == 0 || p0->m418 == 0) {
        return 0;
    }
    o = (struct Obj1 *)p0->m410;
    len = o->m08;
    r1 = ArenaAllocAligned_370330(p1, len, p2, p3);
    p0->m41C = r1;
    if (r1 != 0) {
        memcpy(r1, p0->m418, len);
    }
    return p0->m41C;
}
