/* rgp:protos */
#define RGP_SELF_ItemDefGetKind2Or3Data_40e140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj0040e140 {
    u8 pad0[0x20];
    s32 unk20;
} Obj0040e140;

/*rgp*/
/*rgp*/

s32 ItemDefGetKind2Or3Data_40e140(Obj0040e140 *self)
{
    s32 result;

    if (((unsigned char)ItemDefIsKind3_40e350((void *)self)) == 0) {
        result = (((unsigned char)ItemDefIsKind2_40e360(self)) != 0) ? self->unk20 : 0;
    } else {
        result = self->unk20;
    }
    return result;
}
