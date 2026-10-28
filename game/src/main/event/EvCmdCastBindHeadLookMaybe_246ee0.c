/* rgp:protos */
#define RGP_SELF_EvCmdCastBindHeadLookMaybe_246ee0 1
#define RGP_SELF_List_Next 1
#include "port/game_protos.h"
#line 1
#pragma inline_depth(10)
#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 key;
} Node;

typedef struct List {
    Node *head;
    Node *cur;
    s32 end;
} List;

typedef struct Ctx {
    s32 p0;
    u8 *p4;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_0045EB00[0x10];
extern Ctx *gEventContext;

static inline u8 *List_Next(List *l, s32 *key)
{
    Node *n = l->cur;
    u8 *r;
    if (n == 0) {
        return 0;
    }
    *key = n->key;
    r = (u8 *)n + 0x10;
    l->cur = n->next;
    if (l->cur == 0) {
        l->end = 1;
    }
    return r;
}

s32 EvCmdCastBindHeadLookMaybe_246ee0(s64 *arg0)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 base;
    s32 r;
    s32 a;
    s32 ha;
    s32 hb;
    u8 *p;
    s32 k;
    List *l;
    s32 b;

    arg0++;
    base = gEventContext->p0;
    l = (List *)(gEventContext->p4 + 0x60);
    if (ScriptGetInt_2490f0((void *)rgp_entry_arg0) != 0) {
        a = EventCastFindKeyByName_24bb50(l, ScriptGetCodeAddr_249050((s32)arg0++));
        b = EventCastFindKeyByName_24bb50(l, ScriptGetCodeAddr_249050((s32)arg0));
        ha = EventCastGetObjId_24c160(l, a, 0);
        hb = EventCastGetObjId_24c160(l, b, 0);
        if (l->cur != 0) {
            r = -1;
        } else {
            r = 0;
            l->cur = l->head;
            l->end = 0;
        }
        if (r != 0) {
            p = 0;
        } else {
            while ((p = List_Next(l, &k)) != 0) {
                if (a == k) {
                    break;
                }
            }
            l->cur = 0;
            l->end = 0;
        }
        if (p != 0) {
            *(s16 *)(p + 0x8C) = 1;
            *(s16 *)(p + 0x8E) = 0;
            HeadLookBindNodes_1c5b70(p + 0x50, base, (long long)(ha), D_0045EB00);
            *(s32 *)(p + 0xD0) = hb;
        }
    } else {
        a = EventCastFindKeyByName_24bb50(l, ScriptGetCodeAddr_249050((s32)arg0));
        EventCastGetObjId_24c160(l, a, 0);
        if (l->cur != 0) {
            r = -1;
        } else {
            r = 0;
            l->cur = l->head;
            l->end = 0;
        }
        if (r != 0) {
            p = 0;
        } else {
            while ((p = List_Next(l, &k)) != 0) {
                if (a == k) {
                    break;
                }
            }
            l->cur = 0;
            l->end = 0;
        }
        if (p != 0) {
            *(s16 *)(p + 0x8C) = 0;
            *(s16 *)(p + 0x8E) = 0;
        }
    }
    return 1;
}
