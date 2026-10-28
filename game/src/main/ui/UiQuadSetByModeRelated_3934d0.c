/* rgp:protos */
#define RGP_SELF_UiQuadSetByModeRelated_3934d0 1
#define RGP_SELF_boxEnd 1
#define RGP_SELF_boxSet 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Six-case switch on a real jump table (jtbl_00464260 -- the table is the
   identity permutation, so the physical block order IS the source order).
   Every arm writes the SAME twelve-store row through the pointer at +0x20,
   with different immediates, so the row is a static inline; case 5 has a
   conditional re-write of +0x08/+0x0A in the middle of the row, which is why
   the row is split into the box part and the tail part.

   The +0x18/+0x1A pair is `(s16)` of a named f32 that holds 0.0f: mwcc
   materialises 0.0f with `mtc1 $0` and still does the conversion at run time
   (`cvt.w.s` / `mfc1`), CSE'd across the two stores.

   MEASURED, build 1 -> build 2: mwcc does NOT schedule these stores past one
   another.  An ascending source order emitted ascending, so retail's EMISSION
   order IS its source order and the whole residue (80 of 137 words) was read
   straight off the listing.  That is also why case 0 cannot be a boxSet() call
   with zero arguments: its row is a genuinely DIFFERENT order
   (00 02 08 0C 04 0A 0E 06) from the other five (02 00 04 06 0C 0E 08 0A).

   SHIPPING THIS UNIT NEEDS A .rodata SLOT (see memory levers.d/main-rodata-slot):
       config/crodata.txt:  UiQuadSetByModeRelated_3934d0  00464260  18   # jtbl_00464260, 6 cases
   scripts/sandbox_build.py cannot place the section, so it reports 2 bad words
   -- the `lui %hi` / `addiu %lo` of the table -- and nothing else.
   build/wf18_rodata_check.py places it and scores 0 bad / 137. */

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
    s16 unk0E;
    s32 unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
} Box;

typedef struct {
    u8 pad00[0x20];
    Box *unk20;
} Widget;

static inline void boxSet(Box *b, s16 x, s16 y, s16 u, s16 v, s16 w, s16 h)
{
    b->unk02 = 0;
    b->unk00 = 0;
    b->unk04 = x;
    b->unk06 = y;
    b->unk0C = w;
    b->unk0E = h;
    b->unk08 = u;
    b->unk0A = v;
}

static inline void boxEnd(Box *b)
{
    f32 z = 0.0f;

    b->unk14 = 0;
    b->unk10 = 0;
    b->unk1A = (s16)z;
    b->unk18 = (s16)z;
}

void UiQuadSetByModeRelated_3934d0(void *ctx, Widget *w, s16 x, s16 y, u32 mode, s32 flag)
{
    Box *b;

    if (w != NULL) {
        b = w->unk20;
        if (b != NULL) {
            switch (mode) {
            case 0:
                b->unk00 = 0;
                b->unk02 = 0;
                b->unk08 = 0;
                b->unk0C = 0;
                b->unk04 = 0;
                b->unk0A = 0;
                b->unk0E = 0;
                b->unk06 = 0;
                boxEnd(b);
                break;
            case 1:
                boxSet(b, x, y, 0x34, 0x8C, 4, 4);
                boxEnd(b);
                break;
            case 2:
                boxSet(b, x, y, 0xFC, 0x24, 2, 0x18);
                boxEnd(b);
                break;
            case 3:
                boxSet(b, x, y, 0xF8, 0x24, 2, 0x18);
                boxEnd(b);
                break;
            case 4:
                boxSet(b, x, y, 0xF4, 0x24, 2, 0x18);
                boxEnd(b);
                break;
            case 5:
                boxSet(b, x, y, 2, 0xE4, 0x56, 0x1A);
                if (flag != 0) {
                    b->unk08 = 0x4E;
                    b->unk0A = 0xC8;
                }
                boxEnd(b);
                break;
            }
        }
    }
}
