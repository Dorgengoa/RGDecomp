#include "types.h"

/* Tree-node unlink.  &parent->child is held in a local (the addiu before the
   compare).  bnel $3,$4 -> the FALL-THROUGH (equal) case is the `if` body.
   The three clears are NOT a shared tail: retail writes them out in each arm
   (8 zero stores), and the else arm clears `parent` FIRST. */

struct Node2 {
    u8 pad000[0x40];
    struct Node2 *parent; /* 0x40 */
    struct Node2 *prev;   /* 0x44 */
    struct Node2 *next;   /* 0x48 */
    struct Node2 *child;  /* 0x4C */
};

void MemStackDetach_14d5e0(struct Node2 *n)
{
    struct Node2 *p;
    struct Node2 **pp;

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
