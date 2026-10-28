/* rgp:protos */
#define RGP_SELF_StrMapInsertNode_1a6fa0 1
#define RGP_SELF_StringReplace_106f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Consolea6fa0 {
    u8 pad00[0x8];
    void *unk08;
    void *out;              /* +0x0C */
} Consolea6fa0;

extern Consolea6fa0 *const volatile D_00449858;
extern char D_0045A710[];
extern char D_0045A770[];

extern void Fprintf_12f9a0(void *out, const char *fmt);
/*rgp*/
/*rgp*/
/*rgp*/
struct Alloca6fa0; extern void StringReplace_106f90(void *s, s32 a, s32 b, const char *first, const char *last, struct Alloca6fa0 al);
/*rgp*/

struct Alloca6fa0 {
    char c;
};

struct Bodya6fa0 {
    f32 v[3];
};

struct Stra6fa0 {
    s32 m00;
    s32 m04;
    const char *m08;
    s32 m0C;
};

struct Nodea6fa0 {
    struct Nodea6fa0 *left;      /* +0x00 */
    struct Nodea6fa0 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Stra6fa0 val;         /* +0x0C */
};

struct Treea6fa0 {
    s32 size;                   /* +0x00 */
    void *head;                 /* +0x04 */
    u8 pad008[0x4];
    struct Nodea6fa0 *lmost;     /* +0x0C */
};

struct Nodea6fa0 *StrMapInsertNode_1a6fa0(struct Treea6fa0 *t, struct Nodea6fa0 *y, s32 addleft,
                              s32 setlmost, struct Stra6fa0 *src)
{
    struct Nodea6fa0 *n;
    struct Stra6fa0 *s;
    u32 i;
    struct Alloca6fa0 al __attribute__((aligned(16)));

    if ((u32)t->size > 0xFFFFFFFEU) {
        Fprintf_12f9a0(D_00449858->out, D_0045A710);
        Abort_12de80();
    }
    n = (struct Nodea6fa0 *)OperatorNew_100990(0x1C);
    if (n == 0) {
        Fprintf_12f9a0(D_00449858->out, D_0045A770);
        Abort_12de80();
    }
    s = &n->val;
    if (s != 0) {
        if ((src->m00 & 1) == 0) {
            *(struct Bodya6fa0 *)s = *(struct Bodya6fa0 *)src;
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
