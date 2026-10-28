/* rgp:protos */
#define RGP_SELF_LoadingScreenLoadText_1fe7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x34];
    char lines[14][0x40];
    u8 pad3B4[0x70];
    s32 unk424;
    s32 unk428;
    s32 unk42C;
    s32 unk430;
} Msg001FE7F0;

typedef struct {
    u8 pad0[0xC];
    char *text;
} Str001FE7F0;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} Tbl001FE7F0;

typedef struct {
    u8 pad0[0x88];
    Tbl001FE7F0 *unk88;
} Ctx001FE7F0;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 strlen(const char *);
char *strncpy(char *, const char *, s32);

void LoadingScreenLoadText_1fe7f0(Msg001FE7F0 *self, s32 a1, s32 a2, s32 a3, s32 a4) {
    Str001FE7F0 *str;
    Ctx001FE7F0 *ctx;
    s32 size;
    s32 maxw;
    s32 count;
    s32 line;
    s32 font;
    s32 heap;
    char *p;
    s32 w;
    s32 len;
    s32 maxh;
    s32 x;
    char *start;
    s32 i;
    s32 h;
    u8 *buf;

    ctx = ((Ctx001FE7F0 *)GetWorldDataMgr_1fedf0());
    self->unk430 = 1;
    self->unk424 = 0;
    self->unk428 = 1;
    font = ((s32)GetSysTextStyle_313570());
    TextStyleInit_26c610(font);
    TextStyleSetFontType_26edf0(font, 1);
    heap = ((s32)GetReadBuffHeap_2025e0());
    buf = ((u8 *)MemStackHeapAlloc_14db10(heap, 2, 0x1CCCC, 0x40));
    if (buf == NULL) {
        return;
    }
    MemStackAlign64_14d8e0(heap);
    x = WorldDataGetPurposePacPath_3f0230(ctx, 0);
    size = 0;
    ResidentFileReadLocalizedMaybe_1c2860(x, buf, &size);
    WorldDataMgrRelease_3f0320(ctx, 1);
    WorldDataMgrSetPurposeSource_3f02b0(ctx, 0, buf, size);
    WorldDataMgrSelectPurpose_3f05f0(ctx, -1);
    WorldDataMgrSetupPurpose_3f0450(ctx);
    MemStackReturnToOwnerMaybe_14dad0(heap);
    MemStackHeapFree_14dcb0(heap, buf);
    x = ctx->unk88->unkC;
    str = x ? ((Str001FE7F0 *)WorldTextFindEntryMaybe_410c70(x, a1, a2, a3, a4)) : NULL;
    if (str == NULL) {
        return;
    }
    p = str->text;
    if (p == NULL) {
        return;
    }
    line = 0;
    start = p;
    len = strlen(p);
    for (i = 0; i < len; i++) {
        if (*p == 0x5C && p[1] == 'n') {
            *p = 0;
            p += 2;
            strncpy(self->lines[line], start, 0x40);
            self->lines[line][0x3F] = 0;
            line++;
            start = p;
            if (line >= 14) {
                break;
            }
        } else {
            p++;
        }
    }
    strncpy(self->lines[line], start, 0x40);
    self->lines[line][0x3F] = 0;
    count = line + 1;
    TextStyleInit_26c610(font);
    TextStyleSetFontType_26edf0(font, 1);
    TextStyleAddSpacing_26f2b0(font, 3, 0);
    maxw = 0;
    maxh = 0;
    for (i = 0; i < count; i++) {
        w = 0;
        h = 0;
        FontMeasureString_26daf0(font, self->lines[i], &w, &h);
        if (maxw < w) {
            maxw = w;
        }
        if (maxh < h) {
            maxh = h;
        }
    }
    self->unk424 = count;
    self->unk428 = maxw;
    self->unk42C = maxh;
    self->unk430 = 0;
}
