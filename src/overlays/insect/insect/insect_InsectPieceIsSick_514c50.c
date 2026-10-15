#include "types.h"
/* insect 0x00514c50 -- 32 B / 8 words.  Four-member family (00514bf0/c10/c30/c50)
 * that differs only in the constant handed to insect_InsectPieceTestStatus_513280.
 * `sltu $2,$0,$2` after the call is the `!= 0` normalisation.
 */

typedef struct Ent Ent;

extern s32 insect_InsectPieceTestStatus_513280(Ent *e, s32 k);

s32 insect_InsectPieceIsSick_514c50(Ent *e)
{
    return insect_InsectPieceTestStatus_513280(e, 3) != 0;
}
