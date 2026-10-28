/* rgp:protos */
#define RGP_SELF_insect_InsectBattleModelMemInit_50e5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E5E0 -- 92 bytes, 23 instructions, no branches.  Straight
 * transcription; the sub-object at +0x4B4C is re-materialised at every call
 * (`addiu $4, $16, 0x4B4C` four times), which is what a member address gives. */

typedef struct Sub {
    u8 pad00[4];
} Sub;

typedef struct Obj {
    u8   pad0000[0xDC];
    s32  f00DC;                     /* +0x00DC */
    u8   pad00E0[0x35F8 - 0xE0];
    u8   f35F8[0x3F8C - 0x35F8];    /* +0x35F8 */
    u8   f3F8C[0x4B4C - 0x3F8C];    /* +0x3F8C */
    Sub  f4B4C;                     /* +0x4B4C */
    u8   pad4B50[0x4F84 - 0x4B50];
    void *f4F84;                    /* +0x4F84 */
    void *f4F88;                    /* +0x4F88 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleModelMemInit_50e5e0(Obj *o)
{
    insect_InsectModelMemClear_512a40(&o->f4B4C);
    insect_InsectModelMemSetScene_512a10(&o->f4B4C);
    insect_InsectModelMemInitHeap_512900(&o->f4B4C, o->f00DC, 0x18380);
    insect_InsectModelMemNop_5128f0(&o->f4B4C);
    o->f4F84 = o->f35F8;
    o->f4F88 = o->f3F8C;
}
