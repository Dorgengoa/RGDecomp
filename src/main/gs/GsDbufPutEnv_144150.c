#include "types.h"

typedef struct Dispfb {
    u32 FBP:9;
    u32 FBW:6;
    u32 PSM:5;
    u32 p0:12;
    u32 DBX:11;
    u32 DBY:11;
    u32 p1:10;
} Dispfb;

typedef struct Display {
    u32 DX:12;
    u32 DY:11;
    u32 MAGH:4;
    u32 MAGV:2;
    u32 p0:3;
    u32 DW:12;
    u32 DH:11;
    u32 p1:9;
} Display;

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
extern void sceDmaSync_10a2e0(s32, s32, s32);

#define GS_PMODE    (*(volatile u64 *)0x12000000)
#define GS_DISPFB1  (*(volatile u64 *)0x12000070)
#define GS_DISPLAY1 (*(volatile u64 *)0x12000080)

void GsDbufPutEnv_144150(Obj *o)
{
    Db *db;
    s32 ch;
    DispEnv env;
    Display d;

    ch = sceDmaGetChan(2);
    db = o->db;
    *(Env40 *)&env = db->env;
    env.display.DX += (u32)o->ox;
    env.display.DY += o->oy;
    FlushCache(0);
    sceGsSyncV(0);
    sceGsPutDispEnv(&env);
    sceGsPutDrawEnv(db->draw);
    sceDmaSync_10a2e0(ch, 0, 0);
    if (db->interlace != 0) {
    GS_PMODE = 0x7F23;
    GS_DISPFB1 = (u64)env.dispfb.FBP | ((u64)env.dispfb.FBW << 9) | ((u64)env.dispfb.PSM << 15) | ((u64)0x800 << 32);
    d.DX = env.display.DX;
    d.DY = env.display.DY;
    d.MAGH = env.display.MAGH;
    d.MAGV = env.display.MAGV;
    d.p0 = env.display.p0;
    d.DW = env.display.DW;
    d.DH = env.display.DH - 1;
    d.p1 = env.display.p1;
    GS_DISPLAY1 = *(u64 *)&d;
    } else {
        GS_PMODE = 0xFF22;
    }
}
