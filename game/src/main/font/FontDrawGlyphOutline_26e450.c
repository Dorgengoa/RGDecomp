/* rgp:protos */
#define RGP_SELF_FontDrawGlyphOutline_26e450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct R4 {
    s32 x;
    s32 y;
    s64 wh;
} R4;

typedef struct I4 {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} I4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 D_0047E968[4][2];
extern s8 D_0047E970[4][2];
extern s8 D_0047E978[4][2];
extern s8 D_0047E980[4][2];
extern s8 D_0047E988[4][2];
extern s8 D_0044EBB0[12][2];

void FontDrawGlyphOutline_26e450(s32 a0, s32 a1, V4 *pa, V4 *pb, s32 col)
{
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    R4 r __attribute__((aligned(16)));
    s32 k;
    s32 m;
    s32 i;

    a = *pa;
    b = *pb;
    m = 0;
    if (((short)TextStyleGetZEnable_26e410(a0)) != 0) {
        m = TextStyleGetZ_26e430(a0);
    }
    k = (col << 7) / 128;
    r.wh = *(s64 *)&((I4 *)&a)->z;
    switch (((signed char)TextStyleGetOutlineMode_26f150(a0))) {
    case 0:
        break;
    case 1:
        GsPktSetRGBAQ_13ee40(a1, 0, 0, 0, k);
        a0 = ((I4 *)&a)->y;
        for (i = 0; i < 4; i++) {
            r.x = ((I4 *)&a)->x + D_0047E968[i][0];
            r.y = a0 + D_0047E968[i][1];
            GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        }
        break;
    case 2:
        GsPktSetRGBAQ_13ee40(a1, 0x40, 0x40, 0x40, k);
        r.x = ((I4 *)&a)->x + 1;
        a0 = ((I4 *)&a)->y;
        r.y = a0 + 1;
        GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        GsPktSetRGBAQ_13ee40(a1, 0, 0, 0, k);
        r.y = a0 + 2;
        r.x = ((I4 *)&a)->x + 2;
        GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        break;
    case 3:
        GsPktSetRGBAQ_13ee40(a1, 0, 0, 0, k);
        r.x = ((I4 *)&a)->x + 2;
        r.y = ((I4 *)&a)->y + 2;
        GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        break;
    case 4:
        GsPktSetRGBAQ_13ee40(a1, 0, 0, 0, k);
        a0 = ((I4 *)&a)->y;
        for (i = 0; i < 12; i++) {
            r.x = ((I4 *)&a)->x + D_0044EBB0[i][0];
            r.y = a0 + D_0044EBB0[i][1];
            GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        }
        break;
    case 5:
        GsPktSetRGBAQ_13ee40(a1, 0, 0, 0, k);
        a0 = ((I4 *)&a)->y;
        for (i = 0; i < 4; i++) {
            r.x = ((I4 *)&a)->x + D_0047E970[i][0];
            r.y = a0 + D_0047E970[i][1];
            GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        }
        GsPktSetRGBAQ_13ee40(a1, 0x20, 0x20, 0x20, k);
        for (i = 0; i < 4; i++) {
            r.x = ((I4 *)&a)->x + D_0047E978[i][0];
            r.y = a0 + D_0047E978[i][1];
            GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        }
        break;
    case 6:
        GsPktSetRGBAQ_13ee40(a1, 0, 0, 0, k);
        a0 = ((I4 *)&a)->y;
        for (i = 0; i < 4; i++) {
            r.x = ((I4 *)&a)->x + D_0047E980[i][0];
            r.y = a0 + D_0047E980[i][1];
            GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        }
        for (i = 0; i < 4; i++) {
            r.x = ((I4 *)&a)->x + D_0047E988[i][0];
            r.y = a0 + D_0047E988[i][1];
            GsPktSpriteUVRect_26eb30(a1, &r, &b, m);
        }
        break;
    }
}
