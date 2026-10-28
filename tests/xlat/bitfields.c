/* SPDX-License-Identifier: CC0-1.0 */
/* dialect `bitfield-gcc` (tools/portxform.py, docs/PROTOS.md): after the stage the
 * MSVC-layout port must put every bitfield where mwcc (GCC packing) did.  Shapes from
 * the corpus: WorldDataCmdSetPartyMember_3b9b00 (u64 flags after a 2-byte pad),
 * DataTableCmdEntryDefine_3f87f0 (mixed s8/s16 runs), DataTableCmdSubEntryDefine_403b00
 * (u8/u16 run followed by a byte member), KernelGetOsdConfigParam2_446be0 (u64/u32
 * all-bitfield struct).  Expected bit positions are mipsel-linux-gnu's
 * (-fdump-record-layouts).  Exit 0 = all match. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct G {
    u8 pad0[0x94];
    u8 *unk94;
    u8 pad98[2];
    u64 f0 : 1;
    u64 f1 : 1;
    u64 f2 : 1;
} G;

typedef struct Ent {
    s16 h0;
    u16 h2;
    s8 b4a : 6;
    s8 b4b : 1;
    s8 b4c : 1;
    s8 b5;
    s8 b6a : 5;
    s16 b6b : 9;
    s8 b8a : 4;
    s16 b8b : 8;
    s32 mC;
} Ent;

typedef struct Sub {
    u8  b000_0 : 5;
    u16 b000_5 : 8;
    u16 pb000_13 : 3;
    u8  b002_0 : 4;
    u8  b002_4 : 4;
    u8  pad003[0x1];
} Sub;

typedef struct { u64 a:6; unsigned int b:3; u64 c:31; u64 d:1; u64 e:1; u64 f:2; unsigned int g:4; u64 h:16; } K;

static int bit(const void *p, unsigned pos)
{
    return (((const u8 *)p)[pos / 8] >> (pos % 8)) & 1;
}

static int only(const void *p, unsigned size, unsigned lo, unsigned w)
{
    unsigned i;
    for (i = 0; i < size * 8; i++)
        if (bit(p, i) != (i >= lo && i < lo + w))
            return 0;
    return 1;
}

#define ZERO(x) do { unsigned k_; for (k_ = 0; k_ < sizeof(x); k_++) ((u8 *)&(x))[k_] = 0; } while (0)

int main(void)
{
    int bad = 0;
    G g; Ent e; Sub s; K k;
    ZERO(g); g.f2 = 1; bad |= !only(&g, sizeof g, 0x9A * 8 + 2, 1) << 0;
    ZERO(e); e.b6b = -1; bad |= !only(&e, sizeof e, 6 * 8 + 5, 9) << 1;
    ZERO(e); e.b8a = -1; bad |= !only(&e, sizeof e, 8 * 8, 4) << 2;
    ZERO(e); e.b8b = -1; bad |= !only(&e, sizeof e, 8 * 8 + 4, 8) << 3;
    ZERO(e); e.mC = -1; bad |= !only(&e, sizeof e, 12 * 8, 32) << 4;
    ZERO(s); s.b000_5 = 0xFF; bad |= !only(&s, sizeof s, 5, 8) << 5;
    ZERO(s); s.b002_4 = 0xF; bad |= !only(&s, sizeof s, 20, 4) << 6;
    ZERO(s); s.pad003[0] = 0xFF; bad |= !only(&s, sizeof s, 24, 8) << 7;
    ZERO(k); k.c = 0x7FFFFFFF; bad |= !only(&k, sizeof k, 9, 31) << 8;
    ZERO(k); k.g = 0xF; bad |= !only(&k, sizeof k, 44, 4) << 9;
    ZERO(k); k.h = 0xFFFF; bad |= !only(&k, sizeof k, 48, 16) << 10;
    bad |= (sizeof(G) != 0xA0) << 11;
    bad |= (sizeof(Sub) != 4) << 12;
    bad |= (sizeof(K) != 8) << 13;
    return bad;
}
