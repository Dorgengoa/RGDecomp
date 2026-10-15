#include "types.h"

/* Colour lookup: writes four floats through p1 from a small palette keyed on
   the s16 at 0x1A, falling back to copying p0's own three floats.

   Retail FALLS THROUGH both guards (`bgtzl` on the s8 at 0x18, `beqz` on the
   s16 at 0x1A) into the palette block, so the source `if` body is the switch
   and the three-float copy is the `else` (levers: the fall-through is the if
   body).  The `bgtzl` carries the else-block's first `lwc1 $f0,0x0($4)` in its
   delay slot, which is why the else has two entry labels.

   jtbl_0045D020 is 10 entries and is NOT the identity permutation: entry 0
   points at the SECOND physical block and entry 1 at the FIRST, so the source
   spells `case 1:` before `case 0:` and cases 2..9 in order.  Physical block
   order IS source order.

   The four stores BEFORE the switch are the source's defaults; every arm
   rewrites all four (mwcc does not DSE repeated stores through a pointer), and
   out-of-range falls past the switch with the defaults standing -- which is
   why they cannot be spelled as a `default:` arm.  mwcc hoists the two
   constants that every arm shares (128.0f, 216.0f) into $f0/$f1 via mtc1 and
   materialises the per-arm ones with lui + sw.

   The switch operand is a SECOND `lh $3,0x1A($4)` -- read the member again,
   do not reuse a local.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  CharaTintGetColor_21f1b0  0045D020  28   # jtbl_0045D020, 10 cases */

struct Src {
    f32 m00;
    f32 m04;
    f32 m08;
    u8 pad00C[0xC];
    s8 m18;
    s8 m19;
    s16 m1A;
};

struct Rgba {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

void CharaTintGetColor_21f1b0(struct Src *p0, struct Rgba *p1)
{
    if (p0->m18 <= 0 && p0->m1A != 0) {
        p1->r = 216.0f;
        p1->g = 216.0f;
        p1->b = 128.0f;
        p1->a = 128.0f;
        switch (p0->m1A) {
        case 1:
            p1->r = 255.0f;
            p1->g = 176.0f;
            p1->b = 216.0f;
            p1->a = 128.0f;
            break;
        case 0:
            p1->r = 64.0f;
            p1->g = 64.0f;
            p1->b = 64.0f;
            p1->a = 128.0f;
            break;
        case 2:
            p1->r = 176.0f;
            p1->g = 176.0f;
            p1->b = 255.0f;
            p1->a = 128.0f;
            break;
        case 3:
            p1->r = 64.0f;
            p1->g = 64.0f;
            p1->b = 64.0f;
            p1->a = 128.0f;
            break;
        case 4:
            p1->r = 216.0f;
            p1->g = 216.0f;
            p1->b = 255.0f;
            p1->a = 128.0f;
            break;
        case 5:
            p1->r = 160.0f;
            p1->g = 255.0f;
            p1->b = 255.0f;
            p1->a = 128.0f;
            break;
        case 6:
            p1->r = 108.0f;
            p1->g = 0.0f;
            p1->b = 176.0f;
            p1->a = 128.0f;
            break;
        case 7:
            p1->r = 255.0f;
            p1->g = 160.0f;
            p1->b = 0.0f;
            p1->a = 128.0f;
            break;
        case 8:
            p1->r = 255.0f;
            p1->g = 240.0f;
            p1->b = 0.0f;
            p1->a = 128.0f;
            break;
        case 9:
            p1->r = 32.0f;
            p1->g = 24.0f;
            p1->b = 96.0f;
            p1->a = 128.0f;
            break;
        }
    } else {
        p1->r = p0->m00;
        p1->g = p0->m04;
        p1->b = p0->m08;
        p1->a = 128.0f;
    }
}
