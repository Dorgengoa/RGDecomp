/* SPDX-License-Identifier: CC0-1.0 */
/* VU instruction decoding, shared by the interpreter, the disassembler and the
 * opcode census.  Encoding from the public VU instruction-set description. */
#ifndef RG_PS2_VU_DECODE_H
#define RG_PS2_VU_DECODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- upper ---- */
#define VU_UPPER_KINDS(X) \
    X(ADD) X(SUB) X(MADD) X(MSUB) X(MUL) X(MAX) X(MINI) \
    X(OPMULA) X(OPMSUB) X(ITOF) X(FTOI) X(ABS) X(CLIP) X(NOP) X(INVALID)

enum {
#define X(n) VU_U_##n,
    VU_UPPER_KINDS(X)
#undef X
    VU_U_COUNT
};

enum { VU_SRC_VF = 0, VU_SRC_BC = 1, VU_SRC_Q = 2, VU_SRC_I = 3 };

/* bits field of vu_upper */
enum { VU_B_I = 0x10, VU_B_E = 0x08, VU_B_M = 0x04, VU_B_D = 0x02, VU_B_T = 0x01 };

typedef struct vu_upper {
    uint8_t kind, src, bc, to_acc;
    uint8_t dest, fs, ft, fd;
    uint8_t frac;   /* ITOF/FTOI: 0, 4, 12, 15 */
    uint8_t bits;   /* VU_B_* */
} vu_upper;

/* ---- lower ---- */
#define VU_LOWER_OPS(X) \
    X(NOP) X(LOI) X(INVALID) \
    X(LQ) X(SQ) X(ILW) X(ISW) X(IADDIU) X(ISUBIU) \
    X(FCEQ) X(FCSET) X(FCAND) X(FCOR) X(FSEQ) X(FSSET) X(FSAND) X(FSOR) \
    X(FMEQ) X(FMAND) X(FMOR) X(FCGET) \
    X(B) X(BAL) X(JR) X(JALR) X(IBEQ) X(IBNE) X(IBLTZ) X(IBGTZ) X(IBLEZ) X(IBGEZ) \
    X(IADD) X(ISUB) X(IADDI) X(IAND) X(IOR) \
    X(MOVE) X(MR32) X(LQI) X(SQI) X(LQD) X(SQD) X(DIV) X(SQRT) X(RSQRT) X(WAITQ) \
    X(MTIR) X(MFIR) X(ILWR) X(ISWR) X(RNEXT) X(RGET) X(RINIT) X(RXOR) X(MFP) \
    X(XTOP) X(XITOP) X(XGKICK) \
    X(ESADD) X(ERSADD) X(ELENG) X(ERLENG) X(EATANxy) X(EATANxz) X(ESUM) \
    X(ESQRT) X(ERSQRT) X(ERCPR) X(WAITP) X(ESIN) X(EATAN) X(EEXP)

enum {
#define X(n) VU_L_##n,
    VU_LOWER_OPS(X)
#undef X
    VU_L_COUNT
};

typedef struct vu_lower {
    uint16_t op;
    uint8_t dest, ft, fs, fd;  /* ft = it, fs = is, fd = id */
    uint8_t fsf, ftf;
    int32_t imm;               /* imm11/imm5 sign-extended; imm15/12/24 raw; LOI word */
} vu_lower;

typedef struct vu_pair {
    vu_upper up;
    vu_lower lo;
    uint32_t uw, lw;           /* raw words */
} vu_pair;

void vu_decode_upper(uint32_t w, vu_upper *u);
void vu_decode_lower(uint32_t w, vu_lower *l);
/* decodes a pair; if the upper I bit is set the lower is LOI */
void vu_decode_pair(uint32_t lower_word, uint32_t upper_word, vu_pair *p);

/* census name of an upper op, e.g. "MADDAbc", "MULq", "FTOI4" */
const char *vu_upper_name(const vu_upper *u);
const char *vu_lower_name(int op);

/* one-line disassembly; pc in bytes (used for branch targets) */
void vu_disasm_pair(const vu_pair *p, uint32_t pc, char *buf, unsigned bufsz);

/* register-use summary (for the stall model and census checks) */
typedef struct vu_use {
    uint8_t vf_r[4];  uint8_t vf_r_mask[4];  unsigned n_vf_r;  /* up to 4 VF reads */
    uint8_t vf_w;     uint8_t vf_w_mask;     /* 0 = none (vf0 writes are dropped) */
    int8_t vi_w;      /* VI written by lower, -1 none */
    int8_t vi_r0, vi_r1;  /* VI read by lower, -1 none */
    uint8_t is_branch, is_cond_branch, uses_q, writes_q, uses_p, writes_p;
    uint8_t reads_i;
} vu_use;
void vu_upper_use(const vu_upper *u, vu_use *out);
void vu_lower_use(const vu_lower *l, vu_use *out);

#ifdef __cplusplus
}
#endif
#endif
