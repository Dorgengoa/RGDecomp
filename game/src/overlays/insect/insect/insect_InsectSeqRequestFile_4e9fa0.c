/* rgp:protos */
#define RGP_SELF_insect_InsectSeqRequestFile_4e9fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004E9FA0 -- straight-line setup.  insect_D_005248D0 / insect_D_005248D8 are
 * overlay data (0x0052xxxx), outside the gp window 0x47D170..0x48D170, so both
 * externs are `const` -- otherwise mwcc gives them %gp_rel and the link dies
 * with a GP offset overflow while the object still compiles clean. */
typedef struct Ent {
    u8 pad00[0x198];
    u8 f198[0x40];     /* +0x198 */
} Ent;

extern u8 insect_D_005248D0[];
extern u8 insect_D_005248D8[];
/*rgp*/
/*rgp*/
extern void memset(void *dst, s32 c, s32 n);
extern void Sprintf_1343b8(void *dst, const u8 *a, const u8 *b, s32 c);

void insect_InsectSeqRequestFile_4e9fa0(Ent *o, s32 k)
{
    insect_InsectSeqSetState_4ea3c0(o, 2);
    insect_InsectSeqSetSubState_4ea350(o, 0);
    memset(o->f198, 0, 0x40);
    Sprintf_1343b8(o->f198, insect_D_005248D0, insect_D_005248D8, k);
}
