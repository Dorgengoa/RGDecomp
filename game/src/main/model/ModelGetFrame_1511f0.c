/* rgp:protos */
#define RGP_SELF_ModelGetFrame_1511f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Look an id up in the table at +0x104, but only if the object at +0x0 is
   live. The guard is spelled with the LIVE case inside it and the zero after,
   which is what puts the zeroing in retail's beql delay slot -- the same rule
   ModelObjGetMotionName_1add90 needed. ArrayGetChecked_152fd0 is the bounds-checked accessor. */

typedef struct Obj001511f0 {
    s32 unk0;
    u8 pad4[0x104 - 0x4];
    void *table;       /* +0x104 */
} Obj001511f0;

/*rgp*/

void *ModelGetFrame_1511f0(Obj001511f0 *self, s32 id)
{
    if (self->unk0 != 0) {
        return ArrayGetChecked_152fd0(self->table, id);
    }
    return 0;
}
