/* rgp:protos */
#define RGP_SELF_GsEnvInit_1573b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
typedef struct {
    __extension__ unsigned short nloop : 15;
    unsigned short eop : 1;
    u8 pad2[5];
    u8 pad7 : 4;
    u8 nreg : 4;
    u8 regs0 : 4;
    u8 regs1 : 4;
    u8 pad9[7];
} __attribute__((aligned(2))) Tag;
typedef struct {
    Tag tag;
    u64 d10;
    u64 a18;
    u64 d20;
    u64 a28;
    u64 d30;
    u64 a38;
    u64 d40;
    u64 a48;
    s32 d50;
    s32 pad54;
    s32 a58;
} Pkt;
/*rgp*/

void GsEnvInit_1573b0(Pkt *p) {
    *(u128 *)&p->tag = 0;
    p->tag.nloop = 5;
    p->tag.eop = 1;
    p->tag.nreg = 1;
    p->tag.regs0 = 0xE;
    p->d20 = 0x5000B;
    p->d10 = 0x44;
    p->a28 = 0x47;
    p->a38 = 0x4E;
    p->a18 = 0x42;
    p->a48 = 0x4A;
    p->a58 = 0x4C;
    GsEnvSetDefaults_1572d0(p);
}
