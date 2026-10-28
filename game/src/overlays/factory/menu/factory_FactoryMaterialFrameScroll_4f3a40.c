/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialFrameScroll_4f3a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8 pad00[0x50];
    u8 f50[0x28];
    u8 f78;
} A;

/*rgp*/

void factory_FactoryMaterialFrameScroll_4f3a40(A *o)
{
    if (o->f78 != 2) {
        UiSelFrameAnimStep_28d820(&o->f50, 0x63);
    }
}
