#include "types.h"
/* insect 0x00522860 -- 144 bytes.  A ten-slot search: fetch, skip nulls,
 * match the s8 tag at +0x71 against the parameter, then confirm with a
 * predicate call.  `beql` into the increment is the null CONTINUE. */
typedef struct Obj {
    u8 pad00[0x71];
    s8 f71;                         /* +0x71 */
} Obj;

extern Obj *insect_InsectAiGetPiece_5228f0(void *a, s32 i);
extern s32  insect_InsectPieceIsKing_514b00(Obj *o);

Obj *insect_InsectAiFindKing_522860(void *a, s32 tag)
{
    s32  i;
    Obj *o;

    for (i = 0; i < 0xA; i++) {
        o = insect_InsectAiGetPiece_5228f0(a, i);
        if (o != 0) {
            if (tag == o->f71) {
                if (insect_InsectPieceIsKing_514b00(o) != 0) {
                    return o;
                }
            }
        }
    }
    return 0;
}
