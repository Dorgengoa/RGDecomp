/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerSetKindUv_4f61a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F61A0 -- set one grid cell's scroll offset from
 * the kind stored in its record.
 *
 * A compiled `switch` over kinds 1..8, so mwcc emits a real jump table;
 * scripts/f_jtbl.py points it at the overlay's own factory_jtbl_0050CC10.
 *
 * ★ factory_jtbl_0050CC10's entry 0 holds the address of the EPILOGUE, not of a case
 * body, so `case 0` is simply absent from the source and mwcc fills the hole
 * with the default.  The bound `sltiu 0x9` comes from the highest case, 8.
 *
 * ★ `dsll32 $7, $5, 16 / dsra32 $7, $7, 16` at the top is the normalisation of
 * an `s16` PARAMETER, not source arithmetic.
 *
 * ★★ THE RECORD ELEMENT IS A NAMED LOCAL, NOT AN INLINE INDEX.  Written as
 * `switch (o->f78[i].f0C)` the unit is the RIGHT LENGTH with 7 bad words: mwcc
 * starts the record index chain before the cell base and the two chains take
 * each other's registers.  `Rec *r = &o->f78[i];` -- the ELEMENT address, not
 * the array base and not the loaded value -- is what puts them in retail's
 * order.  Measured in one probe build against ten other spellings (a named
 * array base, an `s32`/`s16` kind local, the pointer add form, both
 * declaration orders): every one of them scores the same 7 and only the
 * element form moves.
 *
 * ★ factory_D_0050B7A0 is overlay data at 0x50B7A0, far outside the gp window
 * 0x47D170..0x48D170, so it must not take a %gp_rel relocation -- an
 * INCOMPLETE array type is what gives it `lui %hi` + `addiu %lo`.
 */

typedef struct Cell {
    u8  pad0[8];
    s16 f08;
    s16 f0A;
    u8  pad0C[0x34];
} Cell;

typedef struct Rec {
    u8  pad0[0xC];
    s16 f0C;
    u8  pad0E[6];
} Rec;

typedef struct Grid {
    u8   pad0[0x78];
    Rec *f78;
} Grid;

extern Cell factory_D_0050B7A0[];

void factory_FactoryMarkerSetKindUv_4f61a0(Grid *o, s16 i)
{
    Rec  *r = &o->f78[i];
    Cell *c = &factory_D_0050B7A0[i];

    switch (r->f0C) {
    case 1:
        c->f08 = 0;
        c->f0A = 0;
        break;
    case 2:
        c->f08 = 0;
        c->f0A = 0x30;
        break;
    case 3:
        c->f08 = 0;
        c->f0A = 0x60;
        break;
    case 4:
        c->f08 = 0;
        c->f0A = 0x90;
        break;
    case 5:
        c->f08 = 0;
        c->f0A = 0xC0;
        break;
    case 6:
        c->f08 = 0;
        c->f0A = 0xF0;
        break;
    case 7:
        c->f08 = 0;
        c->f0A = 0x120;
        break;
    case 8:
        c->f08 = 0;
        c->f0A = 0x150;
        break;
    }
}
