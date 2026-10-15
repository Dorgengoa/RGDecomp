#include "types.h"

/* Retail FALLS THROUGH into the `sw $16,0x4($17)`, so the source's `if` body
   is the assignment and the call is the else arm. */

extern void ListAppendTail_19b1f0(void *);

void SceneTreeAttachChild_19b320(void **a, void **b)
{
    if (a[1] == 0) {
        a[1] = b;
    } else {
        ListAppendTail_19b1f0(a[1]);
    }
    b[0] = a;
}
