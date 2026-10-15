#pragma opt_propagation off
#include "types.h"

/* Clone-group member (s44c, group of 5: EquipSlotSerialize_39f4e0, CharaSysSerialize_3a0b30,
   StateBlockSerialize_3cb9d0, OptionsSerialize_3d5de0, InsectTeamTableSerialize_42fdd0). All five share the identical
   normalized opcode stream; the only difference is the literal "kind" code
   handed to SerialWriteChunkHeader_370e50 (7 / 0xE / 2 / 1 / 0xF here).

   Appends up to `arg2` bytes of some self-formatted representation into the
   caller's buffer `arg1`. SerialWriteChunkHeader_370e50 (already matched, src/s32a) writes a
   prefix into arg1 and optionally records a follow-on write address through
   its out-param; then a virtual call (vtable slot 0x10) asks the object how
   many more bytes it wants to contribute, and -- if the caller's buffer has
   room left -- a second virtual call (vtable slot 0x08) returns a *byte
   offset from `self`* that is memcpy'd out.

   Both `jalr $25` sites are true C++ virtual dispatch (see
   jalr-is-cpp-virtual memory) -- no C spelling reaches `jalr $25`, so this is
   .cpp with a minimal dummy-virtual class. vptr is at offset 0 (`lw
   $25,0x0($16)`), so there is no data padding before the first virtual.

   MATCH (s41 agent36): `#pragma opt_propagation off` + a fresh `rem = arg2`
   at body start (puts the a2 copy in the bgtzl delay slot) + declaration
   order sp6C, dest, len, rem, total, count (picks the s-register colouring).
   The same recipe should close the other four clone-group members. */

struct VE0039f4e0 {
    virtual s32 v0();  /* slot 0x08 -- returns a byte offset from `self` */
    virtual void v1(); /* slot 0x0C -- unused by this function */
    virtual s32 v2();  /* slot 0x10 -- returns a byte count */
};

extern "C" s32 SerialWriteChunkHeader_370e50(s32 p0, s32 p1, s32 p2, s32 p3, s32 **p4);
extern "C" void memcpy(void *, void *, s32);

extern "C" s32 EquipSlotSerialize_39f4e0(VE0039f4e0 *self, s32 arg1, s32 arg2)
{
    s32 *sp6C;
    s32 dest;
    s32 len;
    s32 rem;
    s32 total;
    s32 count;

    if (arg1 == 0) {
        goto ret0;
    }
    if (arg2 > 0) {
        goto body;
    }
ret0:
    return 0;
body:
    rem = arg2;
    sp6C = 0;
    total = 0;
    len = SerialWriteChunkHeader_370e50(arg1, rem, 7, 0, &sp6C);
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
