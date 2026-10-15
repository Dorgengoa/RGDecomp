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

extern const u8 D_00477600;

extern Ctx  *func_1FEDE0(void);
extern void  func_3FCF00(Query *q, Ctx *c, s32 a, s32 b, s32 d, s32 e, s32 f, s32 g);
extern void  func_370170(Iter *it, Query *q);
extern Ent  *func_370040(Iter *it);
extern void  func_3CCB70(void *p, s32 k, s32 a, s32 b);

s32 normal_TransHunterBountyMarkReported_51e480(void)
{
    Iter   it;
    Query  q;
    Ctx   *c;
    Ent   *e;

    c = func_1FEDE0();
    q.f00 = &D_00477600;
    func_3FCF00(&q, c, 1, 1, 0, 0, 1, 0);
    func_370170(&it, &q);
    while ((e = func_370040(&it)) != NULL) {
        func_3CCB70(c->f10, e->f12, 1, 0);
    }
    return 1;
}
