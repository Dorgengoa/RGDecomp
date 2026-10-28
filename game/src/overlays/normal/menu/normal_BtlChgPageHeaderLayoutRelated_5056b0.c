/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageHeaderLayoutRelated_5056b0 1
#include "port/game_protos.h"
#line 1
/* NORMAL 0x005056B0, 268 bytes. Private exact candidate, 2026-09-17.
 * Five six-byte geometry records occupy independent eight-byte stack slots.
 * Preserve the two-byte source alignment and first record's const lvalue
 * view: they determine copy width, retention, and scheduling in MWCC 3.0.1.
 * No inherited pragmas. See the private session's complete verification.
 */
#include "types.h"

typedef struct Vec  { s16 x; s16 y; s16 z; } Vec;
typedef struct Box  { s16 x; s16 y; s16 w; s16 h; } Box;
typedef struct Row  { Box a; Box b; } Row;
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

extern Vec D_004805B8 __attribute__((section(".sdata"),aligned(2)));
extern Vec D_004805C0 __attribute__((section(".sdata"),aligned(2)));
extern Vec D_004805C8 __attribute__((section(".sdata"),aligned(2)));
extern Vec D_004805D0 __attribute__((section(".sdata"),aligned(2)));
extern Vec D_004805D8 __attribute__((section(".sdata"),aligned(2)));
/*rgp*/
/*rgp*/

extern s32 normal_BtlChgPageHeaderLayoutRelated_5056b0(void *a, s32 id);

s32 normal_BtlChgPageHeaderLayoutRelated_5056b0(void *a, s32 id)
{
    Vec t5 __attribute__((aligned(16)));
    Vec t4 __attribute__((aligned(16)));
    Vec t3 __attribute__((aligned(16)));
    Vec t2 __attribute__((aligned(16)));
    Vec t1 __attribute__((aligned(16)));
    void *w;
    Hold *h;
    Row  *r;
    s16   v;
    s16   u;

    t5 = *(const Vec *)&D_004805B8;
    t4 = D_004805C0;
    t3 = D_004805C8;
    t2 = D_004805D0;
    t1 = D_004805D8;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    h = UiFindWidget_290460(w, id);
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    r->b.x = t5.z;
    r->b.y = t4.z;
    v = t3.z;
    r->b.w = v;
    r->a.w = v;
    u = t2.z;
    r->b.h = u;
    r->a.h = u;
    r->a.x = t1.z;
    r->a.y = 3;
    return 1;
}
