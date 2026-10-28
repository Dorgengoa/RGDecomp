/* rgp:protos */
#define RGP_SELF_EffDefCmdObjAccele_19d3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EffDefCmdObjAccele_19d3b0(s32 arg0, s32 arg1, u8 **arg2)
{
    u8 *obj;
    void *p;
    void *q;

    obj = *arg2;
    q = *(void **)(obj + 0x48);
    switch ((s32)q) {
    case 0:
        switch (*(u32 *)(obj + 0x40)) {
        case 0:
        case 4:
        case 5:
            break;
        case 1:
            p = MemStackNew_14e230(0x80, *(s32 *)(obj + 0x20));
            if (p != 0) {
                p = EffAttachCtorPos_19d350(p);
            }
            *(void **)(obj + 0x48) = p;
            break;
        case 2:
            p = MemStackNew_14e230(0x80, *(s32 *)(obj + 0x20));
            if (p != 0) {
                p = EffAttachCtorRot_19d2f0(p);
            }
            *(void **)(obj + 0x48) = p;
            break;
        case 3:
            p = MemStackNew_14e230(0x80, *(s32 *)(obj + 0x20));
            if (p != 0) {
                p = EffAttachCtorScale_19d290(p);
            }
            *(void **)(obj + 0x48) = p;
            break;
        case 6:
            p = MemStackNew_14e230(0x80, *(s32 *)(obj + 0x20));
            if (p != 0) {
                p = EffAttachCtorTexUv_19d230(p);
            }
            *(void **)(obj + 0x48) = p;
            break;
        case 7:
            p = MemStackNew_14e230(0x80, *(s32 *)(obj + 0x20));
            if (p != 0) {
                p = EffAttachCtorColor_19d1d0(p);
            }
            *(void **)(obj + 0x48) = p;
            break;
        }
        q = *(void **)(obj + 0x48);
        break;
    }
    if (q != 0) {
        EffRandParamParseArgs_19fad0((u8 *)q + 0x40, arg0, arg1);
    }
    return 1;
}
