#include "types.h"

extern s32 Strcasecmp_1345b8(const char *a, const char *b);

struct Str4ac0 {
    s32 m00;
    u8 pad004[0x4];
    const char *m08;
};

struct Node4ac0 {
    struct Node4ac0 *left;      /* +0x00 */
    struct Node4ac0 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Str4ac0 key;         /* +0x0C */
};

struct Tree4ac0 {
    s32 size;                   /* +0x00 */
    struct Node4ac0 head;       /* +0x04 */
};

#define CSTR4AC0(s) (((s)->m00 & 1) ? (s)->m08 : (const char *)(s) + 1)

void StrMapFind_1a4ac0(struct Node4ac0 **out, struct Tree4ac0 *t, struct Str4ac0 *key)
{
    struct Node4ac0 *x;
    struct Node4ac0 *y;

    x = t->head.left;
    y = &t->head;
    while (x != 0) {
        if (Strcasecmp_1345b8(CSTR4AC0(&x->key), CSTR4AC0(key)) >= 0) {
            y = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if (y == &t->head || Strcasecmp_1345b8(CSTR4AC0(key), CSTR4AC0(&y->key)) < 0) {
        *out = &t->head;
    } else {
        *out = y;
    }
}
