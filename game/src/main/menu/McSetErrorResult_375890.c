/* rgp:protos */
#define RGP_SELF_McSetErrorResult_375890 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: m2c aborts outright ("Found jr instruction ... jump table not
 * provided") -- a switch statement whose jump table was not supplied to the
 * decompiler in this session. 0 round trips spent; needs the jump table
 * looked up (jtbl_* label near this address in asm/matchings/main) and fed
 * to `python scripts/rgd.py decomp McSetErrorResult_375890 --switch <addr> jtbl_XXXX`
 * or hand-reconstructed from the listing. Not attempted further this
 * session -- no skeleton written since the control flow shape is unknown
 * without the table. */
/* s49m: MATCH (jtbl, rodata_check) */
#include "types.h"

typedef struct Ent {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 padC[0x10];
} Ent;

typedef struct Obj {
    u8 pad0[0x4A4];
    Ent ents[2];
    s32 unk4DC;
    s32 unk4E0;
    u8 pad4E4[8];
    s16 idx;
    s16 unk4EE;
} Obj;

/*rgp*/

s32 McSetErrorResult_375890(Obj *o, s32 a)
{
    s16 *out;
    Ent *e;

    out = ((s16 *)SaveMgrGetResult_375a00(o));
    e = &o->ents[o->idx];
    switch (a) {
    case -8:
    case -7:
    case -6:
    case -5:
    case -4:
    case -1:
        break;
    case -2:
        out[0] = 7;
        e->unk8 = 0;
        break;
    case -3:
        out[0] = 4;
        break;
    }
    if (a == -1 || (a >= -19 && a <= -11) || (a >= -49 && a <= -40)
        || (a >= -59 && a <= -50) || (a >= -79 && a <= -70)) {
        out[0] = 8;
        e->unk0 = 0;
        if (o->unk4DC == 4) {
            out[0] = 6;
        }
    }
    if (a < 0) {
        out[1] = o->unk4DC;
        out[3] = o->unk4E0;
        out[2] = o->unk4EE;
    }
    return 1;
}
