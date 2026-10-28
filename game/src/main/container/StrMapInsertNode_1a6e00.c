/* rgp:protos */
#define RGP_SELF_StrMapInsertNode_1a6e00 1
#define RGP_SELF_StringReplace_106f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Console6e00 {
    u8 pad00[0x8];
    void *unk08;
    void *out;              /* +0x0C */
} Console6e00;

extern Console6e00 *const volatile D_00449858;
extern char D_0045A710[];
extern char D_0045A790[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
/*rgp*/
/*rgp*/
/*rgp*/
struct Alloc6e00; extern void StringReplace_106f90(void *s, s32 a, s32 b, const char *first, const char *last, struct Alloc6e00 al);
/*rgp*/

struct Alloc6e00 {
    char c;
};

struct Body6e00 {
    f32 v[3];
};

struct Str6e00 {
    s32 m00;
    s32 m04;
    const char *m08;
    s32 m0C;
};

struct Node6e00 {
    struct Node6e00 *left;      /* +0x00 */
    struct Node6e00 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Str6e00 val;         /* +0x0C */
};

struct Tree6e00 {
    s32 size;                   /* +0x00 */
    void *head;                 /* +0x04 */
    u8 pad008[0x4];
    struct Node6e00 *lmost;     /* +0x0C */
};

struct Node6e00 *StrMapInsertNode_1a6e00(struct Tree6e00 *t, struct Node6e00 *y, s32 addleft,
                              s32 setlmost, struct Str6e00 *src)
{
    struct Node6e00 *n;
    struct Str6e00 *s;
    u32 i;
    struct Alloc6e00 al __attribute__((aligned(16)));

    if ((u32)t->size > 0xFFFFFFFEU) {
        Fprintf_12f9a0(D_00449858->out, D_0045A710);
        Abort_12de80();
    }
    n = (struct Node6e00 *)OperatorNew_100990(0x1C);
    if (n == 0) {
        Fprintf_12f9a0(D_00449858->out, D_0045A790);
        Abort_12de80();
    }
    s = &n->val;
    if (s != 0) {
        if ((src->m00 & 1) == 0) {
            *(struct Body6e00 *)s = *(struct Body6e00 *)src;
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
