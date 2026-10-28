/* rg-override: replaces game/src/main/camera/AabbInFrustum_13be60.c sha256 03e4450d1ee19c81d9341e17e1186d91688d8b37930f4d3aa7b5da0f140a06e8
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* Both helpers pass their state through VU0 registers (vf7, vf10-12). */
extern void AabbLoadToVu_13bfc0(const void *box, const void *m);
extern void AabbPlaneDistances_13bf50(void *ext, void *dist, const void *planes);

/* 1 when the box (loaded by AabbLoadToVu from a, b) is not fully outside any
   of the four planes in c nor the first two planes in d.  The listing
   returns $2; the one caller declares it void. */
s32 AabbInFrustum_13be60(const void *a, const void *b, const void *c, const void *d)
{
    f32 ext[4];                                         /* sp+0x40 */
    f32 dist[4];                                        /* sp+0x30 */

    AabbLoadToVu_13bfc0(a, b);                          /* jal AabbLoadToVu ($4, $5 passed through) */
    AabbPlaneDistances_13bf50(ext, dist, c);            /* $4 = sp+0x40, $5 = sp+0x30, $6 = c */
    if (dist[0] <= -ext[0])                             /* c.le.s; bc1tl (slot $2 = 0) */
        return 0;
    if (dist[1] <= -ext[1])
        return 0;
    if (dist[2] <= -ext[2])
        return 0;
    if (dist[3] <= -ext[3])                             /* bc1fl (slot $6 = d) */
        return 0;
    AabbPlaneDistances_13bf50(ext, dist, d);
    if (dist[0] <= -ext[0])
        return 0;
    if (!(dist[1] <= -ext[1]))                          /* bc1fl (slot $2 = 1) */
        return 1;
    return 0;
}
