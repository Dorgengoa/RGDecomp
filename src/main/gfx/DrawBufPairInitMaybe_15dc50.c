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
extern void MemStackCtor_14e030(void *buf);
extern void *MemStackAllocAligned64_14da10(void *a, void *b);
extern void MemStackInit_14d810(void *buf, void *r, void *e);
extern void DrawListInitDoubleBufMaybe_1427e0(void *ctx, Rec *a, Rec *b);

s32 DrawBufPairInitMaybe_15dc50(void *a, void *b, void *c, void *unused, void *e)
{
    Rec t1;
    Rec t2;

    MemStackCtor_14e030(t1.m08);
    MemStackCtor_14e030(t2.m08);
    t1.m00 = MemStackAllocAligned64_14da10(a, b);
    t1.m04 = b;
    t2.m00 = MemStackAllocAligned64_14da10(a, b);
    t2.m04 = b;
    MemStackInit_14d810(t1.m08, MemStackAllocAligned64_14da10(c, e), e);
    MemStackInit_14d810(t2.m08, MemStackAllocAligned64_14da10(c, e), e);
    DrawListInitDoubleBufMaybe_1427e0(D_004810A4, &t1, &t2);
    return 1;
}
