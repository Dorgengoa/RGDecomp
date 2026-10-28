/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_DrawListInitDoubleBufMaybe_1427e0 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

typedef struct {
    s32 w[22];
} Body;

typedef struct {
    s32 h0;
    s32 h1;
    Body body;
} Blk;

typedef struct {
    u8 pad0[8];
    Blk *p8;
    Blk *pC;
    Blk a;
    Blk b;
} Obj;

/*rgp*/

void DrawListInitDoubleBufMaybe_1427e0(Obj *arg0, Blk *arg1, Blk *arg2)
{
    s32 n1;
    s32 n2;
    s32 k1;
    s32 k2;

    arg0->a.h0 = arg1->h0;
    arg0->a.h1 = arg1->h1;
    arg0->a.body = arg1->body;
    arg0->b.h0 = arg2->h0;
    arg0->b.h1 = arg2->h1;
    arg0->b.body = arg2->body;
    n1 = arg1->body.w[11];
    k1 = arg1->body.w[10] + n1 * 16;
    n2 = arg2->body.w[11];
    k2 = arg2->body.w[10] + n2 * 16;
    { s32 t = arg1->body.w[13] - n1; MemStackInit_14d810(&arg0->a.body, (k1), t); }
    MemStackInit_14d810(&arg0->b.body, (k2), arg2->body.w[13] - arg2->body.w[11]);
    arg0->p8 = &arg0->a;
    arg0->pC = &arg0->b;
}
