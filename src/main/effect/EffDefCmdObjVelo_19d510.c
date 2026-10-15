/* PARK: m2c cannot decompile -- "Found jr instruction ... but the
   corresponding jump table is not provided." Needs a jump-table
   reconstruction pass this lane's budget does not cover. Not attempted. */
/* s49m: MATCH jtbl rodata_check */
#include "types.h"

extern void *MemStackNew_14e230(s32 arg0, s32 arg1);
extern void *EffAttachCtorPos_19d350(void *arg0);
extern void *EffAttachCtorRot_19d2f0(void *arg0);
extern void *EffAttachCtorScale_19d290(void *arg0);
extern void *EffAttachCtorTexUv_19d230(void *arg0);
extern void *EffAttachCtorColor_19d1d0(void *arg0);
extern void EffRandParamParseArgs_19fad0(void *arg0, s32 arg1, s32 arg2);

s32 EffDefCmdObjVelo_19d510(s32 arg0, s32 arg1, u8 **arg2)
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
        EffRandParamParseArgs_19fad0((u8 *)q + 0x10, arg0, arg1);
    }
    return 1;
}
