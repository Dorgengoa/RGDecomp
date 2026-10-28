/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintSetCategoryIcon_4f8e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Page {
    u8    pad00[0x80];
    void *f80;
} Page;

/*rgp*/

void factory_FactoryBlueprintSetCategoryIcon_4f8e90(Page *o, s32 id, s32 n)
{
    switch (id) {
    case 0x44F:
        UiSetSpriteUvRect_28f9d0(o->f80, 0x3B, 0x4E, 0x2E, 0x16, 0x16, n);
        break;
    case 0x44D:
        UiSetSpriteUvRect_28f9d0(o->f80, 0x3B, 0x7A, 0x2E, 0x16, 0x16, n);
        break;
    case 0x44E:
        UiSetSpriteUvRect_28f9d0(o->f80, 0x3B, 0x64, 0x2E, 0x16, 0x16, n);
        break;
    case 0x450:
        UiSetSpriteUvRect_28f9d0(o->f80, 0x3B, 0x38, 0x2E, 0x16, 0x16, n);
        break;
    case 0x44C:
        UiSetSpriteUvRect_28f9d0(o->f80, 0x3B, 0x90, 0x2E, 0x16, 0x16, n);
        break;
    }
}
