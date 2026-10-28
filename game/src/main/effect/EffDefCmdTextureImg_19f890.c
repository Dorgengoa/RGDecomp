/* rgp:protos */
#define RGP_SELF_EffDefCmdTextureImg_19f890 1
#define RGP_SELF_EffHdlAddByName_1a37a0 1
#define RGP_SELF_IsValid 1
#define RGP_SELF_Link 1
#define RGP_SELF_List_Add 1
#define RGP_SELF_Pool_Alloc 1
#define RGP_SELF_Release 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct Handle {
    void *p;
} Handle;

typedef struct Res {
    void *vt;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} Res;

typedef struct Node {
    struct Node *next;
    Handle data;
} Node;

typedef struct NodeList {
    u8 pad0[0x68];
    Node *head;
    s32 f6C;
} NodeList;

typedef struct Pool {
    u8 pad0[0x48];
    u8 sub48[0xC8];
    s32 count;
    s32 base;
    s32 *used;
} Pool;

typedef struct Ctx {
    Pool *pool;
    s32 f4;
    u8 pad8[0x18];
    void *heap;
    NodeList *list;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void EffHdlRemove_1a36e0(void *, Handle);
void EffHdlAddByName_1a37a0(void *, void *, void *, void *);
/*rgp*/
extern void *memcpy(void *, const void *, u32);
extern u8 D_004709B8[0x10];
extern u8 D_004709C8[0x10];

static inline s32 IsValid(Handle h)
{
    return h.p != 0;
}

static inline void Release(Pool *p, Handle h)
{
    EffHdlRemove_1a36e0(p->sub48, h);
}

static inline void Link(NodeList *l, Node *n)
{
    Node *p = l->head;
    if (p == 0) {
        l->head = n;
        return;
    }
    while (p != 0) {
        Node *nx = p->next;
        if (nx == 0) {
            p->next = n;
            return;
        }
        p = nx;
    }
    p->next = n;
}

static inline Handle *List_Add(NodeList *l, void *heap)
{
    Node *n = (Node *)MemStackNew_14e230(8, heap);
    Handle *r;
    if (n != 0) {
        n->data.p = 0;
        n->next = 0;
    }
    if (n == 0) {
        r = 0;
    } else {
        Node *p;
        l->f6C = 0;
        p = l->head;
        if (p != 0) {
            while (p != 0) {
                Node *nx = p->next;
                if (nx == 0) {
                    break;
                }
                p = nx;
            }
            p->next = n;
        } else {
            l->head = n;
        }
        r = &n->data;
    }
    return r;
}

static inline s32 Pool_Alloc(Pool *p)
{
    s32 i;
    for (i = 0; i < p->count; i++) {
        if (p->used[i] == 0) {
            p->used[i] = 1;
            return i + p->base;
        }
    }
    return -1;
}

s32 EffDefCmdTextureImg_19f890(s32 a0, s32 a1, Ctx **pctx)
{
    Ctx *ctx = *pctx;
    void *heap = ctx->heap;
    s32 key = SlotGetInt_15f720((void *)a0);
    s32 size;
    Handle h __attribute__((aligned(16)));
    Res *ref;
    volatile Handle t __attribute__((aligned(16)));
    void *data;
    void *buf;
    Res *obj;
    Handle *slot;
    s32 id;

    data = ArchiveGetFileData_181dd0(ctx->f4, key, &size);
    if (data == 0) {
        return 0;
    }
    obj = (Res *)MemStackNew_14e230(0x18, heap);
    if (obj != 0) {
        obj->vt = D_004709C8;
        obj->vt = D_004709B8;
        obj->f8 = 0;
        obj->f10 = -1;
        obj->f14 = -1;
        obj->f4 = 0;
    }
    if (obj == 0) {
        return 0;
    }
    buf = MemStackAllocQw_14d950(heap, size / 16 + 1);
    if (buf == 0) {
        return 0;
    }
    memcpy(buf, data, size);
    ref = obj;
    h = ({ Handle rgp_sret; EffHdlAddByName_1a37a0((void *)&rgp_sret, (void *)(ctx->pool->sub48), (void *)(key), (void *)(&ref)); rgp_sret; });
    if ((IsValid(h) ^ 1) != 0) {
        return 0;
    }
    slot = List_Add(ctx->list, heap);
    if (slot == 0) {
        t = h;
        EffHdlRemove_1a36e0(ctx->pool->sub48, t);
        return 0;
    }
    slot->p = h.p;
    id = Pool_Alloc(ctx->pool);
    if (id >= 0) {
        EffTexResBind_1a84b0(obj, buf, id, heap);
    }
    return 1;
}
