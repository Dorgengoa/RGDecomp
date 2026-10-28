/* rgp:protos */
#define RGP_SELF_MenuPanelGridAlloc_28b660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The 16-byte key is copied local-to-local with lwc1/swc1 => its members
   are f32; it is then read back as one word plus five halfwords, so the
   local is a union. */

typedef struct F4 {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} F4;

typedef union Key {
    F4 f;
    struct {
        s32 h;
        u16 v[6];
    } i;
} Key;

typedef struct Cell {
    s16 m0;
    s16 m2;
    s16 m4;
    s16 m6;
    u8  pad08[8];
    s16 m10;
    u8  pad12[4];
    s16 m16;
    s16 m18;
    s16 m1A;
    s16 m1C;
    s16 m1E;
} Cell;

typedef struct Hold {
    u8    pad00[0x20];
    Cell *m20;
    Cell *m24;
} Hold;

/*rgp*/
/*rgp*/
extern s32   memset(void *p, s32 v, s32 n);

void MenuPanelGridAlloc_28b660(void *o, F4 *src)
{
    Key k __attribute__((aligned(16)));
    Hold *h1;
    Hold *h2;
    Hold *h3;
    Cell *e1;
    Cell *e2;
    Cell *e3;
    s32 i;
    s32 j;

    k.f = *src;

    h1 = ((Hold *)UiFindWidget_290460(k.i.h, k.i.v[0]));
    h2 = ((Hold *)UiFindWidget_290460(k.i.h, k.i.v[1]));
    h3 = ((Hold *)UiFindWidget_290460(k.i.h, k.i.v[2]));

    e1 = ((Cell *)MemStackAllocQw_14d950(o, 0x52));
    e2 = ((Cell *)MemStackAllocQw_14d950(o, 0x52));
    e3 = ((Cell *)MemStackAllocQw_14d950(o, 0x52));

    h1->m20 = e1;
    h2->m20 = e2;
    h3->m24 = e3;

    memset(e1, 0, 0x520);
    memset(e2, 0, 0x520);
    memset(e3, 0, 0x520);

    for (i = 0; i < 0x28; i++) {
        e1->m6 = -1;
        e1->m4 = -1;
        e2->m6 = -1;
        e2->m4 = -1;
        e3->m0 = (i % 8) * 42;
        e3->m2 = (i / 8) * 50;
        e3->m10 = 2;
        e3->m16 = 0xC;
        e3->m18 = 0x10;
        e3->m1A = 2;
        e3->m1C = 0xA;
        e3->m1E = 0x10;
        e1++;
        e2++;
        e3++;
    }
    e1->m0 = -1;
    e2->m0 = -1;
    e3->m0 = -1;

    e1 = ((Cell *)MemStackAllocQw_14d950(o, 0x22));
    e2 = ((Cell *)MemStackAllocQw_14d950(o, 0x12));
    memset(e1, 0, 0x220);
    memset(e2, 0, 0x120);

    h1 = ((Hold *)UiFindWidget_290460(k.i.h, k.i.v[3]));
    h2 = ((Hold *)UiFindWidget_290460(k.i.h, k.i.v[4]));
    h1->m20 = e1;
    h2->m24 = e2;

    for (j = 0; j < 8; j++) {
        for (i = 0; i < 2; i++) {
            e1->m6 = -1;
            e1->m4 = -1;
            e1->m1A = -1;
            e1->m18 = -1;
            e1->m1C = 2;
            e1++;
        }
        e2->m10 = 0xA;
        e2->m18 = -1;
        e2->m16 = -1;
        e2++;
    }
    e1->m0 = -1;
    e2->m0 = -1;
}
