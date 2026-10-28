/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_GsDbufPutEnv_144150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Dispfb {
    __extension__ unsigned int FBP:9;
    unsigned int FBW:6;
    unsigned int PSM:5;
    unsigned int p0:12;
    unsigned int  : 0, DBX:11;
    unsigned int DBY:11;
    unsigned int p1:10;
} __attribute__((aligned(4))) Dispfb;

typedef struct Display {
    __extension__ unsigned int DX:12;
    unsigned int DY:11;
    unsigned int MAGH:4;
    unsigned int MAGV:2;
    unsigned int p0:3;
    unsigned int  : 0, DW:12;
    unsigned int DH:11;
    unsigned int p1:9;
} __attribute__((aligned(4))) Display;

typedef struct DispEnv {
    u64 pmode;
    u64 smode2;
    Dispfb dispfb;
    Display display;
    u64 bgcolor;
} DispEnv;

typedef struct Env40 {
    u32 w[10];
} Env40;

typedef struct Db {
    u8 pad0[0x1C];
    s32 interlace;      /* 0x1C */
    u8 pad20[0x24];
    Env40 env;          /* 0x44 */
    u8 pad6C[4];
    u8 draw[1];         /* 0x70 */
} Db;

typedef struct Obj {
    u8 pad0[0x270];
    Db *db;             /* 0x270 */
    u8 pad274[0xF08 - 0x274];
    u16 ox;             /* 0xF08 */
    u8 padF0A[2];
    s32 oy;             /* 0xF0C */
} Obj;

extern s32 sceDmaGetChan(s32);
extern void FlushCache(s32);
extern void sceGsSyncV(s32);
extern void sceGsPutDispEnv(DispEnv *);
extern void sceGsPutDrawEnv(void *);
/*rgp*/

#define GS_PMODE    (((u64)rg_gs_reg_r64(RG_GS_PMODE)))
#define GS_DISPFB1  (((u64)rg_gs_reg_r64(RG_GS_DISPFB1)))
#define GS_DISPLAY1 (((u64)rg_gs_reg_r64(RG_GS_DISPLAY1)))

void GsDbufPutEnv_144150(Obj *o)
{
    Db *db;
    s32 ch;
    DispEnv env __attribute__((aligned(16)));
    Display d __attribute__((aligned(16)));

    ch = sceDmaGetChan(2);
    db = o->db;
    *(Env40 *)&env = db->env;
    env.display.DX += (u32)o->ox;
    env.display.DY += o->oy;
    FlushCache(0);
    sceGsSyncV(0);
    sceGsPutDispEnv(&env);
    sceGsPutDrawEnv(db->draw);
    sceDmaSync_10a2e0(ch, 0);
    if (db->interlace != 0) {
    rg_gs_reg_w64(RG_GS_PMODE, 0x7F23);
    rg_gs_reg_w64(RG_GS_DISPFB1, (u64)env.dispfb.FBP | ((u64)env.dispfb.FBW << 9) | ((u64)env.dispfb.PSM << 15) | ((u64)0x800 << 32));
    d.DX = env.display.DX;
    d.DY = env.display.DY;
    d.MAGH = env.display.MAGH;
    d.MAGV = env.display.MAGV;
    d.p0 = env.display.p0;
    d.DW = env.display.DW;
    d.DH = env.display.DH - 1;
    d.p1 = env.display.p1;
    rg_gs_reg_w64(RG_GS_DISPLAY1, *(u64 *)&d);
    } else {
        rg_gs_reg_w64(RG_GS_PMODE, 0xFF22);
    }
}
