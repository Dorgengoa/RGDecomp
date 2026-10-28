/* rgp:protos */
#define RGP_SELF_EffNameMapInsertUnique_1a5970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str {
    u32 cap;
    u32 len;
    char *ptr;
} Str;

typedef struct Node {
    struct Node *l;
    struct Node *r;
    struct Node *p;
    Str key;
} Node;

typedef struct Tree {
    s32 unk0;
    Node *root;
} Tree;

typedef struct Iter {
    Node *n;
} Iter;

typedef struct Ret {
    Node *first;
    u8 second;
} Ret;

/*rgp*/
/*rgp*/
extern u8 D_0047E184;
extern u8 D_0047E188;

#define SDATA(s) (((s)->cap & 1) ? (s)->ptr : (char *)(s) + 1)

void EffNameMapInsertUnique_1a5970(Ret *ret, Tree *t, Str *v)
{
    Node *y;
    Node *j;
    Node *x;
    u8 comp;
    u8 atbegin;

    j = 0;
    y = (Node *)&t->root;
    x = t->root;
    comp = 1;
    atbegin = comp;
    while (x != 0) {
        y = x;
        if (Strcasecmp_1345b8(SDATA(v), SDATA(&x->key)) < 0) {
            x = x->l;
            comp = 1;
        } else {
            j = x;
            comp = 0;
            x = x->r;
            atbegin = 0;
        }
    }
    if (j == 0 || Strcasecmp_1345b8(SDATA(&j->key), SDATA(v)) < 0) {
        Node *volatile deada; Node *nna = ((Node *)StrMapInsertNode_1a72e0(t, y, comp, atbegin, v));
        ret->first = nna;
        deada = nna;
        ret->second = D_0047E184;
    } else {
        Node *volatile deadb;
        ret->first = j;
        deadb = j;
        ret->second = D_0047E188;
    }
}
