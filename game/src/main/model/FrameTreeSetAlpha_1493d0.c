/* rgp:protos */
#define RGP_SELF_FrameTreeSetAlpha_1493d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node001493d0 {
    u8 pad0[8];
    struct Node001493d0 *child;   /* +0x8 */
    struct Node001493d0 *sibling; /* +0xC */
    u8 pad1[0x2e - 0x10];
    s16 scale;                    /* +0x2e */
} Node001493d0;

/*rgp*/

void FrameTreeSetAlpha_1493d0(Node001493d0 *self, f32 scale)
{
    Node001493d0 *c1, *c2, *c3, *c4, *c5, *c6;

    self->scale = (s16)(16384.0f * scale);
    for (c1 = self->child; c1 != NULL; c1 = c1->sibling) {
        c1->scale = (s16)(16384.0f * scale);
        for (c2 = c1->child; c2 != NULL; c2 = c2->sibling) {
            c2->scale = (s16)(16384.0f * scale);
            for (c3 = c2->child; c3 != NULL; c3 = c3->sibling) {
                c3->scale = (s16)(16384.0f * scale);
                for (c4 = c3->child; c4 != NULL; c4 = c4->sibling) {
                    c4->scale = (s16)(16384.0f * scale);
                    for (c5 = c4->child; c5 != NULL; c5 = c5->sibling) {
                        FrameSetAlpha_149510(c5, scale);
                        for (c6 = c5->child; c6 != NULL; c6 = c6->sibling) {
                            FrameTreeSetAlpha_1493d0(c6, scale);
                        }
                    }
                }
            }
        }
    }
}
