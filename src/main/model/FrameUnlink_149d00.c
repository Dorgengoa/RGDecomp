#include "types.h"

/* Tree-node unlink.  &parent->child is held in a local (the addiu before the
   compare).  bnel $3,$4 -> the FALL-THROUGH (equal) case is the `if` body.
   The three clears are NOT a shared tail: retail writes them out in each arm
   (8 zero stores), and the else arm clears `parent` FIRST. */

struct Node {
    u8 pad000[4];
    struct Node *parent; /* 0x04 */
    struct Node *child;  /* 0x08 */
    struct Node *next;   /* 0x0C */
    struct Node *prev;   /* 0x10 */
};

void FrameUnlink_149d00(struct Node *n)
{
    struct Node *p;
    struct Node **pp;

    p = n->parent;
    if (p != 0) {
        pp = &p->child;
        if (*pp == n) {
            *pp = n->next;
            if (n->next != 0) {
                n->next->prev = 0;
            }
            n->parent = 0;
            n->next = 0;
            n->prev = 0;
        } else {
            n->parent = 0;
            if (n->prev != 0) {
                n->prev->next = n->next;
            }
            n->next = 0;
            n->prev = 0;
        }
    }
}
