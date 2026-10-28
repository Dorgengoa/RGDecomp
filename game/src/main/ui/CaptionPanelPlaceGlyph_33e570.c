/* rgp:protos */
#define RGP_SELF_CaptionCfgGetAltGlyphOrigin_33ff00 1
#define RGP_SELF_CaptionCfgGetGlyphOrigin_33fe80 1
#define RGP_SELF_CaptionPanelPlaceGlyph_33e570 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Pt {
    s32 x;
    s32 y;
    s32 key;
    s32 t;
} Pt;

typedef struct Quad {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10;
    f32 f14;
    s16 h18;
    s16 h1A;
    s16 h1C;
} Quad;

typedef struct Node {
    u8 pad[0x20];
    Quad *q;
} Node;

typedef struct Self {
    u8 pad[0x10];
    void *p10;
} Self;

/*rgp*/
/*rgp*/
void CaptionCfgGetAltGlyphOrigin_33ff00(void *, void *);
void CaptionCfgGetGlyphOrigin_33fe80(void *, void *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CaptionPanelPlaceGlyph_33e570(Self *self, s32 n, s32 mode, s32 id, s32 a4, s32 a5, s32 a6) {
    Pt pos __attribute__((aligned(16)));
    Pt tmp1 __attribute__((aligned(16)));
    Pt tmp2 __attribute__((aligned(16)));
    Pt tmp3 __attribute__((aligned(16)));
    s32 w;
    s32 h;
    s32 cols;
    s32 rows;
    Node *nd;
    Quad *q;
    s32 x;
    s32 y;
    s32 key;
    s32 t;

    key = id + 3;
    nd = ((Node *)UiFindWidget_290460(((s32)UiPanelGetWidgetList_33e860(self)), key));
    if (nd == 0) {
        return 0;
    }
    w = 0;
    h = 0;
    if (mode == 1) {
        tmp1 = ({ Pt rgp_sret; CaptionCfgGetAltGlyphOrigin_33ff00((void *)&rgp_sret, (void *)(self->p10)); rgp_sret; });
        pos = tmp1;
        CaptionCfgGetAltCellSize_3401c0(self->p10, &w, &h);
        CaptionCfgGetAltGridDims_340160(self->p10, &cols, &rows);
        n += ((signed char)CaptionCfgGetAltGlyphBase_33fe40(self->p10));
    } else if (mode == 0) {
        tmp2 = ({ Pt rgp_sret; CaptionCfgGetGlyphOrigin_33fe80((void *)&rgp_sret, (void *)(self->p10)); rgp_sret; });
        pos = tmp2;
        CaptionCfgGetCellSize_3401f0(self->p10, &w, &h);
        CaptionCfgGetGridDims_340190(self->p10, &cols, &rows);
        n += ((signed char)CaptionCfgGetGlyphBase_33fe60(self->p10));
    } else if (mode == 2) {
        tmp3 = ({ Pt rgp_sret; CaptionCfgGetGlyphOrigin_33fe80((void *)&rgp_sret, (void *)(self->p10)); rgp_sret; });
        pos = tmp3;
        CaptionCfgGetCellSize_3401f0(self->p10, &w, &h);
        CaptionCfgGetGridDims_340190(self->p10, &cols, &rows);
        w /= 2;
    }
    if (cols <= 0) {
        cols = 1;
    }
    if (rows <= 0) {
        rows = 1;
    }
    x = w * (n % cols);
    y = h * (n / cols);
    UiPanelGetGlyphSpacing_33dfc0(self);
    x += pos.x;
    y += pos.y;
    q = nd->q;
    if (q == 0) {
        return 0;
    }
    if (a6 != -1) {
        w = a6;
    }
    if (n != -1) {
        q->h0 = 0;
        q->h2 = h * a5;
        t = w;
        q->hC = t;
        q->h4 = t;
        t = h;
        q->hE = t;
        q->h6 = t;
        q->h8 = x;
        q->hA = y;
        q->f14 = 1.0f;
        q->f10 = 1.0f;
        q->h1A = 0;
        q->h18 = 0;
        q->h1C = 0;
    } else {
        q->h0 = 0;
        q->h2 = 0;
        t = w;
        q->hC = t;
        q->h4 = t;
        q->hE = 0;
        q->h6 = 0;
        q->h8 = 0;
        q->hA = 0;
        q->f14 = 0.0f;
        q->f10 = 0.0f;
        q->h1A = 0;
        q->h18 = 0;
        q->h1C = 0;
    }
    UiSetWidgetVisible_290010(((s32)UiPanelGetWidgetList_33e860(self)), key, 1, -1);
    UiSetWidgetPos_290f60(((s32)UiPanelGetWidgetList_33e860(self)), key, a4, 0);
    return 1;
}
