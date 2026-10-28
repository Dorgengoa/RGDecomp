/* SPDX-License-Identifier: CC0-1.0 */
/* Read-only access to the retail ELF's VU microcode packets, for the opcode
 * census tool and the whole-program smoke tests.  Never used by the game. */
#ifndef RG_PS2_VU_RETAIL_H
#define RG_PS2_VU_RETAIL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rg_elf {
    uint8_t *data;
    size_t size;
    int nph;
    struct { uint32_t off, vaddr, filesz; } ph[32];
} rg_elf;

/* RG_ELF env var, else ../work/SCUS_974.90 */
const char *rg_retail_elf_path(void);
int rg_elf_load(rg_elf *e, const char *path); /* 0 = ok */
void rg_elf_free(rg_elf *e);
const uint8_t *rg_elf_ptr(const rg_elf *e, uint32_t vaddr, uint32_t len);

/* A DMA-tagged VIF packet at vaddr: returns the VIF word stream (the tag's
 * two VIF words followed by qwc qwords) and its length in words. */
const uint32_t *rg_vif_packet(const rg_elf *e, uint32_t vaddr, size_t *nwords);

/* census/platform_vu1.tsv rows */
typedef struct vu_census_row {
    char kind[16];      /* mpg, variant, vcallms, ... */
    char addr[24];      /* hex packet address or a[i][j] */
    char vu[16];
    uint32_t dest, insns;
    char sha1[16];
    char used_by[512];
    char detail[512];
} vu_census_row;
int vu_census_load(const char *tsv_path, vu_census_row **rows); /* count, -1 on error */

#ifdef __cplusplus
}
#endif
#endif
