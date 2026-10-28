/* rgp:protos */
#define RGP_SELF_DrawBufPairInitMaybe_15dc50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two 0x58-byte request records built on the stack and handed to DrawListInitDoubleBufMaybe_1427e0.
   Stack locals are allocated in REVERSE declaration order, so `t1` (sp+0xB0)
   is declared first and `t2` (sp+0x50) second.  The fourth parameter ($7) is
   never read - it is a real, dead argument. */

typedef struct Rec {
    void *m00;
    void *m04;
    u8 m08[0x50];
} Rec;

extern void *D_004810A4;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DrawBufPairInitMaybe_15dc50(void *a, void *b, void *c, void *unused, void *e)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Rec)]; char m1[0x60]; char m2[0x48]; char m3[0x40]; })];
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x0 + sizeof(Rec)]; char m1[0x60]; char m2[0x48]; char m3[0x40]; })];

    MemStackCtor_14e030((*(Rec *)(rgp_blk1 + 0x0)).m08);
    MemStackCtor_14e030((*(Rec *)(rgp_blk2 + 0x0)).m08);
    (*(Rec *)(rgp_blk1 + 0x0)).m00 = MemStackAllocAligned64_14da10(a, b);
    (*(Rec *)(rgp_blk1 + 0x0)).m04 = b;
    (*(Rec *)(rgp_blk2 + 0x0)).m00 = MemStackAllocAligned64_14da10(a, b);
    (*(Rec *)(rgp_blk2 + 0x0)).m04 = b;
    MemStackInit_14d810((*(Rec *)(rgp_blk1 + 0x0)).m08, MemStackAllocAligned64_14da10(c, e), e);
    MemStackInit_14d810((*(Rec *)(rgp_blk2 + 0x0)).m08, MemStackAllocAligned64_14da10(c, e), e);
    DrawListInitDoubleBufMaybe_1427e0(D_004810A4, &(*(Rec *)(rgp_blk1 + 0x0)), &(*(Rec *)(rgp_blk2 + 0x0)));
    return 1;
}
