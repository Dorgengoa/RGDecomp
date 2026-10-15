/* PARKED at triage (0 round trips): very large (0x1150+ byte) stack frame
 * with many unresolved "?" locals (sp1100, sp10C0, sp880, sp40) passed by
 * address into CfgVmRegisterCmds_42fb00/CfgVmLoad_42fac0/CfgVmRun_42fa20 -- sizes unknown, high
 * risk of getting the stack layout wrong without a raw-asm trace. Deferred
 * to preserve lane throughput. See asm/matchings/main/MapAreaRunDataScripts_1ead90.s. */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    f32 r, g, b, a;
} Color;

typedef struct {
    u8 data[0x828];
    u8 flag;
    u8 pad829[7];
} Tex;

typedef struct {
    u8 pad0[2];
    s16 count;
    s32 file;
    s32 size;
} Entry;

extern u8 *D_004818FC;
extern f32 D_0047E420;
extern f32 D_0047E424;
extern f32 D_0047E428;
extern f32 D_0047E42C;
extern f32 D_0047E430;
extern f32 D_0047E434;
extern f32 D_0047E438;
extern f32 D_0047E43C;
extern char D_0045B668[];
extern char D_0045B678[];
extern void LoadHandlePollThunk_1ccb00(u8 *);
extern Entry *MapAreaLoadHandleAt_1dd120(u8 *, s32);
extern s32 MapDataGetFileName_1e7be0(u8 *);
extern s32 Sprintf_1343b8(char *, char *, s32);
extern s32 ArchiveGetFileByPath_1c2800(s32, char *, s32 *);
extern void MapDataSetHeapSize_1e7470(u8 *, s32);
extern void CfgVmReset_42fc10(Tex *);
extern void CfgVmRegisterCmds_42fb00(Tex *, Color *);
extern void CfgVmLoad_42fac0(Tex *, s32, s32);
extern void CfgVmRun_42fa20(Tex *);

s32 MapAreaRunDataScripts_1ead90(u8 *o)
{
    s32 sz1;
    s32 sz2;
    char name1[0x40];
    char name2[0x40];
    Color c1;
    Tex t1;
    Color c2;
    Tex t2;
    Entry *e;
    s32 d1;
    s32 d2;

    D_004818FC = 0;
    LoadHandlePollThunk_1ccb00(o + 0xA8);
    e = MapAreaLoadHandleAt_1dd120(o + 0xA8, 0);
    if (e == 0) {
        return -1;
    }
    if (e->count == 0) {
        return 0;
    }
    if (e->file == 0 || e->size <= 0) {
        *(u32 *)(o + 0x2C) |= 0x400;
        return 2;
    }
    Sprintf_1343b8(name1, D_0045B668, MapDataGetFileName_1e7be0(o));
    Sprintf_1343b8(name2, D_0045B678, MapDataGetFileName_1e7be0(o));
    d1 = ArchiveGetFileByPath_1c2800(e->file, name1, &sz1);
    d2 = ArchiveGetFileByPath_1c2800(e->file, name2, &sz2);
    MapDataSetHeapSize_1e7470(o, 0);
    D_004818FC = o;
    c1.r = D_0047E420;
    c1.g = D_0047E424;
    c1.b = D_0047E428;
    c1.a = D_0047E42C;
    CfgVmReset_42fc10(&t1);
    t1.flag = 1;
    CfgVmRegisterCmds_42fb00(&t1, &c1);
    CfgVmLoad_42fac0(&t1, d1, sz1);
    CfgVmRun_42fa20(&t1);
    if (d2 != 0) {
        if (sz2 > 0) {
            c2.r = D_0047E430;
            c2.g = D_0047E434;
            c2.b = D_0047E438;
            c2.a = D_0047E43C;
            CfgVmReset_42fc10(&t2);
            t2.flag = 1;
            CfgVmRegisterCmds_42fb00(&t2, &c2);
            CfgVmLoad_42fac0(&t2, d2, sz2);
            CfgVmRun_42fa20(&t2);
        }
    }
    D_004818FC = 0;
    return 2;
}
