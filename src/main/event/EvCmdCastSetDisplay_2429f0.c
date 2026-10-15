#include "types.h"

typedef struct Node_2429f0 {
    struct Node_2429f0 *next;
    s32 pad4;
    s32 pad8;
    s32 key;
    s32 item[1];
} Node_2429f0;

typedef struct {
    Node_2429f0 *head;
    Node_2429f0 *cur;
    s32 flag;
} List_2429f0;

typedef struct {
    s32 unk0;
    u8 *unk4;
} EvCtx_2429f0;

extern void ObjRecClearFlag2_1c3e40(s32, s32, s32);
extern void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern s32 ScriptGetCodeAddr_249050(s32);
extern s32 ScriptGetInt_2490f0(s32);
extern s32 EventCastFindKeyByName_24bb50(void *, s32);
extern EvCtx_2429f0 *gEventContext;

static inline u8 *next_2429f0(List_2429f0 *l, s32 *k)
{
    Node_2429f0 *n;
    u8 *item;

    n = l->cur;
    if (n == NULL) {
        return NULL;
    }
    *k = n->key;
    item = (u8 *)n->item;
    l->cur = n->next;
    if (l->cur == NULL) {
        l->flag = 1;
    }
    return item;
}

s32 EvCmdCastSetDisplay_2429f0(s64 *arg0)
{
    s32 ctx0;
    s32 val;
    s32 key;
    s32 k;
    s32 r;
    List_2429f0 *l;
    Node_2429f0 *n;
    u8 *item;

    ctx0 = gEventContext->unk0;
    if (*(s32 *)arg0 == 2) {
        l = (List_2429f0 *)(gEventContext->unk4 + 0x60);
        key = EventCastFindKeyByName_24bb50(l, ScriptGetCodeAddr_249050((s32)arg0++));
        if (l->cur != NULL) {
            r = -1;
        } else {
            r = 0;
            l->cur = l->head;
            l->flag = 0;
        }
        if (r != 0) {
            item = NULL;
        } else {
            while ((item = next_2429f0(l, &k)) != NULL) {
                if (key == k) {
                    break;
                }
            }
            l->cur = NULL;
            l->flag = 0;
        }
        if (item == NULL) {
            return 0;
        }
        val = *(s32 *)(item + 0x1C);
    } else {
        val = ScriptGetInt_2490f0((s32)arg0++);
    }
    if (ScriptGetInt_2490f0((s32)arg0) != 0) {
        ObjRecSetFlag2_1c3e80(ctx0, 1, val);
    } else {
        ObjRecClearFlag2_1c3e40(ctx0, 1, val);
    }
    return 1;
}
