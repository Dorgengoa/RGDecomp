/* rgp:protos */
#define RGP_SELF_ViewSetFov_142f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Forwards five floats out of the record at +0xF20, with the caller's own
   float argument in front of them: $f12 is never loaded here, so it is
   passed straight through, and $f13..$f17 are 0x20, 0x24, 0x44, 0x48, 0x4C. */

typedef struct Rec00142f10 {
    u8 pad0[0x20];
    f32 unk20;
    f32 unk24;
    u8 pad28[0x44 - 0x28];
    f32 unk44;
    f32 unk48;
    f32 unk4C;
} Rec00142f10;

typedef struct Obj00142f10 {
    u8 pad0[0xF20];
    Rec00142f10 *unkF20;
} Obj00142f10;

/*rgp*/

void ViewSetFov_142f10(Obj00142f10 *self, f32 t)
{
    Rec00142f10 *r;

    r = self->unkF20;
    if (r != 0) {
        ViewSetProjection_143000((void *)self, t, r->unk20, r->unk24, r->unk44, r->unk48, r->unk4C);
    }
}
