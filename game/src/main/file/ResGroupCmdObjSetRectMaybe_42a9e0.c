/* rgp:protos */
#define RGP_SELF_ResGroupCmdObjSetRectMaybe_42a9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Script-command handler family (0x42a9xx-0x42b6xx).  The operand stream is
   read 8 bytes at a time; retail keeps a REAL incrementing cursor in a
   callee-saved register (addiu cur,8 in the jal delay slot + daddu a0,cur),
   which is the POST-INCREMENT form f(p++).  Writing `f(p); p += 8;` instead
   lets mwcc fold every advance into base+offset and the unit comes out one
   word short per operand -- measured INERT across ten arithmetic spellings
   on ResGroupCmdObjSetPair_42aae0 (all one object sha1). */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x12];
    s16 m12;
    s16 m14;
    s16 m16;
    s16 m18;
};

s32 ResGroupCmdObjSetRectMaybe_42a9e0(SArg *p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ResGroupListCurElem_42a510();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0++);
    r0->m12 = r1;
    r2 = VariantGetInt_15f780(p0++);
    r0->m14 = r2;
    r3 = VariantGetInt_15f780(p0++);
    r0->m16 = r3;
    r4 = VariantGetInt_15f780(p0);
    r0->m18 = r4;
    return 1;
}
