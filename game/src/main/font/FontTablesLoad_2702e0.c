/* rgp:protos */
#define RGP_SELF_FontTablesLoad_2702e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F5C0[];
extern u8 D_0045F5E0[];
extern u8 D_0045F600[];
extern u8 D_0045F620[];
extern u8 D_004820B8;

s32 FontTablesLoad_2702e0(s32 p0, s32 p1)
{
    s32 v2C;
    s32 v28;
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 t1;
    s32 r3;
    s32 r4;
    s32 t2;
    s32 r5;
    s32 r6;
    s32 t3;
    s32 r7;
    s32 r8;
    s32 t4;
    s32 r9;
    s32 r10;
    s32 t5;
    s32 r11;

    D_004820B8 = p0;
    if (p0 == 0) {
        v2C = 0;
        r0 = ((s32)ArchiveGetFileByPath_1c2800(p1, D_0045F5C0, &v2C));
        t0 = v2C;
        r1 = FontLoadGlyphTable_270270(1, r0, t0);
        r2 = ((s32)ArchiveGetFileByPath_1c2800(p1, D_0045F5E0, &v2C));
        t1 = v2C;
        r3 = FontLoadGlyphTable_270270(0, r2, t1);
        r4 = ((s32)ArchiveGetFileByPath_1c2800(p1, D_0045F600, &v2C));
        t2 = v2C;
        r5 = FontLoadGlyphTable_270270(2, r4, t2);
        return r5;
    }
    v28 = 0;
    r6 = ((s32)ArchiveGetFileByPath_1c2800(p1, D_0045F620, &v28));
    t3 = v28;
    r7 = FontLoadGlyphTable_270270(1, r6, t3);
    r8 = ((s32)ArchiveGetFileByPath_1c2800(p1, D_0045F5E0, &v28));
    t4 = v28;
    r9 = FontLoadGlyphTable_270270(0, r8, t4);
    r10 = ((s32)ArchiveGetFileByPath_1c2800(p1, D_0045F600, &v28));
    t5 = v28;
    r11 = FontLoadGlyphTable_270270(2, r10, t5);
    return r11;
}
