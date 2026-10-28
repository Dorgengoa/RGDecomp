/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinCastIcon_2430a0 1
#define RGP_SELF_begin 1
#define RGP_SELF_end 1
#define RGP_SELF_find 1
#define RGP_SELF_next 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct Data {
    u8 pad00[0xC];
    s32 xC;
    u8 pad10[0xC];
    s32 x1C;
} Data;

typedef struct Elem {
    struct Elem *next;
    u8 pad04[0x8];
    s32 key;
    Data data;
} Elem;

typedef struct List {
    Elem *first;
    Elem *cur;
    s32 done;
} List;

typedef struct Rect {
    u8 pad00[0x40];
    s32 x40;
    s32 x44;
} Rect;

typedef struct Sub {
    u8 pad00[0x60];
    List list;
    u8 pad6c[0x3C0];
    Rect *rect;
} Sub;

typedef struct EventCtx {
    u32 pad00;
    Sub *sub;
} EventCtx;

typedef struct Img {
    s16 x0;
    s16 w;
    s16 h;
} Img;

typedef struct Mgr {
    u8 pad[0x3BA0];
    s32 x3BA0;
} Mgr;

extern EventCtx *gEventContext;
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
extern f32 D_0047E870;
extern f32 D_0047E874;
extern f32 D_0047E878;
extern f32 D_0047E87C;
extern f32 D_0047E880;
extern f32 D_0047E884;
extern f32 D_0047E888;
extern f32 D_0047E88C;

static inline s32 begin(List *l) {
    if (l->cur != 0) {
        return -1;
    }
    l->cur = l->first;
    l->done = 0;
    return 0;
}

static inline Data *next(List *l, s32 *k) {
    Data *d;
    Elem *e;
    e = l->cur;
    if (e == 0) {
        return 0;
    }
    *k = e->key;
    d = &e->data;
    if ((l->cur = e->next) == 0) {
        l->done = 1;
    }
    return d;
}

static inline void end(List *l) {
    l->cur = 0;
    l->done = 0;
}

static inline Data *find(List *l, s32 key, s32 *kp) {
    Data *d;
    if (begin(l) != 0) {
        return 0;
    }
    while ((d = next(l, kp)) != 0) {
        if (key == *kp) {
            break;
        }
    }
    end(l);
    return d;
}

s32 EvCmdMenuWinCastIcon_2430a0(s32 arg0) { __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 h;
    s32 k;
    s32 x1C;
    Sub *sub;
    s32 id;
    s32 y;
    Data *d;
    f32 a[4] __attribute__((aligned(16)));
    Rect *r;
    s32 x;
    List *list;
    Img *img;
    f32 b[4] __attribute__((aligned(16)));

    arg0 += 8;
    sub = gEventContext->sub;
    list = &sub->list;
    h = ((s32)MenuWinGet_2653e0(ScriptGetInt_2490f0((void *)rgp_entry_arg0)));
    if (h == 0) {
        return 0;
    }
    { f32 *pa = (f32 *)&a;
    { f32 *pb = (f32 *)&b;
    pa[0] = D_0047E870;
    pa[1] = D_0047E874;
    pa[2] = D_0047E878;
    pa[3] = D_0047E87C;
    pb[0] = D_0047E880;
    pb[1] = D_0047E884;
    pb[2] = D_0047E888;
    pb[3] = D_0047E88C;
    }}
    r = sub->rect;
    if (r != 0) {
        x = r->x40;
        y = r->x44;
        a[0] = x - 0x1C;
        a[1] = y + 0xA;
    }
    MenuWinSetDrawMode_26c3e0(h, 0);
    MenuWinSetBlendMode_26c270(h, 1);
    MenuWinSetPos_26c3b0(h, a);
    MenuWinSetColor_26c380(h, b);
    MenuWinSetDrawLayer_26c3d0(h, 1);
    MenuWinSetTexFilter_26c3c0(h, 1);
    d = find(list, EventCastFindKeyByName_24bb50(list, ScriptGetCodeAddr_249050(arg0)), &k);
    if (d == 0) {
        return 0;
    }
    x1C = d->x1C;
    id = d->xC;
    img = ((Img *)NameTableFindByName_159fb0(((Mgr *)GetDrawCtx_15de80())->x3BA0, id, -1));
    if (img == 0) {
        return 0;
    }
    MenuWinSetSize_26c320(h, 0x2A, 0x2A);
    MenuWinSetUvRect_26c300(h, 0, 0, img->w, img->h);
    MenuWinSetTexName_26c410(h, id, x1C);
    return 1;
}
