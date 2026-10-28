// SPDX-License-Identifier: CC0-1.0
// GS local memory on the GPU: the 4 MB mirror (a raw buffer) and the
// block/page swizzles, ported 1:1 from src/ps2/gs/gs_mem.c (the bit-formula
// arrangement, checked there against the manual's figures).  docs/GPU.md.

#ifndef GS_COMMON_HLSLI
#define GS_COMMON_HLSLI

#define PSMCT32 0x00
#define PSMCT24 0x01
#define PSMCT16 0x02
#define PSMCT16S 0x0A
#define PSMT8 0x13
#define PSMT4 0x14
#define PSMT8H 0x1B
#define PSMT4HL 0x24
#define PSMT4HH 0x2C
#define PSMZ32 0x30
#define PSMZ24 0x31
#define PSMZ16 0x32
#define PSMZ16S 0x3A

uint blk32(uint bx, uint by)
{
    return (bx & 1) | ((by & 1) << 1) | ((bx & 2) << 1) | ((by & 2) << 2) | ((bx & 4) << 2);
}
uint blk16(uint bx, uint by)
{
    return (by & 1) | ((bx & 1) << 1) | ((by & 2) << 1) | ((bx & 2) << 2) | ((by & 4) << 2);
}
uint blk16s(uint bx, uint by)
{
    return (by & 1) | ((bx & 1) << 1) | (by & 4) | ((by & 2) << 2) | ((bx & 2) << 3);
}
uint colword32(uint x, uint y)
{
    return (x & 1) | ((y & 1) << 1) | ((x & 6) << 1);
}
uint blkaddr(uint bp, uint page, uint blk)
{
    return ((bp + page * 32 + blk) & 0x3FFF) << 8;
}
uint addr32(uint bp, uint bw, uint x, uint y, uint z)
{
    uint page = (x >> 6) + (y >> 5) * bw;
    uint blk = blk32((x >> 3) & 7, (y >> 3) & 3);
    if (z) blk ^= 24;
    return blkaddr(bp, page, blk) | (((y >> 1) & 3) << 6) | (colword32(x & 7, y & 1) << 2);
}
uint addr16(uint bp, uint bw, uint x, uint y, uint s, uint z)
{
    uint page = (x >> 6) + (y >> 6) * bw;
    uint bx = (x >> 4) & 3, by = (y >> 3) & 7;
    uint blk = s ? blk16s(bx, by) : blk16(bx, by);
    if (z) blk ^= 24;
    uint w = colword32(x & 7, y & 1);
    return blkaddr(bp, page, blk) | (((y >> 1) & 3) << 6) | (w << 2) | (((x >> 3) & 1) << 1);
}
uint addr8(uint bp, uint bw, uint x, uint y)
{
    uint page = (x >> 7) + (y >> 6) * (bw >> 1);
    uint blk = blk32((x >> 4) & 7, (y >> 4) & 3);
    uint col = (y >> 2) & 3;
    uint cy = y & 3, hi = cy >> 1;
    uint xx = x & 7;
    if (hi ^ (col & 1)) xx ^= 4;
    uint w = colword32(xx, cy & 1);
    uint byte = (((x >> 3) & 1) << 1) | hi;
    return blkaddr(bp, page, blk) | (col << 6) | (w << 2) | byte;
}
uint addr4n(uint bp, uint bw, uint x, uint y)
{
    uint page = (x >> 7) + (y >> 7) * (bw >> 1);
    uint blk = blk16((x >> 5) & 3, (y >> 4) & 7);
    uint col = (y >> 2) & 3;
    uint cy = y & 3, hi = cy >> 1;
    uint xx = x & 7;
    if (hi ^ (col & 1)) xx ^= 4;
    uint w = colword32(xx, cy & 1);
    uint nib = (((x >> 3) & 3) << 1) | hi;
    return ((blkaddr(bp, page, blk) | (col << 6) | (w << 2)) << 1) + nib;
}

// Byte address of pixel (x,y); nib = nibble select for PSMT4.
uint gs_addr(uint psm, uint bp, uint bw, uint x, uint y, out uint nib)
{
    x &= 2047; y &= 2047;
    nib = 0;
    switch (psm) {
    case PSMZ32: case PSMZ24: return addr32(bp, bw, x, y, 1);
    case PSMCT16: return addr16(bp, bw, x, y, 0, 0);
    case PSMCT16S: return addr16(bp, bw, x, y, 1, 0);
    case PSMZ16: return addr16(bp, bw, x, y, 0, 1);
    case PSMZ16S: return addr16(bp, bw, x, y, 1, 1);
    case PSMT8: return addr8(bp, bw, x, y);
    case PSMT4: {
        uint a = addr4n(bp, bw, x, y);
        nib = a & 1;
        return a >> 1;
    }
    default: return addr32(bp, bw, x, y, 0);
    }
}

bool psm_is16(uint psm)
{
    return psm == PSMCT16 || psm == PSMCT16S || psm == PSMZ16 || psm == PSMZ16S;
}

// RGBA8 <-> stored colour (gs_mem.c gs_color_from_stored / _to_stored)
uint4 from_stored(uint psm, uint raw)
{
    if (psm_is16(psm))
        return uint4((raw & 31) << 3, ((raw >> 5) & 31) << 3, ((raw >> 10) & 31) << 3,
                     (raw & 0x8000) ? 0x80 : 0);
    uint4 c = uint4(raw & 255, (raw >> 8) & 255, (raw >> 16) & 255, raw >> 24);
    if (psm == PSMCT24 || psm == PSMZ24) c.a = 0;
    return c;
}
uint to_stored(uint psm, uint4 c)
{
    if (psm_is16(psm))
        return ((c.r >> 3) & 31) | (((c.g >> 3) & 31) << 5) | (((c.b >> 3) & 31) << 10) |
               ((c.a >> 7) << 15);
    uint v = c.r | (c.g << 8) | (c.b << 16) | (c.a << 24);
    if (psm == PSMCT24 || psm == PSMZ24) v &= 0xFFFFFF;
    return v;
}

#ifndef GS_MEM_RW
ByteAddressBuffer g_mem : register(t0);
#else
RWByteAddressBuffer g_mem : register(u0);
#endif

uint mem_rd32(uint a) { return g_mem.Load(a & 0x3FFFFC); }

// Raw pixel bits (gs_mem.c gs_read_pixel)
uint gs_read_pixel(uint psm, uint bp, uint bw, uint x, uint y)
{
    uint nib;
    uint a = gs_addr(psm, bp, bw, x, y, nib);
    uint w = mem_rd32(a);
    uint sh = (a & 3) * 8;
    switch (psm) {
    case PSMCT32: case PSMZ32: return w;
    case PSMCT24: case PSMZ24: return w & 0xFFFFFF;
    case PSMCT16: case PSMCT16S: case PSMZ16: case PSMZ16S: return (w >> sh) & 0xFFFF;
    case PSMT8: return (w >> sh) & 255;
    case PSMT4: { uint b = (w >> sh) & 255; return nib ? (b >> 4) : (b & 15); }
    case PSMT8H: return w >> 24;
    case PSMT4HL: return (w >> 24) & 15;
    case PSMT4HH: return w >> 28;
    default: return w;
    }
}

#endif
