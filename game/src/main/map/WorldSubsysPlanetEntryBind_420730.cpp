/* WorldSubsysPlanetEntryBind_420730 -- byte-identical clone of WorldSubsysPlanetEntryBind_412a80 (248 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 3-member byte-identical group (248 B each):
   WorldSubsysPlanetEntryBind_420730 / WorldSubsysPlanetEntryBind_413110 / WorldSubsysPlanetEntryBind_420730.

   C++ because of the `jalr $25` -- vptr at +0, vtable slot 0x1C, which with
   this compiler's two-word vtable header is virtual index 5
   (0x1C == 4 * (5 + 2); see the 0x88 == 4 * (32 + 2) reading in
   src/s22b/DataTableCompareThunk_3ba1d0.cpp).  Bit 0 of the byte at +0x7A is a 1-bit
   bitfield: retail masks with a REGISTER -2, which is the bitfield insert
   sequence, not `& 0xFE`. */

struct Link12a80 {
    struct Node12a80 *m00;      /* +0x00 */
    u8    pad004[0x14 - 0x04];
    void *m14;                  /* +0x14 */
};

struct Node12a80 {
    u8    pad000[0xC];
    void *m0C;                  /* +0x0C */
};

class C12a80 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    bool v5(void *a, void *b, void *c) { return (vc_u8)VCM(vc_u32, (void *, void *, void *, void *), 0x1C, a, b, c) != 0; }

    u8    pad004[0x08 - 0x04];
    void *m08;                  /* +0x08 */
    u8    pad00C[0x10 - 0x0C];
    s32   m10;                  /* +0x10 */
    u8    pad014[0x7A - 0x14];
    u8    busy : 1;             /* +0x7A bit 0 */
    u8    rest : 7;
    u8    pad07B[0x94 - 0x7B];
    struct Link12a80 *m94;      /* +0x94 */
};

extern "C" void Sprintf_1343b8(void *out, void *a, void *b, void *c);

extern "C" bool WorldSubsysPlanetEntryBind_420730(C12a80 *o, struct Link12a80 *link, void *ctx)
{
    u8 scratch[0x80] __attribute__((aligned(16)));
    bool ok;

    if (o->m10 == 0 || link == 0) {
        return false;
    }
    if (link->m00 == 0) {
        return false;
    }
    if (link->m14 == 0) {
        return false;
    }
    if (link->m00->m0C == 0) {
        return false;
    }
    if (o->m08 == 0) {
        return false;
    }
    Sprintf_1343b8(scratch, o->m08, link->m00->m0C, link->m00->m0C);
    o->busy = 1;
    o->m94 = 0;
    ok = o->v5(link->m14, ctx, scratch);
    if (ok) {
        o->m94 = link;
    }
    o->busy = 0;
    return ok;
}
