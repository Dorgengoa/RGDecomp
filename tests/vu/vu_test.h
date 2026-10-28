/* SPDX-License-Identifier: CC0-1.0 */
/* Shared helpers for the VU/VIF tests: a tiny check framework and an
 * instruction encoder written independently of src/ps2/vu/vu_decode.c (it is
 * cross-checked against retail words in vu_tests.c:decode_retail). */
#ifndef RG_VU_TEST_H
#define RG_VU_TEST_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "vu.h"

extern int g_fail;
#define CHECK(c)                                                              \
    do {                                                                      \
        if (!(c)) {                                                           \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c);               \
            g_fail++;                                                         \
        }                                                                     \
    } while (0)
#define CHECKX(a, b)                                                          \
    do {                                                                      \
        uint32_t a_ = (uint32_t)(a), b_ = (uint32_t)(b);                      \
        if (a_ != b_) {                                                       \
            printf("FAIL %s:%d: %s = 0x%08X, expected 0x%08X\n", __FILE__,   \
                   __LINE__, #a, a_, b_);                                     \
            g_fail++;                                                         \
        }                                                                     \
    } while (0)

static inline uint32_t F(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static inline float AF(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }

/* ---- encoder ---- */
enum { DX = 8, DY = 4, DZ = 2, DW = 1, DXYZW = 15, DXYZ = 14 };
#define U_E 0x40000000u
#define U_I 0x80000000u
#define UNOP 0x000002FFu
#define LNOP 0x8000033Cu
/* upper, normal (op6) and special (op11) forms */
#define UP(op6, dest, ft, fs, fd) \
    ((uint32_t)(dest) << 21 | (uint32_t)(ft) << 16 | (uint32_t)(fs) << 11 | (uint32_t)(fd) << 6 | (op6))
#define UP2(op11, dest, ft, fs) \
    ((uint32_t)(dest) << 21 | (uint32_t)(ft) << 16 | (uint32_t)(fs) << 11 | ((uint32_t)(op11) >> 2) << 6 | 0x3C | ((op11) & 3))
/* lower: 7-bit major opcode forms */
#define LO(op7, dest, ft, fs, imm11) \
    ((uint32_t)(op7) << 25 | (uint32_t)(dest) << 21 | (uint32_t)(ft) << 16 | (uint32_t)(fs) << 11 | ((uint32_t)(imm11) & 0x7FF))
/* lower: 0x40 group, op6 (IADD..IOR) */
#define LOP(op6, ft, fs, fd) \
    (0x80000000u | (uint32_t)(ft) << 16 | (uint32_t)(fs) << 11 | (uint32_t)(fd) << 6 | (op6))
/* lower: 0x40 group, special op11 */
#define LOP2(op11, dest, ft, fs) \
    (0x80000000u | (uint32_t)(dest) << 21 | (uint32_t)(ft) << 16 | (uint32_t)(fs) << 11 | ((uint32_t)(op11) >> 2) << 6 | 0x3C | ((op11) & 3))

/* common ops */
#define ADD(d, fd, fs, ft) UP(0x28, d, ft, fs, fd)
#define SUB(d, fd, fs, ft) UP(0x2C, d, ft, fs, fd)
#define MUL(d, fd, fs, ft) UP(0x2A, d, ft, fs, fd)
#define MADD(d, fd, fs, ft) UP(0x29, d, ft, fs, fd)
#define MSUB(d, fd, fs, ft) UP(0x2D, d, ft, fs, fd)
#define MAX(d, fd, fs, ft) UP(0x2B, d, ft, fs, fd)
#define MINI(d, fd, fs, ft) UP(0x2F, d, ft, fs, fd)
#define ADDbc(d, fd, fs, ft, bc) UP(0x00 + (bc), d, ft, fs, fd)
#define MULbc(d, fd, fs, ft, bc) UP(0x18 + (bc), d, ft, fs, fd)
#define MADDbc(d, fd, fs, ft, bc) UP(0x08 + (bc), d, ft, fs, fd)
#define MINIbc(d, fd, fs, ft, bc) UP(0x14 + (bc), d, ft, fs, fd)
#define MAXbc(d, fd, fs, ft, bc) UP(0x10 + (bc), d, ft, fs, fd)
#define MULq(d, fd, fs) UP(0x1C, d, 0, fs, fd)
#define ADDq(d, fd, fs) UP(0x20, d, 0, fs, fd)
#define ADDi(d, fd, fs) UP(0x22, d, 0, fs, fd)
#define MULi(d, fd, fs) UP(0x1E, d, 0, fs, fd)
#define MAXi(d, fd, fs) UP(0x1D, d, 0, fs, fd)
#define MINIi(d, fd, fs) UP(0x1F, d, 0, fs, fd)
#define SUBi(d, fd, fs) UP(0x26, d, 0, fs, fd)
#define MSUBi(d, fd, fs) UP(0x27, d, 0, fs, fd)
#define MADDi(d, fd, fs) UP(0x23, d, 0, fs, fd)
#define OPMSUB(fd, fs, ft) UP(0x2E, DXYZ, ft, fs, fd)
#define MULA(d, fs, ft) UP2(0x2A, d, ft, fs)
#define MADDA(d, fs, ft) UP2(0x29, d, ft, fs)
#define MULAbc(d, fs, ft, bc) UP2(0x18 + (bc), d, ft, fs)
#define MADDAbc(d, fs, ft, bc) UP2(0x08 + (bc), d, ft, fs)
#define MULAi(d, fs) UP2(0x1E, d, 0, fs)
#define MSUBAi(d, fs) UP2(0x27, d, 0, fs)
#define MADDAi(d, fs) UP2(0x23, d, 0, fs)
#define OPMULA(fs, ft) UP2(0x2E, DXYZ, ft, fs)
#define ITOF(n, d, ft, fs) UP2(0x10 + (n), d, ft, fs) /* n: 0..3 = 0/4/12/15 */
#define FTOI(n, d, ft, fs) UP2(0x14 + (n), d, ft, fs)
#define ABS(d, ft, fs) UP2(0x1D, d, ft, fs)
#define CLIP(fs, ft) UP2(0x1F, DXYZ, ft, fs)

#define LQ(d, ft, is, imm) LO(0x00, d, ft, is, imm)
#define SQ(d, fs, it, imm) LO(0x01, d, it, fs, imm)
#define ILW(d, it, is, imm) LO(0x04, d, it, is, imm)
#define ISW(d, it, is, imm) LO(0x05, d, it, is, imm)
#define IADDIU(it, is, imm) LO(0x08, ((imm) >> 11) & 15, it, is, (imm) & 0x7FF)
#define ISUBIU(it, is, imm) LO(0x09, ((imm) >> 11) & 15, it, is, (imm) & 0x7FF)
#define FCEQ(imm) ((0x10u << 25) | ((imm) & 0xFFFFFF))
#define FCSET(imm) ((0x11u << 25) | ((imm) & 0xFFFFFF))
#define FCAND(imm) ((0x12u << 25) | ((imm) & 0xFFFFFF))
#define FCOR(imm) ((0x13u << 25) | ((imm) & 0xFFFFFF))
#define FSIMM(op7, it, imm) ((uint32_t)(op7) << 25 | (((imm) >> 11) & 1u) << 21 | (uint32_t)(it) << 16 | ((imm) & 0x7FF))
#define FSEQ(it, imm) FSIMM(0x14, it, imm)
#define FSSET(imm) FSIMM(0x15, 0, imm)
#define FSAND(it, imm) FSIMM(0x16, it, imm)
#define FSOR(it, imm) FSIMM(0x17, it, imm)
#define FMEQ(it, is) LO(0x18, 0, it, is, 0)
#define FMAND(it, is) LO(0x1A, 0, it, is, 0)
#define FMOR(it, is) LO(0x1B, 0, it, is, 0)
#define FCGET(it) LO(0x1C, 0, it, 0, 0)
#define B(off) LO(0x20, 0, 0, 0, off)
#define BAL(it, off) LO(0x21, 0, it, 0, off)
#define JR(is) LO(0x24, 0, 0, is, 0)
#define JALR(it, is) LO(0x25, 0, it, is, 0)
#define IBEQ(it, is, off) LO(0x28, 0, it, is, off)
#define IBNE(it, is, off) LO(0x29, 0, it, is, off)
#define IBLTZ(is, off) LO(0x2C, 0, 0, is, off)
#define IBGTZ(is, off) LO(0x2D, 0, 0, is, off)
#define IBLEZ(is, off) LO(0x2E, 0, 0, is, off)
#define IBGEZ(is, off) LO(0x2F, 0, 0, is, off)
#define IADD(id, is, it) LOP(0x30, it, is, id)
#define ISUB(id, is, it) LOP(0x31, it, is, id)
#define IADDI(it, is, imm5) LOP(0x32, it, is, ((imm5) & 31))
#define IAND(id, is, it) LOP(0x34, it, is, id)
#define IOR(id, is, it) LOP(0x35, it, is, id)
#define MOVE(d, ft, fs) LOP2(0x30, d, ft, fs)
#define MR32(d, ft, fs) LOP2(0x31, d, ft, fs)
#define LQI(d, ft, is) LOP2(0x34, d, ft, is)
#define SQI(d, fs, it) LOP2(0x35, d, it, fs)
#define LQD(d, ft, is) LOP2(0x36, d, ft, is)
#define SQD(d, fs, it) LOP2(0x37, d, it, fs)
#define DIV(fs, fsf, ft, ftf) LOP2(0x38, ((ftf) << 2) | (fsf), ft, fs)
#define SQRT(ft, ftf) LOP2(0x39, (ftf) << 2, ft, 0)
#define RSQRT(fs, fsf, ft, ftf) LOP2(0x3A, ((ftf) << 2) | (fsf), ft, fs)
#define WAITQ LOP2(0x3B, 0, 0, 0)
#define MTIR(it, fs, fsf) LOP2(0x3C, fsf, it, fs)
#define MFIR(d, ft, is) LOP2(0x3D, d, ft, is)
#define ILWR(d, it, is) LOP2(0x3E, d, it, is)
#define ISWR(d, it, is) LOP2(0x3F, d, it, is)
#define RNEXT(d, ft) LOP2(0x40, d, ft, 0)
#define RGET(d, ft) LOP2(0x41, d, ft, 0)
#define RINIT(fs, fsf) LOP2(0x42, fsf, 0, fs)
#define RXOR(fs, fsf) LOP2(0x43, fsf, 0, fs)
#define MFP(d, ft) LOP2(0x64, d, ft, 0)
#define XTOP(it) LOP2(0x68, 0, it, 0)
#define XITOP(it) LOP2(0x69, 0, it, 0)
#define XGKICK(is) LOP2(0x6C, 0, 0, is)
#define EFU(op11, fs, fsf) LOP2(op11, fsf, 0, fs)
#define WAITP LOP2(0x7B, 0, 0, 0)

typedef struct { uint32_t up, lo; } pair_t;

/* load pairs at byte address 0, followed by an E-bit end pair + delay slot */
static inline void load_prog(vu_state *vu, const pair_t *p, int n)
{
    uint32_t w[2 * 520];
    int k;
    for (k = 0; k < n; k++) { w[2 * k] = p[k].lo; w[2 * k + 1] = p[k].up; }
    w[2 * n] = LNOP; w[2 * n + 1] = UNOP | U_E;
    w[2 * n + 2] = LNOP; w[2 * n + 3] = UNOP;
    vu_load_code(vu, 0, w, (uint32_t)(n + 2) * 8);
}

static inline vu_stop run_prog(vu_state *vu, const pair_t *p, int n)
{
    load_prog(vu, p, n);
    vu_start(vu, 0);
    return vu_run(vu, 100000);
}

static inline void setv(vu_state *vu, int r, float x, float y, float z, float w)
{
    vu->vf[r].f[0] = x; vu->vf[r].f[1] = y; vu->vf[r].f[2] = z; vu->vf[r].f[3] = w;
}

static inline void setvu(vu_state *vu, int r, uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    vu->vf[r].u[0] = x; vu->vf[r].u[1] = y; vu->vf[r].u[2] = z; vu->vf[r].u[3] = w;
}

#define CHECKV(vu, r, a, b, c, d)                                            \
    do {                                                                     \
        CHECKX((vu)->vf[r].u[0], F(a)); CHECKX((vu)->vf[r].u[1], F(b));      \
        CHECKX((vu)->vf[r].u[2], F(c)); CHECKX((vu)->vf[r].u[3], F(d));      \
    } while (0)

#endif
