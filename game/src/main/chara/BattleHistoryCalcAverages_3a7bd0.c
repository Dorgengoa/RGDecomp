/* rgp:protos */
#define RGP_SELF_BattleHistoryCalcAverages_3a7bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
//PRAGMA

typedef struct {
    s16 type;
    u8 pad2[0xE];
    f64 x10;
    s64 x18;
    s64 x20;
    u8 pad28[4];
    s32 x2C;
    s32 x30;
    s16 x34;
    s16 x36;
    s32 x38;
    s32 x3C;
    u8 pad40[0x20];
} Ent;

typedef struct {
    s32 x18;
    s32 x1C;
    s16 x20;
    s16 x22;
    s32 x24;
    s32 x28;
    u8 pad2C[4];
} Avg;

typedef struct {
    s16 n;
    s16 x2;
    s16 x4;
    u8 pad6[2];
    f64 x8;
    f64 x10;
    Avg avg;
    Ent e[1];
} Stat;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 BattleHistoryCalcAverages_3a7bd0(Stat *st)
{
    //DECLS
    f64 d1;
    f64 d2;
    s32 s2C;
    s32 s30;
    Ent *e;
    s32 s34;
    s32 s36;
    s32 i;
    s32 s38;
    s32 s3C;
    s64 prev;
    f32 fn;
    //ENDDECLS

    s36 = 0;
    s34 = 0;
    s30 = 0;
    d1 = 0;
    d2 = 0;
    s2C = 0;
    s38 = 0;
    st->x2 = 0;
    st->x4 = 0;
    st->x8 = 0;
    st->x10 = 0;
    s3C = 0;
    BattleRecordStatsReset_3a7fb0(&st->avg);
    prev = 0;
    e = st->e;
    for (i = 0; i < st->n; i++) {
        if (e->type == 1) {
            st->x2++;
        } else if (e->type == 3) {
            st->x4++;
        }
        d1 = d1 + e->x10;
        if (i > 0) {
            d2 = d2 + U64ToDouble_100370(prev - e->x20);
        }
        s2C += e->x2C;
        s30 += e->x30;
        s34 += e->x34;
        s36 += e->x36;
        s38 += e->x38;
        s3C += e->x3C;
        prev = e->x18;
        e++;
    }
    if (st->n > 0) {
        fn = (f32)st->n;
        st->x8 = dpdiv(d1, fn);
        st->avg.x18 = (s32)(0.5f + (f32)s2C / fn);
        st->avg.x1C = (s32)(0.5f + (f32)s30 / fn);
        st->avg.x20 = (s32)(0.5f + (f32)s34 / fn);
        st->avg.x22 = (s32)(0.5f + (f32)s36 / fn);
        st->avg.x24 = (s32)(0.5f + (f32)s38 / fn);
        st->avg.x28 = (s32)(0.5f + (f32)s3C / fn);
        if (st->n >= 2) {
            st->x10 = dpdiv(d2, litodp(st->n - 1));
        }
    }
    return 1;
}
