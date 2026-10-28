/* rgp:protos */
#define RGP_SELF_MinimapScriptCmdAddPos_32ad30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MinimapScriptCmdAddPos_32ad30(Cur8 *q)
{
    void *p;
    void *t;
    void *r;
    char *s;
    f32 a;
    f32 b;
    f32 c;
    u8 buf[16] __attribute__((aligned(16)));

    p = GetMinimapSubGlobal_32c2c0();
    t = GetEntryTableGlobal_32c2e0();
    if (p != 0) {
        if (t != 0) {
            s = ((char *)SlotGetInt_15f720(q++));
            a = VariantGetFloat_15f740(q++);
            b = VariantGetFloat_15f740(q++);
            c = VariantGetFloat_15f740(q);
            r = EntryListFindByNameInRange_323420(t, s, b, 0.0f);
            Vec3Set_32b0b0(buf, a, b, c);
            EntryPosRecSetEntry_32b0a0(buf, r);
            MinimapSubAppendPos_32aeb0(p, buf);
        }
    }
    return 1;
}
