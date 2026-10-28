/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuHideHeader_4f1220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8    pad00[0x64];
    void *f64;
} A;

/*rgp*/

void factory_FactoryMenuHideHeader_4f1220(A *o)
{
    UiSetWidgetVisible_290010(o->f64, 1, 0, -1);
}
