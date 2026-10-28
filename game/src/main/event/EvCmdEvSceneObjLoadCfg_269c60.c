/* rgp:protos */
#define RGP_SELF_EvCmdEvSceneObjLoadCfg_269c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdEvSceneObjLoadCfg_269c60(s64 *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 k;
    s32 n;
    s32 r;

    if (arg1 == 4) {
        s32 buf[0x80] __attribute__((aligned(16)));

        a = ScriptGetInt_26a2a0((s32)arg0++);
        b = ScriptGetCodeAddr_26a200((s32)arg0++);
        buf[0] = ScriptGetCodeAddr_26a200((s32)arg0++);
        d = ScriptGetInt_26a2a0((s32)arg0++);
        k = FileLoadCached_26a6c0(b, 0);
        return k ? EvSceneObjLoadFromCfg_269da0(a, buf, d, k) : 0;
    }
    if (arg1 == 5) {
        s32 buf2[0x80] __attribute__((aligned(16)));
        s32 x;
        s32 y;
        s32 z;

        x = ScriptGetInt_26a2a0((s32)arg0++);
        y = ScriptGetCodeAddr_26a200((s32)arg0++);
        z = ScriptGetCodeAddr_26a200((s32)arg0++);
        buf2[0] = ScriptGetCodeAddr_26a200((s32)arg0++);
        d = ScriptGetInt_26a2a0((s32)arg0++);
        k = FileLoadCached_26a6c0(y, 0);
        if (k == 0) {
            return 0;
        }
        k = ((s32)ArchiveGetFileByPath_1c2800(k, z, &n));
        return k ? EvSceneObjLoadFromCfg_269da0(x, buf2, d, k) : 0;
    }
    return 1;
}
