#include "types.h"
/* insect 0x004E9FA0 -- straight-line setup.  D_005248D0 / D_005248D8 are
 * overlay data (0x0052xxxx), outside the gp window 0x47D170..0x48D170, so both
 * externs are `const` -- otherwise mwcc gives them %gp_rel and the link dies
 * with a GP offset overflow while the object still compiles clean. */
typedef struct Ent {
    u8 pad00[0x198];
    u8 f198[0x40];     /* +0x198 */
} Ent;

extern const u8 D_005248D0[];
extern const u8 D_005248D8[];
extern void insect_InsectSeqSetState_4ea3c0(Ent *o, s32 b);
extern void insect_InsectSeqSetSubState_4ea350(Ent *o, s32 b);
extern void func_131B60(void *dst, s32 c, s32 n);
extern void func_1343B8(void *dst, const u8 *a, const u8 *b, s32 c);

void insect_InsectSeqRequestFile_4e9fa0(Ent *o, s32 k)
{
    insect_InsectSeqSetState_4ea3c0(o, 2);
    insect_InsectSeqSetSubState_4ea350(o, 0);
    func_131B60(o->f198, 0, 0x40);
    func_1343B8(o->f198, D_005248D0, D_005248D8, k);
}
