/* rgp:protos */
#define RGP_SELF_VariantRecCopy_36ee10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rec_FUN_0036ee10 {
    u8 pad000[0x10];
    s32 f10;
    u8 pad014[0x4];
    u64 f18;
    s32 f20;
    u8 pad024[0x4];
    u64 f28;
    s16 f30;
    u8 b32_0 : 1;
    u8 b32_r : 7;
} Rec_FUN_0036ee10;

/*rgp*/

void VariantRecCopy_36ee10(Rec_FUN_0036ee10 *d, Rec_FUN_0036ee10 *s)
{
    VariantCopy_36f5e0(d, s, 0);
    d->f10 = s->f10;
    d->f18 = s->f18;
    d->f20 = s->f20;
    d->f28 = s->f28;
    d->f30 = s->f30;
    d->b32_0 = s->b32_0;
}
