#include "types.h"
#pragma opt_propagation off

/* Clone-group member (s44c, group of 5: EquipSlotSerialize_39f4e0, CharaSysSerialize_3a0b30,
   StateBlockSerialize_3cb9d0, OptionsSerialize_3d5de0, InsectTeamTableSerialize_42fdd0). Identical shape to
   EquipSlotSerialize_39f4e0.cpp -- see that file for the full derivation and the
   register-permutation residue writeup. Only the literal "kind" code handed
   to SerialWriteChunkHeader_370e50 differs (1 here vs 7/0xE/2/0xF in the siblings).

   STATUS: length-exact (56/56 words), same 28-bad pure callee-saved
   register permutation as EquipSlotSerialize_39f4e0 -- confirms the residue is a
   property of the shared shape, not of this unit's specific constant. */

struct VE003d5de0 {
    virtual s32 v0();  /* slot 0x08 -- returns a byte offset from `self` */
    virtual void v1(); /* slot 0x0C -- unused by this function */
    virtual s32 v2();  /* slot 0x10 -- returns a byte count */
};

extern "C" s32 SerialWriteChunkHeader_370e50(s32 p0, s32 p1, s32 p2, s32 p3, s32 **p4);
extern "C" void memcpy(void *, void *, s32);

extern "C" s32 OptionsSerialize_3d5de0(VE003d5de0 *self, s32 arg1, s32 arg2)
{
    s32 rem;
    s32 dest;
    s32 len;
    s32 total;
    s32 count;
    s32 *sp6C;
    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    rem = arg2;
    sp6C = 0;
    total = 0;
    len = SerialWriteChunkHeader_370e50(arg1, rem, 1, 0, &sp6C);
    dest = arg1 + len;
    rem = rem - len;
    total = total + len;
    count = self->v2();
    if (count <= rem) {
        memcpy((void *)dest, (u8 *)self + self->v0(), count);
        total += count;
        if (sp6C != 0) {
            *sp6C += count;
        }
    }
    return total;
}
