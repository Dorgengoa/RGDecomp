/* rgp:protos */
#define RGP_SELF_SceneTreeAttachChild_19b320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Retail FALLS THROUGH into the `sw $16,0x4($17)`, so the source's `if` body
   is the assignment and the call is the else arm. */

/*rgp*/

void SceneTreeAttachChild_19b320(void **a, void **b)
{
    if (a[1] == 0) {
        a[1] = b;
    } else {
        ListAppendTail_19b1f0(a[1], (void *)b);
    }
    b[0] = a;
}
