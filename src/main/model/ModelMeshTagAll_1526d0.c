#include "types.h"
typedef struct N001526d0 {
    struct N001526d0 *next;
    u8 pad[0xC];
    s32 v;                    /* +0x10 */
} N001526d0;

typedef struct S001526d0 {
    u8 pad[0x44];
    N001526d0 *head;
} S001526d0;

s32 ModelMeshTagAll_1526d0(S001526d0 *s, s32 val)
{
    N001526d0 *n;
    s32 *p;
    s32 c;

    c = 0;
    n = s->head;
    while (n != 0) {
        p = &n->v;
        if (p != 0) {
            *p = val;
            c++;
        }
        n = n->next;
    }
    return c;
}
