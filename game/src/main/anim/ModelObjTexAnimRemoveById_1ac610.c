/* rgp:protos */
#define RGP_SELF_Find1AC610 1
#define RGP_SELF_Find2 1
#define RGP_SELF_ModelObjTexAnimRemoveById_1ac610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node001AC610 {
    struct Node001AC610 *next;
    struct Node001AC610 *prev;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Node001AC610;

typedef struct {
    u8 pad0[0x220];
    Node001AC610 *unk220;
    u8 pad224[0x4DC - 0x224];
    s32 unk4DC;
} Obj0Arg0;

typedef struct {
    s64 a;
    s64 b;
} V16_1AC610;

typedef struct {
    s64 v[8];
} M64_1AC610;

/*rgp*/
extern void ImgGetEntryDesc_158f50(V16_1AC610 *, s32, s32);
/*rgp*/
/*rgp*/

static inline Node001AC610 *Find1AC610(Obj0Arg0 *o, s32 id)
{
    Node001AC610 *p;

    for (p = o->unk220; p != NULL; p = p->next) {
        if (id == p->unkC) {
            return p;
        }
    }
    return NULL;
}

static inline Node001AC610 *Find2(Obj0Arg0 *o, s32 id, Node001AC610 **pp)
{
    for (*pp = o->unk220; *pp != NULL; *pp = (*pp)->next) {
        if (id == (*pp)->unkC) {
            return *pp;
        }
    }
    return NULL;
}
void ModelObjTexAnimRemoveById_1ac610(Obj0Arg0 *arg0, s32 arg1)
{
    V16_1AC610 *src;
    Node001AC610 *prev;
    Node001AC610 *next;
    V16_1AC610 *dst;
    Node001AC610 *p;
    Node001AC610 *head;
    V16_1AC610 c[4] __attribute__((aligned(16)));
    s32 n;
    s32 w;
    s32 k;
    s32 *q;
    s32 h;
    V16_1AC610 a[4] __attribute__((aligned(16)));
    s32 d;

    p = Find2(arg0, arg1, &p);
    if (p == NULL) {
        return;
    }
    w = arg0->unk4DC;
    q = &p->unk10;
    h = GetDrawCtxNameTable_15de40();
    if (q != NULL) {
        d = *q;
        n = ImgGetEntryCount_159250(d);
        {
        s32 i;
        for (i = 0; i < n; i++) {
            ImgGetEntryDesc_158f50(a, d, i);
            src = a;
            dst = c;
            k = 4;
            do {
                k -= 1;
                dst->a = src->a;
                dst->b = src->b;
                src += 1;
                dst += 1;
            } while (k > 0);
            NameTableRemoveByName_158c40(h, c, w);
        }
        }
    }
    prev = p->prev;
    if (prev != NULL) {
        next = p->next;
        prev->next = next;
        if (next != NULL) {
            next->prev = prev;
        }
        head = p->prev;
        while (head->prev != NULL) {
            head = head->prev;
        }
    } else {
        next = p->next;
        if (next != NULL) {
            next->prev = NULL;
        }
        head = p->next;
    }
    p->prev = NULL;
    p->next = NULL;
    arg0->unk220 = head;
}
