/* rgp:protos */
#define RGP_SELF_EvCmdEvSceneObjReloadCfg_268dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x1];
} Buf00268DC0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdEvSceneObjReloadCfg_268dc0(s64 *arg0, s32 arg1) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0xc + sizeof(Buf00268DC0)]; char m1[0x10]; })];
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    s32 r;

    if (arg1 == 4) {
        v1 = ScriptGetInt_26a2a0((s32)arg0++);
        v2 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v3 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v4 = ScriptGetInt_26a2a0((s32)arg0);
        r = FileLoadCached_26a6c0(v2, 0);
        if (r != 0) {
            return EvSceneObjReloadCfg_268f10(v1, v3, v4, r);
        }
        return 0;
    } else if (arg1 == 5) {
        v0 = ScriptGetInt_26a2a0((s32)arg0++);
        v1 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v2 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v3 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v4 = ScriptGetInt_26a2a0((s32)arg0);
        r = FileLoadCached_26a6c0(v1, 0);
        if (r == 0) {
            return 0;
        }
        r = ((s32)ArchiveGetFileByPath_1c2800(r, v2, &(*(Buf00268DC0 *)(rgp_blk1 + 0xc))));
        if (r != 0) {
            return EvSceneObjReloadCfg_268f10(v0, v3, v4, r);
        }
        return 0;
    }
    return 1;
}
