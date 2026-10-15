#pragma divbyzerocheck on
#include "types.h"
/* insect 0x004F0220 -- 180 B / 45 words.  SIX divides, THREE breaks.
 *
 * Which divides carry the bnez/break is decided by mflo-vs-mfhi:
 *   div;mflo  (`/`)  -> break   x3   (t/10, (t/10)/100000, t/100000)
 *   div;mfhi  (`%`)  -> no break x3  (%10000, %10, %100000)
 *
 * The tail is a 16-byte block copy done through $f0/$f1/$f2, i.e. ONE struct
 * assignment `*out = q` off a 0x10-byte stack local; the 0x3F800000 arrives as
 * `lui/sw`, which is mwcc's float-constant-to-memory form. */

typedef struct F220Quad {
    s32 a;                          /* +0x00 */
    s32 b;                          /* +0x04 */
    s32 c;                          /* +0x08 */
    f32 d;                          /* +0x0C */
} F220Quad;

void insect_InsectBattleVoiceIdSplit_4f0220(F220Quad *out, s32 unused, s32 t)
{
    F220Quad q;

    q.a = t / 10 / 100000 % 10000;
    q.b = t / 100000 % 10;
    q.c = t % 100000;
    q.d = 1.0f;
    *out = q;
}
