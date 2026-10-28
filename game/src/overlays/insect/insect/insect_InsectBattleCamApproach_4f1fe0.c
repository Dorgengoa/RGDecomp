/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCamApproach_4f1fe0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"
/* insect 0x004F1FE0 -- 276 bytes, 69 instructions, no calls.
 * A three-element clamp/accumulate loop over a 6x4 float matrix. */

void insect_InsectBattleCamApproach_4f1fe0(f32 *m)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        m[i] = m[i] + m[i + 16];
        if (m[i + 16] > 0.0f) {
            if (m[i] >= m[i + 8]) {
                m[i] = m[i + 8];
                m[i + 16] = 0.0f;
            }
        }
        if (m[i + 16] < 0.0f) {
            if (m[i] <= m[i + 8]) {
                m[i] = m[i + 8];
                m[i + 16] = 0.0f;
            }
        }
        m[i + 4] = m[i + 4] + m[i + 20];
        if (m[i + 20] > 0.0f) {
            if (m[i + 4] >= m[i + 12]) {
                m[i + 4] = m[i + 12];
                m[i + 20] = 0.0f;
            }
        }
        if (m[i + 20] < 0.0f) {
            if (m[i + 4] <= m[i + 12]) {
                m[i + 4] = m[i + 12];
                m[i + 20] = 0.0f;
            }
        }
    }
}
