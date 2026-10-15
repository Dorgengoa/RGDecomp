#include "types.h"
/* normal 0x00505A50 -- writes one 0xAC record header; the row index is scaled
 * by 24 (sll 1 / addu / sll 3) and the fourth argument is widened into an s64
 * FIELD (dsll32/dsra32 0), not cast in the source.  Every path returns 0. */

typedef struct Rec  { s16 f00; s16 f02; u8 pad04[4]; s64 f08; } Rec;
typedef struct Hold { u8 pad000[0x24]; Rec *f024; } Hold;

extern void *normal_UiPageGetLayout_289b60(void *p);
extern Hold *func_290460(void *p, u16 id);

s32 normal_BtlChgPageRowTextLayout_505a50(void *a, u16 id, s32 c, s32 d)
{
    void *w;
    Hold *h;
    Rec  *m;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    h = func_290460(w, id);
    if (h == 0) {
        return 0;
    }
    m = h->f024;
    if (m == 0) {
        return 0;
    }
    m->f00 = 0xAC;
    m->f02 = c * 24 + 0xC;
    m->f08 = d;
    return 0;
}
