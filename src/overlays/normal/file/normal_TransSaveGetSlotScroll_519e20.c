#include "types.h"
/* normal 0x00519E20 -- NULL-guarded lookup returning one s16 field.
 * The `beql` delay slot carries `daddu $2,$0,$0`: the guard is written
 * POSITIVE with the `return 0` as the TAIL, so the shared-return conversion
 * puts the zero in the delay slot.  The negative form costs `b`+`move`. */

typedef struct Node {
    u8  pad00[0x16];
    s16 f16;
} Node;

extern void *D_00484720;          /* gp - 0xA50 */

extern Node *func_28EC30(void *p, s32 b);

s32 normal_TransSaveGetSlotScroll_519e20(void)
{
    if (D_00484720 != NULL) {
        return func_28EC30(D_00484720, 4)->f16;
    }
    return 0;
}
