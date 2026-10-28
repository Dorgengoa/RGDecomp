/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityReset_51d280 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051D280 -- a plain field-reset.  The store block is written in
 * RETAIL'S EMISSION ORDER, which is NOT ascending field offset here (0x6A sits
 * between 0x66 and 0x67); see the mixed load/store-group recipe.
 * `lui 0x3F80` + `sw` (not mtc1/swc1) is how mwcc stores a float constant whose
 * low half is zero, so +0x6C is an f32 = 1.0f. */
typedef struct Ent {
    u8 pad00[0x60];
    s8 f60, f61, f62, f63;
    s8 f64, f65, f66, f67, f68, f69;
    s16 f6A;
    f32 f6C;           /* +0x6C */
} Ent;

extern void memset(void *dst, s32 c, s32 n);

void insect_InsectAbilityReset_51d280(Ent *o)
{
    o->f60 = -1;
    o->f61 = -1;
    o->f62 = -1;
    o->f63 = -1;
    o->f64 = 0;
    o->f65 = 0;
    o->f66 = 0;
    o->f6A = 0;
    o->f67 = 0;
    o->f68 = 0;
    o->f69 = 0;
    o->f6C = 1.0f;
    memset(o, 0, 0x20);
    memset((u8 *)o + 0x20, 0, 0x10);
    memset((u8 *)o + 0x30, 0, 0x20);
    memset((u8 *)o + 0x50, 0, 0x10);
}
