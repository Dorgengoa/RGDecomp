/* rgp:protos */
#define RGP_SELF_ZoneRadiusLeaveFireEventMaybe_3ebba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 2-member byte-identical group (232 B each):
   ZoneRadiusLeaveFireEventMaybe_3ebba0 / ZoneKeyedLeaveFireEventMaybe_3ebd90.  Build a request on a 0x30-byte stack object
   and hand it to the 0x3e0000 subsystem.
   Both s16 parameters are re-extended (`dsll32/dsra32 ..,16`), which is an
   explicit (s16) cast on an s32 parameter -- see
   [[normal-s16-cast-sign-extension]].

   MEASURED, 6 arms one sweep: TWO factors, both required.
     * declaration order `x` before `h` -- retail puts LocationFindByIdMaybe_411480's result
       in $17 and GetCurrentScene_1f5be0's in $18; declaring h first swaps them (5 bad);
     * the last guard is a WRAPPED body, not an early return: retail's
       `bnel $2,$0,<epilogue>` with `addiu $2,$0,1` in the likely slot is
       `if (!busy) { ... }` followed by one `return 1`, not
       `if (busy) return 1;` (which is 2 words long).
   Neither factor alone matches -- see [[insect-guard-polarity-length]] and
   [[mwcc-gpr-decl-order-map]]. */

struct Sub3ebba0 {
    u8   pad000[0x34];
    void *m34;                  /* +0x34 */
};

struct Own3ebba0 {
    u8   pad000[0x24C];
    u8   busy : 1;              /* +0x24C bit 0 */
};

struct Obj3ebba0 {
    u8   pad000[8];
    struct Sub3ebba0 *m08;      /* +0x08 */
    u8   pad00C[0x18 - 0x0C];
    void *m18;                  /* +0x18 */
    u8   pad01C[4];
    struct Own3ebba0 *m20;      /* +0x20 */
    u8   pad024[0x2C - 0x24];
    u8   locked : 1;            /* +0x2C bit 0 */
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ZoneRadiusLeaveFireEventMaybe_3ebba0(struct Obj3ebba0 *o, s32 a, s32 b)
{
    struct Sub3ebba0 *s;
    void *x;
    void *h;
    void *p;
    u8 req[0x30] __attribute__((aligned(16)));

    if (o->locked) {
        return 0;
    }
    s = o->m08;
    if (s == 0) {
        return 0;
    }
    h = LocationFindByIdMaybe_411480(s->m34, (s16)a, (s16)b);
    if (h == 0) {
        return 0;
    }
    x = GetCurrentScene_1f5be0();
    ActionPacketReset_3e3d00(req);
    ActionPacketInitZoneEnterLeaveMaybe_3e38a0(req, x, h, 0);
    EventFireTriggers_3e2660(req, 0);
    if (!o->m20->busy) {
        p = PartyGetLeaderChara_3c2820(o->m18);
        if (p != 0) {
            SkillTriggerEvalMaybe_3e1200(req, p);
        }
    }
    return 1;
}
