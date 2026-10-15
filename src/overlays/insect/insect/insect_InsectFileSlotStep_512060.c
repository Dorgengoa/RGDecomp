#include "types.h"
/* insect 0x00512060 -- 220 bytes, 55 instructions.
 *
 * A four-arm state dispatch on `o->f28`.  Every compare is a `beql` INTO its
 * block, so it is a real `switch` and the source case order is the compare
 * chain (4, 3, 2, 1) REVERSED -- see insect-dispatch-branch-polarity.
 * Case 3 is an empty arm: the listing spends a plain `beq` straight to the
 * epilogue on it.
 */

typedef struct Obj {
    u8  pad00[0x24];
    s32 f24;                        /* +0x24 */
    s32 f28;                        /* +0x28 */
} Obj;

extern void func_1CD340(s32 h, s32 id);
extern s32  func_1CD4F0(s32 h, s32 id);
extern s32  func_1CD870(s32 h, Obj *o, s32 k);
extern s32  func_1F59D0(void);

void insect_InsectFileSlotStep_512060(Obj *o)
{
    s32 h;

    if (o->f28 != 0) {
        h = func_1F59D0();
        if (h != 0) {
            switch (o->f28) {
            case 1:
                o->f24 = func_1CD870(h, o, 0);
                o->f28 = 2;
                break;
            case 2:
                switch (func_1CD4F0(h, o->f24)) {
                case -1:
                case 0:
                    break;
                case 1:
                    o->f28 = 3;
                    break;
                }
                break;
            case 3:
                break;
            case 4:
                func_1CD340(h, o->f24);
                o->f28 = 0;
                o->f24 = -1;
                break;
            }
        }
    }
}
