#include "types.h"

typedef struct Page {
    u8    pad00[0x80];
    void *f80;
} Page;

extern void func_28F9D0(void *h, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);

void factory_FactoryBlueprintSetCategoryIcon_4f8e90(Page *o, s32 id, s32 n)
{
    switch (id) {
    case 0x44F:
        func_28F9D0(o->f80, 0x3B, 0x4E, 0x2E, 0x16, 0x16, n);
        break;
    case 0x44D:
        func_28F9D0(o->f80, 0x3B, 0x7A, 0x2E, 0x16, 0x16, n);
        break;
    case 0x44E:
        func_28F9D0(o->f80, 0x3B, 0x64, 0x2E, 0x16, 0x16, n);
        break;
    case 0x450:
        func_28F9D0(o->f80, 0x3B, 0x38, 0x2E, 0x16, 0x16, n);
        break;
    case 0x44C:
        func_28F9D0(o->f80, 0x3B, 0x90, 0x2E, 0x16, 0x16, n);
        break;
    }
}
