/* rgp:protos */
#define RGP_SELF_EvCmdCharaTrailSetTextureMaybe_2594d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
extern s32 D_0047E964;
extern char D_004BE590[];

struct Obj0 {
    u8 m00[8];
    u8 m08[8];
};

struct Rec {
    u8 pad000[0x4DC];
    s32 m4DC;
};

s32 EvCmdCharaTrailSetTextureMaybe_2594d0(struct Obj0 *p0, s32 p1)
{
    void *h;
    struct Rec *rec;

    if (p1 < 2) {
        return 0;
    }
    D_0047E964 = -1;
    D_004BE590[0] = 0;
    h = GetCurrentScene_1f5be0();
    rec = ObjRecGetLiveObject_1c4a90(h, ScriptGetInt_26a2a0(p0->m00));
    if (rec == 0) {
        return 1;
    }
    D_0047E964 = rec->m4DC;
    strcpy(D_004BE590, ((const char *)ScriptGetCodeAddr_26a200(p0->m08)));
    return 1;
}
