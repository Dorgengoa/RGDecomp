/* rgp:protos */
#define RGP_SELF_EvCmdCastLoadFiles_248e30 1
#define RGP_SELF_lbegin 1
#define RGP_SELF_lend 1
#define RGP_SELF_lnext 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 key;
} Node;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x24 - 8];
    s32 unk24;
    u8 pad28[0x34 - 0x28];
    s32 unk34;
    s32 unk38;
} Item;

typedef struct {
    Node *head;
    Node *cur;
    s32 done;
} List;

typedef struct {
    s32 unk0;
    u8 *unk4;
} Ctx;

typedef struct {
    s32 a;
    s32 b;
} Cmd;

extern Ctx *gEventContext;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 lbegin(List *l)
{
    if (l->cur != NULL) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline Item *lnext(List *l, s32 *key)
{
    Node *n = l->cur;
    Node *nx;
    Item *r;
    if (n == NULL) {
        return NULL;
    }
    *key = n->key;
    r = (Item *)(n + 1);
    nx = n->next;
    l->cur = nx;
    if (nx == NULL) {
        l->done = 1;
    }
    return r;
}

static inline void lend(List *l)
{
    l->cur = NULL;
    l->done = 0;
}

s32 EvCmdCastLoadFiles_248e30(Cmd *arg0, s32 arg1)
{
    s32 key;
    s32 a;
    s32 h;
    s32 i;
    Item *it;
    s32 t;
    List *l;

    a = gEventContext->unk0;
    l = (List *)(gEventContext->unk4 + 0x60);
    h = ((s32)GetLoaderMgr_1f59d0());
    HeapProbeLargestGapMaybe_2504d0(a);
    for (i = 0; i < arg1; i++) {
        switch (arg0->a) {
        case 0:
            break;
        case 2:
            t = EventCastFindKeyByName_24bb50(l, ScriptGetCodeAddr_249050(arg0++));
            if (lbegin(l) != 0) {
                it = NULL;
            } else {
                while ((it = lnext(l, &key)) != NULL) {
                    if (t == key) {
                        break;
                    }
                }
                lend(l);
            }
            if (it == NULL) {
                return 0;
            }
            it->unk24 = LoaderRequestFile_1cd870(h, it->unk4, 0);
            if (it->unk34 != 0) {
                it->unk38 = LoaderRequestFile_1cd870(h, it->unk34, 0);
            }
            break;
        default:
            break;
        }
    }
    if (arg1 > 0) {
        LoaderQueueAppendSeparator_1cd670(h);
    }
    return 1;
}
