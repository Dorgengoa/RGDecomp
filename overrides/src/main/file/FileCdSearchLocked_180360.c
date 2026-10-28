/* rg-override: replaces game/src/main/file/FileCdSearchLocked_180360.c sha256 d8af2d69dd78f41d3614497dc5cbdb129a9172ca13ee08b6320db898eacf6df5
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): "is this file there" by name through
 *      the host file service instead of sceCd(Layer)SearchFile.  Fills the caller's
 *      36-byte sceCdlFILE-shaped record with lsn 0 (no sectors) and the size; only
 *      OverlayLocateFiles_1c3300 calls it, for OverlayCdSeek's (now empty) seek. */
/* rgp:protos */
#define RGP_SELF_FileCdSearchLocked_180360 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_fs.h"

extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_004811C4;

s32 FileCdSearchLocked_180360(void *arg0, s8 *arg1)
{
    s32 var_2;
    s32 h;
    if (D_0047E028 >= 0) {
        WaitSema(D_0047E028);
    }
    D_004811C4 += 1;
    h = rg_fs_open((const char *)arg1);
    var_2 = 0;
    if (h >= 0) {
        s32 *fp = (s32 *)arg0;
        fp[0] = 0;                     /* lsn: none */
        fp[1] = (s32)rg_fs_size(h);    /* size */
        var_2 = 1;
    }
    if (D_0047E028 >= 0) {
        SignalSema(D_0047E028);
    }
    D_004811C4 -= 1;
    return var_2;
}
