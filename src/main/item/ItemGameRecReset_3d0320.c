#include "types.h"

extern void Clear128Bytes_3d2720(void *arg0);
extern void InsectBreedRecReset_3d2730(void *arg0);
extern void ItemReset_3d50d0(void);
typedef struct { u8 pad[0x18]; u8 *p; } A;

void ItemGameRecReset_3d0320(A *arg0)
{
    s32 i;

    ItemReset_3d50d0();
    if (arg0->p != NULL) {
        for (i = 0; i < 5; i++) {
            *(s16 *)(arg0->p + i * 2 + 2) = -1;
            *(s32 *)(arg0->p + i * 4 + 0xC) = 0;
        }
        *(s16 *)(arg0->p + 0x20) = 0;
        *(s16 *)(arg0->p + 0x22) = 0;
        for (i = 0; i < 2; i++) {
            InsectBreedRecReset_3d2730(arg0->p + i * 0x14 + 0x24);
        }
        for (i = 0; i < 0x10; i++) {
            Clear128Bytes_3d2720(arg0->p + (i << 7) + 0x4C);
        }
    }
}
