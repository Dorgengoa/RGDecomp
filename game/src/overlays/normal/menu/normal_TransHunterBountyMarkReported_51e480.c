/* rgp:protos */
#define RGP_SELF_normal_TransHunterBountyMarkReported_51e480 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051E480 -- builds a query record on the stack, opens an iterator
 * over it and pushes every hit through func_3CCB70.
 * Frame -0x40: `sq $16` at 0x00 + `sd $31` at 0x10 is the whole save area
 * (0x00-0x1F), so the two locals occupy 0x20 (query, 0x18 B) and 0x38 (Iter,
 * 8 B) -- REVERSE declaration order, hence Iter is declared FIRST. */

typedef struct Iter { u8 pad00[0x8]; } Iter;

typedef struct Query {
    const u8 *f00;
    u8        pad04[0x14];
} Query;                                        /* 0x18 */

typedef struct Ctx {
    u8    pad00[0x10];
    void *f10;
} Ctx;

typedef struct Ent {
    u8  pad00[0x12];
    s16 f12;
} Ent;

extern u8 D_00477600;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterBountyMarkReported_51e480(void)
{
    Iter   it __attribute__((aligned(16)));
    Query  q __attribute__((aligned(16)));
    Ctx   *c;
    Ent   *e;

    c = ((Ctx *)GetGameData_1fede0());
    q.f00 = &D_00477600;
    HunterBountyIterInit_3fcf00(&q, c, 1, 1, 0, 0, 1, 0);
    IterInit_370170(&it, &q, 0, 0);
    while ((e = ((Ent *)IterNext_370040(&it))) != NULL) {
        StateFlagSet_3ccb70(c->f10, e->f12, 1, 0);
    }
    return 1;
}
