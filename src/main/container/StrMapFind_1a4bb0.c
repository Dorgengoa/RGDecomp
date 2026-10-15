#include "types.h"

extern s32 Strcasecmp_1345b8(const char *a, const char *b);

struct Str4bb0 {
    s32 m00;
    u8 pad004[0x4];
    const char *m08;
};

struct Node4bb0 {
    struct Node4bb0 *left;      /* +0x00 */
    struct Node4bb0 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Str4bb0 key;         /* +0x0C */
};

struct Tree4bb0 {
    s32 size;                   /* +0x00 */
    struct Node4bb0 head;       /* +0x04 */
};

#define CSTR4bb0(s) (((s)->m00 & 1) ? (s)->m08 : (const char *)(s) + 1)

void StrMapFind_1a4bb0(struct Node4bb0 **out, struct Tree4bb0 *t, struct Str4bb0 *key)
{
    struct Node4bb0 *x;
    struct Node4bb0 *y;

    x = t->head.left;
    y = &t->head;
    while (x != 0) {
        if (Strcasecmp_1345b8(CSTR4bb0(&x->key), CSTR4bb0(key)) >= 0) {
            y = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if (y == &t->head || Strcasecmp_1345b8(CSTR4bb0(key), CSTR4bb0(&y->key)) < 0) {
        *out = &t->head;
    } else {
        *out = y;
    }
}
