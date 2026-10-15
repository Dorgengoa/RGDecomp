#include "types.h"

typedef struct E8c80 {
    s32 a;
    s32 b;
} E8c80;

typedef struct Ctxc80 {
    u8 pad000[0x4];
    u8 *m4;
} Ctxc80;

typedef struct Locc80 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Locc80;

extern Ctxc80 *gEventContext;
extern void *ScriptGetCodeAddr_249050(E8c80 *p);
extern void *EventCastFindKeyByName_24bb50(u8 *ctx, void *a);
extern void TaggedGetVec3_249070(Locc80 *dst, E8c80 *p);
extern void EventCastObjSetScale_24a6b0(u8 *ctx, void *b, Locc80 *tmp);

s32 EvCmdCastSetScale_247c80(E8c80 *q)
{
    Locc80 tmp;
    void *b;
    void *a;
    u8 *ctx;

    ctx = gEventContext->m4 + 0x60;
    a = ScriptGetCodeAddr_249050(q++);
    b = EventCastFindKeyByName_24bb50(ctx, a);
    TaggedGetVec3_249070(&tmp, q);
    EventCastObjSetScale_24a6b0(ctx, b, &tmp);
    return 1;
}
