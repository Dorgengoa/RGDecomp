/* rgp:protos */
#define RGP_SELF_EvCmdCastSetRot_247d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8d00 {
    s32 a;
    s32 b;
} E8d00;

typedef struct Ctxd00 {
    u8 pad000[0x4];
    u8 *m4;
} Ctxd00;

typedef struct Locd00 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Locd00;

extern Ctxd00 *gEventContext;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCastSetRot_247d00(E8d00 *q)
{
    Locd00 tmp __attribute__((aligned(16)));
    void *b;
    void *a;
    u8 *ctx;

    ctx = gEventContext->m4 + 0x60;
    a = ScriptGetCodeAddr_249050(q++);
    b = EventCastFindKeyByName_24bb50(ctx, a);
    TaggedGetVec3_249070(&tmp, q);
    EventCastObjSetRot_24a7e0(ctx, b, &tmp);
    return 1;
}
