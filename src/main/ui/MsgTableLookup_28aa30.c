#include "types.h"

extern s32  strncmp(const char *a, const char *b, s32 n);
extern char D_004610B8[];

typedef struct Node {
    s32          key;   /* +0x00 */
    s32          val;   /* +0x04 */
    struct Node *next;  /* +0x08 */
} Node;

s32 MsgTableLookup_28aa30(void *p, s32 key)
{
    Node *n;

    if (p == 0) {
        return 0;
    }
    if (strncmp((char *)p, D_004610B8, 3) != 0) {
        return 0;
    }
    n = (Node *)((u8 *)p + 0x40);
    while (n != 0) {
        if (key == n->key) {
            return n->val;
        }
        n = n->next;
    }
    return 0;
}
