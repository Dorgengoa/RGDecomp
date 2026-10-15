#pragma opt_propagation off
#include "types.h"
#pragma opt_common_subs off
typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 key;
    u8 item[0x20];
} Node;

typedef struct {
    Node *head;
    Node *cur;
    s32 done;
} List;

extern void *NameTableFindByName_159fb0(s32, s32, s32);
extern void *GetDrawCtx_15de80(void *);
extern s32 ScriptGetCodeAddr_249050(s32);
extern s32 ScriptGetInt_2490f0(void);
extern s32 EventCastFindKeyByName_24bb50(List *, s32);
extern s32 MenuWinGet_2653e0(s32);
extern void MenuWinSetBlendMode_26c270(s32, s32);
extern void MenuWinSetUvRect_26c300(s32, s32, s32, s16, s16);
extern void MenuWinSetSize_26c320(s32, s16, s16);
extern void MenuWinSetColor_26c380(s32, f32 *);
extern void MenuWinSetPos_26c3b0(s32, f32 *);
extern void MenuWinSetDrawMode_26c3e0(s32, s32);
extern void MenuWinSetTexName_26c410(s32, s32, s32);
extern f32 D_0047E810;
extern f32 D_0047E814;
extern f32 D_0047E818;
extern f32 D_0047E81C;
extern f32 D_0047E820;
extern f32 D_0047E824;
extern f32 D_0047E828;
extern f32 D_0047E82C;
extern void *gEventContext;

static inline s32 List_begin(List *l)
{
    if (l->cur != NULL) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline void *List_next(List *l, s32 *key)
{
    Node *n = l->cur;
    void *item;

    if (n == NULL) {
        return NULL;
    }
    *key = n->key;
    item = n->item;
    l->cur = n->next;
    if (l->cur == NULL) {
        l->done = 1;
    }
    return item;
}

static inline void List_end(List *l)
{
    l->cur = NULL;
    l->done = 0;
}

s32 EvCmdMenuWinCastImage_243aa0(s32 arg0)
{
    f32 a[4];
    f32 b[4];
    void *p;
    s32 h;
    s32 k2;
    u8 *item;
    s32 key;
    s32 want;
    List *list;
    s32 k1;

    arg0 += 8;
    list = (List *)((u8 *)(*(void **)((u8 *)gEventContext + 0x4)) + 0x60);
    h = MenuWinGet_2653e0(ScriptGetInt_2490f0());
    if (h == 0) {
        return 0;
    }
    { f32 *pa = (f32 *)&a;
    { f32 *pb = (f32 *)&b;
    pa[0] = D_0047E810;
    pa[1] = D_0047E814;
    pa[2] = D_0047E818;
    pa[3] = D_0047E81C;
    pb[0] = D_0047E820;
    pb[1] = D_0047E824;
    pb[2] = D_0047E828;
    pb[3] = D_0047E82C;
    }}
    MenuWinSetDrawMode_26c3e0(h, 0);
    MenuWinSetBlendMode_26c270(h, 1);
    MenuWinSetPos_26c3b0(h, a);
    MenuWinSetColor_26c380(h, b);
    want = EventCastFindKeyByName_24bb50(list, ScriptGetCodeAddr_249050(arg0));
    if (List_begin(list) != 0) {
        item = NULL;
    } else {
        while ((item = List_next(list, &key)) != NULL) {
            if (want == key) {
                break;
            }
        }
        List_end(list);
    }
    if (item == NULL) {
        return 0;
    }
    k2 = *(s32 *)(item + 0x1C);
    k1 = *(s32 *)(item + 0xC);
    p = NameTableFindByName_159fb0(*(s32 *)((u8 *)GetDrawCtx_15de80(item) + 0x3BA0), k1, -1);
    if (p == NULL) {
        return 0;
    }
    MenuWinSetSize_26c320(h, *(s16 *)((u8 *)p + 0x2), *(s16 *)((u8 *)p + 0x4));
    MenuWinSetUvRect_26c300(h, 0, 0, *(s16 *)((u8 *)p + 0x2), *(s16 *)((u8 *)p + 0x4));
    MenuWinSetTexName_26c410(h, k1, k2);
    return 1;
}
