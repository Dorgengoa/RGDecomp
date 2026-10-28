/* rgp:protos */
#define RGP_SELF_TextReaderCtor_15f140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Initialises a Reader: chain to TextReaderBaseCtor_15f190, then clear seven fields and
   hand the object back. Returning the receiver is the Metrowerks constructor
   ABI -- `daddu $2, $16, $0` sits between two of the stores, which is what a
   value already in a callee-saved register looks like when the scheduler has
   somewhere to put it. The seven `sw zero`s are individual fields, not a
   block clear: 0x0, 0x4, 0x8, 0xC, 0x14, 0x2C, 0x30 with gaps. */

typedef struct Reader0015f140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x2C - 0x18];
    s32 unk2C;
    s32 unk30;
} Reader0015f140;

/*rgp*/

Reader0015f140 *TextReaderCtor_15f140(Reader0015f140 *r)
{
    TextReaderBaseCtor_15f190(r);
    r->unk0 = 0;
    r->unk4 = 0;
    r->unk8 = 0;
    r->unkC = 0;
    r->unk14 = 0;
    r->unk2C = 0;
    r->unk30 = 0;
    return r;
}
