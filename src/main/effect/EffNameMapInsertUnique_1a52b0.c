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

extern s32 Strcasecmp_1345b8(const char *a, const char *b);
extern Node *StrMapInsertNode_1a6e00(Tree *t, Node *y, u8 comp, u8 atbegin, Str *v);
extern u8 D_0047E19C;
extern u8 D_0047E1A0;

#define SDATA(s) (((s)->cap & 1) ? (s)->ptr : (char *)(s) + 1)

void EffNameMapInsertUnique_1a52b0(Ret *ret, Tree *t, Str *v)
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
        Node *volatile deada; Node *nna = StrMapInsertNode_1a6e00(t, y, comp, atbegin, v);
        ret->first = nna;
        deada = nna;
        ret->second = D_0047E19C;
    } else {
        Node *volatile deadb;
        ret->first = j;
        deadb = j;
        ret->second = D_0047E1A0;
    }
}
