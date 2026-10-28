/* rgp:protos */
#define RGP_SELF_EntryScriptCmdSetScale_322eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EntryScriptCmdSetScale_322eb0(void *p)
{
    void *a;
    void *b;
    f32 f;

    a = GetEntryTableGlobal_32c2e0();
    if (a == 0) return 0;
    b = EntryTableGetCurrent_323530(a);
    if (b == 0) return 0;
    f = VariantGetFloat_15f740(p);
    EntrySetScale_323c10(b, f);
    return 1;
}
