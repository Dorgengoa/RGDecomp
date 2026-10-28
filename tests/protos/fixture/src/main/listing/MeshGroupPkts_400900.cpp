#include "types.h"
/* vcall-forward + def-vcall-v0: retail's jalr gets the untouched $a1/$a2 and its
   $v0 is the function's return (ModelMeshGetGroupPktsMaybe_15b150 class) */
struct M80 {
    u8 pad[0x10];
    virtual s32 v0();
    virtual s32 v1();
};
struct L4 { s32 m0; };

extern "C" void MeshGroupPkts_400900(M80 *p0, s32 p1, s32 p2)
{
    p0->v1();
    ((L4 *)p2)->m0 = -1;
}

/* vcall-widen: retail's jalr receives this function's untouched $a1, which the C
   never declared (CharaGetEquippedWeapon_3acd40 -> slot 0x374 =
   CharaGetWeaponId_2f5a50(chara, slot)) */
struct W8 {
    virtual s32 g0();
};

extern "C" s32 GetEquipped_400980(W8 *o)
{
    return o->g0();
}
