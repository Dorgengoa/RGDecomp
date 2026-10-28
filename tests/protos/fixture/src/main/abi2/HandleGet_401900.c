#include "types.h"
/* rule short-agg (2026-10-25): a definition taking a word-size union BY VALUE (one GPR on
   the EE, one 4-byte slot on i686) is kept out of game_protos.h, so a caller's short local
   view used to stay short (HandleTableGet_1a1d50 / EffDefDestroy_1a0a90) */
typedef union Handle {
    s32 w;
    struct {
        s16 idx;
        u16 gen;
    } f;
} Handle;

typedef struct Table {
    s32 n;
    u16 gen;
    void *e[4];
} Table;

void **HandleGet_401900(Table *t, Handle h)
{
    if (h.f.idx < 0 || h.f.idx >= t->n || h.f.gen != t->gen) {
        return 0;
    }
    return &t->e[h.f.idx];
}
