#include "types.h"

extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern void CaptionPanelSetOffsetX_33df40(u8 *, s32);
extern void CaptionPanelPlaceGlyph_33e570(u8 *, s32, s32, s32, s32, s32, s32);
extern void UiPanelGetWidgetList_33e860(u8 *);
extern s32 CaptionPanelGetGlyphList_33eaa0(void);
extern s32 CaptionGlyphNodeGetAdvance_340310(s32);
extern s32 CaptionGlyphNodeGetNext_340330(s32);
extern s32 CaptionGlyphNodeGetCode_340350(s32);
extern s32 CaptionGlyphNodeGetSheet_340370(s32);
extern s8 *CaptionGlyphNodeGetKey_340390(s32);
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
    head = CaptionPanelGetGlyphList_33eaa0();
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
        p = CaptionGlyphNodeGetKey_340390(node);
        c = p[1];
        if (c != 0) {
            if (p[0] == s[0] && (s8)c == s[1]) {
                code = CaptionGlyphNodeGetCode_340350(node);
                w = CaptionGlyphNodeGetSheet_340370(node);
                adv = CaptionGlyphNodeGetAdvance_340310(node);
                pos += 2;
                i++;
                goto done;
            }
        } else {
            if (p[0] == *s) {
                code = CaptionGlyphNodeGetCode_340350(node);
                w = CaptionGlyphNodeGetSheet_340370(node);
                adv = CaptionGlyphNodeGetAdvance_340310(node);
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
