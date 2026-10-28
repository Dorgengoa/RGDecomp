/* rgp:protos */
#define RGP_SELF_CaptionPanelSetText_33dfd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strlen(s8 *);

s32 CaptionPanelSetText_33dfd0(u8 *arg0, s8 *arg1)
{
    s32 k;
    s32 head;
    s32 width;
    s32 len;
    s32 pos;
    s32 y;
    s32 i;
    s32 node;
    s32 code;
    s32 w;
    s32 adv;
    s8 *s;
    s8 *p;
    s32 c;

    if (arg1 == 0) {
        return 0;
    }
    head = CaptionPanelGetGlyphList_33eaa0((void *)arg0);
    if (head == 0) {
        *(s32 *)(arg0 + 0x4C) = 0;
        *(s32 *)(arg0 + 0x48) = 0;
        return 0;
    }
    for (k = 0; k <= 0x20; k++) {
        CaptionPanelPlaceGlyph_33e570(arg0, -1, -1, k, 0, 0, -1);
    }
    UiPanelGetWidgetList_33e860(arg0);
    width = DrawEnvGetWidth_1451e0(GetDrawCtx_15de80());
    *(s32 *)(arg0 + 0x68) = 0;
    len = strlen(arg1);
    pos = 0;
    y = 0;
    for (i = 0; i < len; i++) {
        node = head;
        code = -1;
        w = 2;
        adv = 0;
        s = arg1 + pos;
    top:
        if (node == 0) {
            goto done;
        }
        if (*s == '\n') {
            goto done;
        }
        p = ((s8 *)CaptionGlyphNodeGetKey_340390(node));
        c = p[1];
        if (c != 0) {
            if (p[0] == s[0] && (s8)c == s[1]) {
                code = ((short)CaptionGlyphNodeGetCode_340350(node));
                w = ((signed char)CaptionGlyphNodeGetSheet_340370(node));
                adv = ((signed char)CaptionGlyphNodeGetAdvance_340310(node));
                pos += 2;
                i++;
                goto done;
            }
        } else {
            if (p[0] == *s) {
                code = ((short)CaptionGlyphNodeGetCode_340350(node));
                w = ((signed char)CaptionGlyphNodeGetSheet_340370(node));
                adv = ((signed char)CaptionGlyphNodeGetAdvance_340310(node));
                pos += 1;
                goto done;
            }
        }
        node = CaptionGlyphNodeGetNext_340330(node);
        goto top;
    done:
        CaptionPanelPlaceGlyph_33e570(arg0, code, w, i, y, 0, adv);
        y = y + adv - *(s32 *)(arg0 + 0x50);
    }
    *(s32 *)(arg0 + 0x48) = len;
    CaptionPanelSetOffsetX_33df40(arg0, (s32)(width - y) / 2);
    return 1;
}
