#include "types.h"

/* Known-positive sibling shape of CharaSysAttackChainEnd_3a1090 (byte-identical, in cunits):
   a BITFIELD INSERT -- here of a PARAMETER, at bit 1. */

typedef struct ObjFUN_003c9760 {
    u8  pad[0x42D0];
    u8  lo : 1;
    u8  b : 1;
    u8  hi : 6;
} ObjFUN_003c9760;

s32 PartyScriptFlagSetMaybe_3c9760(ObjFUN_003c9760 *p, u8 v)
{
    p->b = v;
    return 1;
}
