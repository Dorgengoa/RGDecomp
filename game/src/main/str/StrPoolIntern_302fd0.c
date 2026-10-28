/* rgp:protos */
#define RGP_SELF_StrPoolIntern_302fd0 1
#define RGP_SELF_find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    struct Node *next;
    char name[4];
} Node;

/*rgp*/
/*rgp*/
/*rgp*/
s32 strcmp(const char *, const char *);
char *strcpy(char *, const char *);

static inline char *find(Node **list, const char *name)
{
    Node *n;

    if (name == 0) {
        return 0;
    }
    for (n = *list; n != 0; n = n->next) {
        if (strcmp(name, n->name) == 0) {
            return n->name;
        }
    }
    return 0;
}

char *StrPoolIntern_302fd0(Node **arg0, const char *arg1, s32 arg2)
{
    char *s;
    Node *n;
    Node *p;

    if (arg1 == 0) {
        return 0;
    }
    s = find(arg0, arg1);
    if (s != 0) {
        return s;
    }
    if (arg2 == 0) {
        return 0;
    }
    n = (Node *)MemStackAllocQw_14d950(arg2, AlignUp16_1cacd0(StrSizeWithNul_1cac60(arg1) + 4) >> 4);
    if (n == 0) {
        return 0;
    }
    n->next = 0;
    if (*arg0 == 0) {
        *arg0 = n;
    } else {
        for (p = *arg0; p->next != 0; p = p->next) {
        }
        p->next = n;
    }
    strcpy(n->name, arg1);
    return n->name;
}
