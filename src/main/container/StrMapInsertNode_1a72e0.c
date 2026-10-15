#include "types.h"

typedef struct Consolea72e0 {
    u8 pad00[0x8];
    void *unk08;
    void *out;              /* +0x0C */
} Consolea72e0;

extern Consolea72e0 *const volatile D_00449858;
extern const char D_0045A710[];
extern const char D_0045A730[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
extern void Abort_12de80(void);
extern void *OperatorNew_100990(s32 n);
extern void StringReserve_107e80(void *s, s32 n);
extern void StringReplace_106f90(void *s, s32 a, s32 b, const char *first, const char *last, struct Alloca72e0 al);
extern void RbTreeRebalance_1a7480(void *node, void *head);

struct Alloca72e0 {
    char c;
};

struct Bodya72e0 {
    f32 v[3];
};

struct Stra72e0 {
    s32 m00;
    s32 m04;
    const char *m08;
    s32 m0C;
};

struct Nodea72e0 {
    struct Nodea72e0 *left;      /* +0x00 */
    struct Nodea72e0 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Stra72e0 val;         /* +0x0C */
};

struct Treea72e0 {
    s32 size;                   /* +0x00 */
    void *head;                 /* +0x04 */
    u8 pad008[0x4];
    struct Nodea72e0 *lmost;     /* +0x0C */
};

struct Nodea72e0 *StrMapInsertNode_1a72e0(struct Treea72e0 *t, struct Nodea72e0 *y, s32 addleft,
                              s32 setlmost, struct Stra72e0 *src)
{
    struct Nodea72e0 *n;
    struct Stra72e0 *s;
    u32 i;
    struct Alloca72e0 al;

    if ((u32)t->size > 0xFFFFFFFEU) {
        Fprintf_12f9a0(D_00449858->out, D_0045A710);
        Abort_12de80();
    }
    n = (struct Nodea72e0 *)OperatorNew_100990(0x1C);
    if (n == 0) {
        Fprintf_12f9a0(D_00449858->out, D_0045A730);
        Abort_12de80();
    }
    s = &n->val;
    if (s != 0) {
        if ((src->m00 & 1) == 0) {
            *(struct Bodya72e0 *)s = *(struct Bodya72e0 *)src;
        } else {
            for (i = 0; i < 3; i++) {
                ((s32 *)s)[i] = 0;
            }
            StringReserve_107e80(s, src->m04);
            StringReplace_106f90(s, 0, 0, src->m08, src->m08 + src->m04, al);
        }
        s->m0C = src->m0C;
    }
    n->right = 0;
    n->left = 0;
    n->parent = (s32)y | (n->parent & 1);
    if (addleft != 0) {
        y->left = n;
    } else {
        y->right = n;
    }
    t->size = t->size + 1;
    RbTreeRebalance_1a7480(n, t->head);
    if (setlmost != 0) {
        t->lmost = n;
    }
    return n;
}
