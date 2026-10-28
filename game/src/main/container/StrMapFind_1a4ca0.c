/* rgp:protos */
#define RGP_SELF_StrMapFind_1a4ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Str4ca0 {
    s32 m00;
    u8 pad004[0x4];
    const char *m08;
};

struct Node4ca0 {
    struct Node4ca0 *left;      /* +0x00 */
    struct Node4ca0 *right;     /* +0x04 */
    s32 parent;                 /* +0x08 */
    struct Str4ca0 key;         /* +0x0C */
};

struct Tree4ca0 {
    s32 size;                   /* +0x00 */
    struct Node4ca0 head;       /* +0x04 */
};

#define CSTR4ca0(s) (((s)->m00 & 1) ? (s)->m08 : (const char *)(s) + 1)

void StrMapFind_1a4ca0(struct Node4ca0 **out, struct Tree4ca0 *t, struct Str4ca0 *key)
{
    struct Node4ca0 *x;
    struct Node4ca0 *y;

    x = t->head.left;
    y = &t->head;
    while (x != 0) {
        if (Strcasecmp_1345b8(CSTR4ca0(&x->key), CSTR4ca0(key)) >= 0) {
            y = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if (y == &t->head || Strcasecmp_1345b8(CSTR4ca0(key), CSTR4ca0(&y->key)) < 0) {
        *out = &t->head;
    } else {
        *out = y;
    }
}
