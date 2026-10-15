#include "types.h"

struct Obj {
    s32 idx;        /* +0x00 */
    s32 count;      /* +0x04 */
    s32 rows;       /* +0x08 */
    s32 cur;        /* +0x0C */
    s32 id;         /* +0x10 */
    s32 value;      /* +0x14 */
    u8 pad18[3];
    u8 active;      /* +0x1B */
};

struct Entry {
    s16 no;         /* +0x00 */
    u8 pad02[0xA];
    s32 val;        /* +0x0C */
    u8 pad10[0x1C];
    s16 v2c;        /* +0x2C */
};

struct Iter {
    void *p;
    s16 count;
};

struct Actor {
    u8 pad0[8];
    u8 *info;       /* +0x08 */
};

extern "C" {
s32 Sprintf_1343b8(char *, const char *, ...);
s32 strlen(const char *);
void *memmove(void *, const void *, u32);
void *memset(void *, s32, u32);
Actor *GetGameData_1fede0(void);
void IterInit_370170(Iter *, void *);
void IterSeek_36fff0(Iter *, s32);
Entry *IterNext_370040(Iter *);
s32 GetDrawCtx_15de80();
s32 DrawListBeginPrim_141b00(s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void FontCtxSetup9x15_2085d0(s32, s32);
void TextCellRectFill9x15Rgba_208430(s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);
void TextScrollBarDraw_208010(s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32);
void DrawListEndPrim_141a20(s32);
void FontDrawTextAtCell_208490(s32, s32, s32, s32, f32, char *);
}
extern char D_00461390[];
extern char D_004613A8[];
extern char D_004613B0[];

extern "C" void DebugItemListDraw_299500(Obj *arg0)
{
    char buf[0x800];
    Iter it;
    s32 width;
    char *q;
    s32 sel;
    bool more;
    s32 len;
    u8 *list;
    s32 pad;
    Actor *actor;
    s32 g;
    s32 idx;
    s32 row;
    bool end;
    char *p;
    s32 rows;
    s32 len0;
    Entry *e;
    s32 n;
    s32 w;
    char *b;

    if (arg0->active == 0) {
        return;
    }
    actor = GetGameData_1fede0();
    if (actor == 0) {
        return;
    }
    buf[0] = 0;
    width = 0;
    sel = -1;
    b = buf;
    p = b;
    p += Sprintf_1343b8(p, D_00461390);
    len0 = strlen(b);
    if (len0 > 0) {
        width = len0;
    }
    p += Sprintf_1343b8(p, D_004613A8);
    list = *(u8 **)(*(u8 **)(actor->info + 0x40) + 8);
    row = 1;
    if (list != 0) {
        list += 0x88;
    }
    IterInit_370170(&it, list);
    arg0->count = it.count;
    idx = arg0->idx;
    IterSeek_36fff0(&it, idx - 1);
    while (!(end = ((e = IterNext_370040(&it)) != 0) ^ 1) && idx < arg0->count && row <= arg0->rows) {
        q = p;
        p += Sprintf_1343b8(p, D_004613B0, e->no, e->val);
        len = strlen(q);
        if (width < len) {
            width = len;
        }
        p += Sprintf_1343b8(p, D_004613A8);
        if (arg0->cur == idx) {
            sel = row;
            arg0->value = e->v2c;
        }
        row++;
        idx++;
    }
    while (row <= arg0->rows) {
        p += Sprintf_1343b8(p, D_004613A8);
        row++;
    }
    more = false;
    if (arg0->rows < arg0->count) {
        more = true;
    }
    if (more) {
        width++;
    }
    g = GetDrawCtx_15de80();
    w = DrawListBeginPrim_141b00(g);
    GsPktSetTextured_13e400(w, 0);
    GsPktSetOriginMode_13e2f0(w, 0);
    GsPktSetAlphaBlend_13e500(w, 1);
    GsPktSetBlendMode_13e4f0(w, 1);
    GsPktEnableAlphaTest_13e4d0(w, 1);
    GsPktSetZWriteMask_13e430(w, 0);
    GsPktEnableZTest_13e460(w, 0);
    FontCtxSetup9x15_2085d0(0x338, arg0->id);
    rows = arg0->rows + 1;
    TextCellRectFill9x15Rgba_208430(w, 0x14, 0x50, 0, 0, width, rows, 6, 160.0f, 160.0f, 160.0f, 88.0f);
    TextCellRectFill9x15Rgba_208430(w, 0x14, 0x50, 0, 0, width, rows, 4, 0.0f, 0.0f, 0.0f, 88.0f);
    TextCellRectFill9x15Rgba_208430(w, 0x14, 0x50, 0, 0, width, 1, 1, 128.0f, 128.0f, 128.0f, 88.0f);
    TextCellRectFill9x15Rgba_208430(w, 0x14, 0x50, 0, sel, width, 1, 0, 64.0f, 64.0f, 192.0f, 88.0f);
    if (more) {
        TextCellRectFill9x15Rgba_208430(w, 0x14, 0x50, width - 1, 1, 1, arg0->rows, 1, 128.0f, 128.0f, 128.0f, 88.0f);
        TextScrollBarDraw_208010(w, 0x14, 0x50, width - 1, 1, 1, arg0->rows, 0, 160.0f, 160.0f, 160.0f, 180.0f, 16.0f, arg0->count, arg0->idx, arg0->rows);
    }
    DrawListEndPrim_141a20(g);
    n = p - buf + 1;
    pad = (width - len0) / 2;
    if (pad > 0) {
        memmove(buf + pad, buf, n);
        memset(buf, 0x20, pad);
    }
    FontDrawTextAtCell_208490(0x14, 0x50, 0, 0, 128.0f, buf);
}
