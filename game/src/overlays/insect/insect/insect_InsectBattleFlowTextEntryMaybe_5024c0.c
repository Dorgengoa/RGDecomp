/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowTextEntryMaybe_5024c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005024C0 -- 1,064 bytes, 266 instructions, 41 calls, 11 conditional
 * branches.  The mini-game's outer state machine.
 *
 * THE JUMP TABLE'S BLOCK ORDER IS THE SOURCE'S CASE ORDER, AND HERE IT IS NOT
 * ASCENDING.  insect_jtbl_00524E00 has eleven entries; indices 0 and 2 both point at
 * the shared exit 0x005028BC, so cases 0 and 2 are present with empty bodies
 * (see [[insect-jump-table-density]]).  The nine remaining blocks are laid out
 * 1, 3, 4, 5, 7, 8, 6, 9, 10 -- case 6 sits between 8 and 9 -- and that is
 * forced, because case 4 FALLS THROUGH into 5 and case 7 falls through into 8.
 * Read the order off the addresses, not off the case values.
 *
 * THE TWO INNER DISPATCHES ARE switches, NOT CHAINS, and the delay slot is the
 * discriminator: each converted beql carries the CASE BODY'S first instruction
 * (daddu $4,$17,$0, the arm's own argument setup), never the next guard's
 * constant.  The compare chain runs 2, 1, 0 -- REVERSED -- so source order is
 * ascending 0, 1, 2 with case 0 empty.
 *
 * lbu / addiu $2,$0,-5 / daddiu $3,$0,4 / and / or / sb on r->f04 is a ONE-BIT
 * BITFIELD AT BIT 2 assigned 1 -- the daddiu materialising the ORed constant
 * beside a full insert is the recorded asymmetry.  mwcc allocates bitfields
 * from the LSB, so the 2-bit filler is declared first.
 *
 * THE SAME SPLIT APPLIES TO THE ESCAPED LOCALS: case 3's out-parameter lives
 * at 0x9C($29) and case 6's pair at 0x98/0x94.  Reusing ONE local for case 3
 * and case 6 is the right length and puts all six of case 6's stack
 * displacements 4 bytes high -- the recorded "every bad word is an ($29)
 * displacement is a declaration order" residue, reached from the direction of
 * a variable that should have been two.  mwcc allocates LATER declarations to
 * LOWER addresses, so the 0x9C slot is declared first.
 *
 * $16 holds TWO distinct source variables with disjoint live ranges -- p16 =
 * r + 0xC in cases 4/6/8, and the insect_InsectFileSlotGetData_511fa0 result in case 3.  They
 * are separate locals; sharing one would give the allocator live ranges the
 * original never had.
 *
 * The allocator call is the ordinary polarity of the ranking rule in
 * [[insect-alloc-ranking-liveness]]: addiu $4,$0,0x248 heads the block and
 * daddu $5,$18,$0 fills the delay slot -- CONSTANT first, because p18 is read
 * again after the call, so its base VALUE lives.  That is the arm our compiler
 * already produces, which is why it needs nothing special here.
 */

typedef struct Ins {
    u8  pad000[0x138];
    u8  f138[0x35F4 - 0x138];
    void *f35F4;                /* +0x35F4 -- the constructed object */
    u8  f35F8[0x4920 - 0x35F8];
    u8  f4920[0x4FBC - 0x4920];
    u8  f4FBC;                  /* +0x4FBC */
    u8  pad4FBD[0x5000 - 0x4FBD];
    u8  f5000[0x30];            /* +0x5000 -- the path buffer */
} Ins;

/* the constructed object's header: a 16-bit state at +0xE6 */
typedef struct Job { u8 pad00[0xE6]; s16 fE6; } Job;

typedef struct Slot { u8 b[0x28]; } Slot;

typedef struct Grp {
    u8   pad00[0xF];
    u8   f0F;                   /* +0x0F */
    u8   pad10[0x18 - 0x10];
    Slot arr[5];                /* +0x18, stride 0x28 */
} Grp;

typedef struct Ent {
    u8 pad00[0x21];
    s8 f21;                     /* +0x21 */
    s8 f22;                     /* +0x22 */
    u8 pad23[0x28 - 0x23];
} Ent;

typedef struct Rec {
    u8 pad00[4];
    u8 fill4 : 2;               /* mwcc allocates bitfields from the LSB */
    u8 bit2  : 1;               /* +0x04 bit 2 */
    u8 rest4 : 5;
    u8 pad05[0xC - 0x05];
    Grp grp;                    /* +0x0C */
} Rec;

typedef struct Head { u8 pad00[0x24]; s32 f24; } Head;

extern u8 insect_D_00524DF0[];
extern u8 D_00455260[];
extern void *D_00484104;        /* gp window: PLAIN */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *dst, const void *src, s32 n);

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowTextEntryMaybe_5024c0(Ins *o)
{
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    Ent *e;
    Grp *p16;
    void *a;
    s32 i;
    void *m;
    void *q;
    void *p18;
    void *p22;
    Ent *p23;
    Rec *r;
    s32 n;

    p22 = o->f4920;
    r = ((Rec *)RecordGetPayloadIfKind3D_430af0(((Head *)GetGameData_1fede0())->f24));
    p18 = o->f138;
    p23 = (Ent *)((u8 *)r + 0xF4);
    p16 = &r->grp;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 0:
        break;
    case 1:
        insect_InsectFileSlotRequest_512140(o->f5000, insect_D_00524DF0, 0);
        insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
        MemStackHeapReinit_14de90(p18);
        o->f4FBC = o->f4FBC | 2;
        break;
    case 2:
        break;
    case 3:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            sp9C = 0;
            q = insect_InsectFileSlotGetData_511fa0(o->f5000, &sp9C);
            MemStackHeapAlloc_14db10(p18, 2, 0, 0x40);
            m = MemStackNew_14e230(0x248, p18);
            if (m != 0) {
                m = TextEntryCtor_436950(m);
            }
            o->f35F4 = m;
            TextEntryReset_436930(m);
            TextEntryAllocParts_436860(o->f35F4, p18, D_00455260);
            TextEntryLoadRes_4366f0(o->f35F4, p18, q);
            D_00484104 = o->f35F4;
            MemStackReturnToOwnerMaybe_14dad0(p18);
            insect_InsectFileSlotRelease_512020(o->f5000);
            insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x44);
            insect_InsectBattleSetFlag_50dad0(o, 0x45);
        }
        break;
    case 4:
        ((Job *)o->f35F4)->fE6 = 0;
        TextEntrySetMode_436450(o->f35F4, (long long)(2));
        TextEntrySetState_434410(o->f35F4, 0x6D61, 1);
        TextEntrySetName_435780(o->f35F4, p16);
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        /* fallthrough */
    case 5:
        switch (((Job *)o->f35F4)->fE6) {
        case 0:
            break;
        case 1:
            insect_InsectBattleSetState_50d8c0(o, 0xF, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x4A, 2, -1);
            MenuResGroupUnloadGroup3_4366a0();
            break;
        case 2:
            insect_InsectBattleSetStep_50d7a0(o, 7, 0, -1);
            break;
        }
        break;
    case 7:
        ((Job *)o->f35F4)->fE6 = 0;
        TextEntrySetMode_436450(o->f35F4, (long long)(3));
        TextEntrySetState_434410(o->f35F4, 0x6D61, 1);
        TextEntrySetName_435780(o->f35F4, (u8 *)p16 + 9);
        insect_InsectBattleSetStep_50d7a0(o, 8, 0, -1);
        /* fallthrough */
    case 8:
        switch (((Job *)o->f35F4)->fE6) {
        case 0:
            break;
        case 1:
            insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
            break;
        case 2:
            insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
            break;
        }
        break;
    case 6:
        a = insect_InsectTeamGetPiece_5138d0(o->f35F8, 0);
        i = 0;
        do {
            n = insect_InsectTeamSlotGetMember_513eb0(p22, i);
            insect_InsectTeamSlotGetCell_513d90(p22, i, &sp98, &sp94, 0);
            sp94 = sp94 - 5;
            e = &p23[n];
            e->f21 = (s8)sp98;
            e->f22 = (s8)sp94;
            memcpy(&p16->arr[i], e, 0x28);
            if (insect_InsectPieceIsKing_514b00(a) != 0) {
                p16->f0F = i;
            }
            i = i + 1;
            a = (u8 *)a + 0x1E8;
        } while (i < 5);
        r->bit2 = 1;
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 9:
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 10:
        insect_InsectBattleSetState_50d8c0(o, 0x28, 0, -1);
        break;
    }
}
