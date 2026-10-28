/* rgp:protos */
#define RGP_SELF_EvTargetPointObjPreUpdate_2f9280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EvTargetPointObjPreUpdate_2f9280 -- copies the 0x10..0x57 block up to 0x58..0x9F.
   The first 36 bytes go as three 12-byte float sub-struct assignments
   (batched lwc1 x3 / swc1 x3); the remaining 36 bytes are a single
   struct assignment, which mwcc emits as its word block-copy loop. */

typedef struct V3 { f32 x, y, z; } V3;
typedef struct B36 { u32 w[9]; } B36;

/*rgp*/

void EvTargetPointObjPreUpdate_2f9280(u8 *p)
{
    EvObjPreUpdateBase_2f9930(p);
    *(V3 *)(p + 0x58) = *(V3 *)(p + 0x10);
    *(V3 *)(p + 0x64) = *(V3 *)(p + 0x1C);
    *(V3 *)(p + 0x70) = *(V3 *)(p + 0x28);
    *(B36 *)(p + 0x7C) = *(B36 *)(p + 0x34);
}
