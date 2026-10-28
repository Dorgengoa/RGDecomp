/* rgp:protos */
#define RGP_SELF_TaskDrawGlare_2f6b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN TaskDrawGlare_2f6b20.  The four constant members of the 0x18-byte
   record are written TWICE -- once before the two NameTableFindByName_159fb0 calls
   and once after -- and retail keeps both blocks, so the duplication
   is in the source, not a scheduling artefact. */

typedef struct Rec6b20 {
    s32 m00;
    s32 m04;
    s32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
} Rec6b20;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00461D28[];
extern u8 D_00461D38[];

void TaskDrawGlare_2f6b20(void)
{
    Rec6b20 r __attribute__((aligned(16)));
    void *v;
    void *w;

    v = GetDrawCtx_15de80();
    w = GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(v, 0x323, 1.0f);
    r.m08 = 0x80;
    r.m0C = 0.1796875f;
    r.m14 = 1.0f;
    r.m10 = 1.0f;
    r.m00 = ((s32)NameTableFindByName_159fb0(w, D_00461D28, -1));
    r.m04 = ((s32)NameTableFindByName_159fb0(w, D_00461D38, -1));
    r.m08 = 0x80;
    r.m0C = 0.1796875f;
    r.m14 = 1.0f;
    r.m10 = 1.0f;
    GlareFilterDrawMaybe_17a0d0(&r);
}
