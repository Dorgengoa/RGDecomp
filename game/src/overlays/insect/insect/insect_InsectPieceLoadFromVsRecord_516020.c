/* rgp:protos */
#define RGP_SELF_insect_InsectPieceLoadFromVsRecord_516020 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00516020 -- 352 bytes, 88 instructions, 4 calls.
 * Field-by-field initialisation of a slot from a descriptor.
 */

typedef struct Src {
    u8   pad00[0xF];
    u8   f0F;                       /* +0x0F */
    u8   f10[6];                    /* +0x10 */
    u8   f16;                       /* +0x16 */
    u8   f17;                       /* +0x17 */
    u8   f18;                       /* +0x18 */
    u8   pad19;
    u16  f1A;                       /* +0x1A */
    u16  f1C;                       /* +0x1C */
    u16  f1E;                       /* +0x1E */
    u8   f20b0 : 1;                 /* +0x20 */
    u8   f20b1 : 1;
    u8   f20b2 : 6;
    u8   f21;                       /* +0x21 */
    u8   f22;                       /* +0x22 */
    u8   pad23;
    s16 *f24;                       /* +0x24 */
} Src;

typedef struct Dst {
    u8   pad00[0x10];
    Src *f10;                       /* +0x10 */
    u8   pad14[0x18 - 0x14];
    s8   f18;                       /* +0x18 */
    u8   pad19[0x22 - 0x19];
    s16  f22;                       /* +0x22 */
    s16  f24;                       /* +0x24 */
    s8   f26;                       /* +0x26 */
    u8   pad27;
    s8   f28;                       /* +0x28 */
    u8   pad29;
    u8   f2A[6];                    /* +0x2A */
    u8   pad30[0x36 - 0x30];
    u8   f36;                       /* +0x36 */
    u8   f37;                       /* +0x37 */
    s8   f38;                       /* +0x38 */
    s8   f39;                       /* +0x39 */
    u8   pad3A[0x4C - 0x3A];
    s8   f4C;                       /* +0x4C */
    u8   pad4D[0x4F - 0x4D];
    s8   f4F;                       /* +0x4F */
    s16  f50;                       /* +0x50 */
    u8   pad52[0x54 - 0x52];
    s32  f54;                       /* +0x54 */
    u8   pad58[0x5C - 0x58];
    Src *f5C;                       /* +0x5C */
    u8   pad60[0x68 - 0x60];
    s32  f68;                       /* +0x68 */
    u8   pad6C[0x73 - 0x6C];
    u8   f73;                       /* +0x73 */
    u8   f74;                       /* +0x74 */
} Dst;

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectPieceLoadFromVsRecord_516020(Dst *d, Src *s)
{
    s32 i;

    if (s == 0) {
        return;
    }
    d->f10 = s;
    d->f5C = s;
    d->f18 = s->f18;
    d->f22 = 0;
    d->f24 = 0x64;
    if (d->f18 >= 6) {
        d->f18 = 5;
        d->f22 = 0x2BC;
        d->f24 = 0x2BC;
    }
    insect_InsectPieceSetMaxHp_512ec0(d, s->f1A, 1);
    d->f50 = 0;
    d->f26 = s->f1C;
    d->f28 = s->f1E;
    for (i = 0; i < 6; i++) {
        d->f2A[i] = s->f10[i];
    }
    d->f36 = s->f16;
    d->f37 = s->f17;
    d->f54 = *s->f24;
    insect_InsectPieceSetItemDef_516580(d, s->f24);
    d->f4C = 0;
    if (d->f38 == 0xC) {
        d->f4C = d->f39 * 5 + 0x32;
    }
    d->f4F = 3;
    d->f68 = s->f0F;
    if (s->f20b0 != 0) {
        insect_InsectPieceSetStatus_5132d0(d, 0x16);
    }
    if (s->f20b1 != 0) {
        insect_InsectPieceSetStatus_5132d0(d, 0x17);
    }
    d->f73 = s->f21;
    d->f74 = s->f22;
}
