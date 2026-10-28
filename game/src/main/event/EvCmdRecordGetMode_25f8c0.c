/* rgp:protos */
#define RGP_SELF_EvCmdRecordGetMode_25f8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_25f8c0;
struct T25f8c0 { s32 m00; };
struct O25f8c0 { s32 m00; u8 pad004[0xC]; s32 m10; };
struct M25f8c0 { u8 pad000[0x1188]; struct O25f8c0 *m1188; };
struct C25f8c0 { u8 pad000[0x24]; struct M25f8c0 *m24; };
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdRecordGetMode_25f8c0(E8_25f8c0 *p0, s32 p1)
{
    struct C25f8c0 *ctx;
    struct O25f8c0 *o;
    s32 a;
    s32 b;
    struct T25f8c0 *r;

    ctx = ((struct C25f8c0 *)GetGameData_1fede0());
    o = ctx->m24->m1188;
    a = o->m00;
    b = o->m10;
    if (p1 > 0) {
        ScriptSetRefInt_26a1e0(p0++, a);
    }
    if (p1 >= 2) {
        ScriptSetRefInt_26a1e0(p0++, b);
    }
    b = 0;
    if (a == 2) {
        r = ((struct T25f8c0 *)RecordGetPayloadIfKind14_430b90(ctx->m24));
        if (r != 0) {
            b = r->m00;
        }
    }
    if (p1 >= 3) {
        ScriptSetRefInt_26a1e0(p0, b);
    }
    return 1;
}
