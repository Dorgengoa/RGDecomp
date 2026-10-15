#include "types.h"
typedef unsigned __int128 u128;
extern s32 TexEnvBuildDmaChainMaybe_14abb0(void *arg0, void *arg1);
extern void GsFrameSet_156e10(s32 arg0, s32 arg1);
extern void GsZbufCopyBaseFmt_156ea0(s32 arg0, s32 arg1);
extern s32 GsEnvWritePacket_157190(s32 arg0, void *arg1);
extern s32 DrawEnvGetZbufRegPtr_157760(s32 arg0);

s32 DrawListWriteTexEnvPacket_148370(void *arg0, u128 *arg1, void *arg2)
{
    s32 obj;
    s32 t;
    u128 *end;
    s32 n;

    obj = *(s32 *)((u8 *)arg2 + 0x14);
    if (obj == 0) {
        return 0;
    }
    t = *(s32 *)((u8 *)arg0 + 0x270);
    GsZbufCopyBaseFmt_156ea0(obj, DrawEnvGetZbufRegPtr_157760(t));
    GsFrameSet_156e10(obj, t + 0x80);
    *arg1 = 0;
    ((s32 *)arg1)[0] = 0x10000006;
    ((s32 *)arg1)[3] = 0x50000006;
    end = arg1 + 1;
    end = end + GsEnvWritePacket_157190(obj, end);
    n = end - arg1;
    n += TexEnvBuildDmaChainMaybe_14abb0(arg2, end);
    return n;
}
