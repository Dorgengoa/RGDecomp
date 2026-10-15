#include "types.h"

/* s88m de-asm: walk n links of a singly linked list (next at +4), stopping at NULL.
 * The `((l != 0) ^ 1) == 0` spelling keeps retail's materialised sltu/xori test. */
typedef struct L {
    s32 x;
    struct L *next;
} L;

L *DListNodeAdvance_42eb00(L *l, s32 n)
{
    while (((l != 0) ^ 1) == 0 && n > 0) {
        l = l->next;
        n--;
    }
    return l;
}
