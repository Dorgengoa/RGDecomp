#include "types.h"

extern s32 Strcasecmp_1345b8(const char *a, const char *b);

struct Str4d90 {
    s32 m00;
    u8 pad004[0x4];
    const char *m08;
};

struct Node4d90 {
    struct Node4d90 *left;      /* +0x00 */
    struct Node4d90 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Str4d90 key;         /* +0x0C */
};

struct Tree4d90 {
    s32 size;                   /* +0x00 */
    struct Node4d90 head;       /* +0x04 */
};

#define CSTR4d90(s) (((s)->m00 & 1) ? (s)->m08 : (const char *)(s) + 1)

void StrMapFind_1a4d90(struct Node4d90 **out, struct Tree4d90 *t, struct Str4d90 *key)
{
    struct Node4d90 *x;
    struct Node4d90 *y;

    x = t->head.left;
    y = &t->head;
    while (x != 0) {
        if (Strcasecmp_1345b8(CSTR4d90(&x->key), CSTR4d90(key)) >= 0) {
            y = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if (y == &t->head || Strcasecmp_1345b8(CSTR4d90(key), CSTR4d90(&y->key)) < 0) {
        *out = &t->head;
    } else {
        *out = y;
    }
}
