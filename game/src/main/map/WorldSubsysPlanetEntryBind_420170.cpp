#include "types.h"

/* Clone of WorldSubsysPlanetEntryBind_403920 -- the seven members of this group are
   instruction-identical.

   Build the transform into a stack scratch, clear the pending slot, then
   offer it to the object; the slot is only latched if the object accepts.
   Every guard is a separate early return -- each one is a `bnel` whose
   likely slot carries the NEXT guard's load, which is why the loads appear
   one branch earlier than the test that uses them. */

class VD {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    bool v5(void * a0, void * a1, void * a2) { return (vc_u8)VCM(vc_u32, (void *, void *, void *, void *), 0x1C, a0, a1, a2) != 0; }
};

typedef struct Src00420170 {
    void *m00;
    u8    pad004[0x14 - 0x04];
    void *m14;
} Src00420170;

typedef struct Mid00420170 {
    u8    pad000[0xC];
    void *m0C;
} Mid00420170;

typedef struct Dst00420170 {
    u8    pad000[0x8];
    void *m08;
    void *m0C;
    s32   m10;
    u8    pad014[0x94 - 0x14];
    void *m94;
} Dst00420170;

extern "C" void Sprintf_1343b8(void *, void *, void *, void *);

extern "C" bool WorldSubsysPlanetEntryBind_420170(Dst00420170 *dst, Src00420170 *src, void *ctx)
{
    u8 scratch[0x80] __attribute__((aligned(16)));
    Mid00420170 *mid;
    void *node;
    bool ok;

    if (dst->m10 == 0 || src == 0) {
        return 0;
    }
    mid = (Mid00420170 *)src->m00;
    if (mid == 0) {
        return 0;
    }
    if (src->m14 == 0) {
        return 0;
    }
    node = mid->m0C;
    if (node == 0) {
        return 0;
    }
    if (dst->m08 == 0) {
        return 0;
    }
    Sprintf_1343b8(scratch, dst->m08, node, node);
    dst->m94 = 0;
    ok = ((VD *)dst)->v5(src->m14, ctx, scratch);
    if (ok) {
        dst->m94 = src;
    }
    return ok;
}
