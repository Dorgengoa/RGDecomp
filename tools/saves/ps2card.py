#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Move Rogue Galaxy saves between the port's memory cards and PCSX2 cards.

Cards it reads and writes (CARD below):
  *.ps2           PCSX2 / raw memory card image: 8 MB card, 16384 pages of 512 bytes,
                  with (8,650,752 bytes) or without (8,388,608 bytes) the 16-byte spare
                  area holding ECC
  a directory     PCSX2 folder memory card (has _pcsx2_superblock), or one of the
                  port's cards (saves/card1, saves/card2; docs/SAVES.md)

Commands:
  list CARD                         save directories with their icon.sys titles
  import CARD [--save GLOB]...      CARD -> the port's card (--saves DIR, --slot 1|2)
  export CARD [--save GLOB]...      the port's card -> CARD (--format: new blank image)
  format IMAGE.ps2                  write a blank formatted 8 MB card image
  verify IMAGE.ps2                  superblock, FAT chains and per-page ECC
  check SAVE                        Rogue Galaxy save header digests (file or directory)
  restore NAME [--snapshot S]       put a backup from saves/backups/cardN/NAME back

--save defaults to BASCUS-97490LV5RG_* (the game's saves). An existing directory of the
same name is replaced only with --force. Run import / export / restore while the game
is not running: the port keeps the card in memory and rewrites its metadata on exit.

Written from public descriptions of the PS2 memory card file system (superblock,
indirect FAT, 512-byte directory entries, Hamming ECC per 128 bytes); no emulator or
GPL code. The ECC layout is implemented from those descriptions and has not been
compared with a card formatted by a PS2 or PCSX2 (`verify` reports what it finds).
Standard library only.
"""
import argparse
import fnmatch
import hashlib
import os
import struct
import sys
import time

# ---- card geometry ---------------------------------------------------------------------
PAGE = 512
SPARE = 16
PAGES = 16384
CLUSTER = 1024
PPC = 2  # pages per cluster
PPB = 16  # pages per erase block
CLUSTERS = PAGES // PPC  # 8192
SIZE_ECC = PAGES * (PAGE + SPARE)  # 8,650,752
SIZE_RAW = PAGES * PAGE  # 8,388,608
MAGIC = b"Sony PS2 Memory Card Format "
VERSION = b"1.2.0.0"

# formatted layout: superblock (cluster 0), indirect FAT (8), FAT (9..40), data from 41,
# two backup erase blocks at the end (1022, 1023)
IFC_CLUSTER = 8
FAT_FIRST = 9
FAT_CLUSTERS = 32
ALLOC_OFFSET = 41
BACKUP1 = 1023
BACKUP2 = 1022
ALLOC_END = BACKUP2 * PPB // PPC - ALLOC_OFFSET  # 8135 allocatable clusters
CARD_FLAGS = 0x52

FAT_FREE = 0x7FFFFFFF
FAT_EOC = 0xFFFFFFFF
FAT_USED = 0x80000000

# directory entry mode bits (sceMcFileAttr*)
M_READ, M_WRITE, M_EXEC, M_PROTECT = 0x0001, 0x0002, 0x0004, 0x0008
M_FILE, M_DIR, M_CLOSED, M_0400 = 0x0010, 0x0020, 0x0080, 0x0400
M_HIDDEN, M_EXISTS = 0x2000, 0x8000
MODE_DIR = 0x8427
MODE_DOTDOT = 0xA426
MODE_FILE = 0x8497

RG_GLOB = "BASCUS-97490LV5RG_*"
RG_DATA_SIZE = 0x1BC00
ICON_SYS_SIZE = 0x3C4


class CardError(Exception):
    pass


# ---- time stamps (sceMcStDateTime: resv, sec, min, hour, day, month, u16 year) ---------
def tod_now():
    # PS2 cards keep Japan time (UTC+9)
    t = time.gmtime(time.time() + 9 * 3600)
    return struct.pack("<BBBBBBH", 0, t.tm_sec, t.tm_min, t.tm_hour, t.tm_mday, t.tm_mon, t.tm_year)


def tod_str(b):
    _, s, mi, h, d, mo, y = struct.unpack("<BBBBBBH", b)
    return "%04d-%02d-%02d %02d:%02d:%02d" % (y, mo, d, h, mi, s)


# ---- ECC: 3 bytes of Hamming code per 128-byte chunk -----------------------------------
def _parity(v):
    v ^= v >> 4
    v ^= v >> 2
    v ^= v >> 1
    return v & 1


def _colmask(v):
    """column parity bits of one byte: bits 0..2 = parity under 0x55, 0x33, 0x0F, bit 3
    unused, bits 4..6 = 0xAA, 0xCC, 0xF0 (mcman's order; retail reads cards written so.  The
    earlier order 0x55, 0xAA, 0x33, -, 0xCC, 0x0F, 0xF0 made retail ignore the card:
    docs/BRINGUP.md 2026-10-18 (f), docs/TEST-FIXTURES.md "Retail comparison")"""
    p = lambda m: _parity(v & m)
    return p(0x55) | p(0x33) << 1 | p(0x0F) << 2 | p(0xAA) << 4 | p(0xCC) << 5 | p(0xF0) << 6


_COL = [_colmask(v) for v in range(256)]
_PAR = [_parity(v) for v in range(256)]


def ecc128(chunk):
    """(column parity, line parity of index bits clear, line parity of index bits set)"""
    cp, lp0, lp1 = 0x77, 0x7F, 0x7F
    for i, c in enumerate(chunk):
        cp ^= _COL[c]
        if _PAR[c]:
            lp0 ^= ~i & 0x7F
            lp1 ^= i
    return bytes((cp, lp0 & 0x7F, lp1 & 0x7F))


def spare_for(page):
    """the 16-byte spare area: ECC of the four 128-byte chunks, then 4 zero bytes"""
    return b"".join(ecc128(page[i:i + 128]) for i in range(0, PAGE, 128)) + b"\0\0\0\0"


# ---- data model shared by every card kind ---------------------------------------------
class Entry:
    """a file in a save directory"""

    def __init__(self, name, data, mode=MODE_FILE, created=None, modified=None):
        self.name = name
        self.data = data
        self.mode = mode
        self.created = created or tod_now()
        self.modified = modified or self.created


class SaveDir:
    def __init__(self, name, files, mode=MODE_DIR, created=None, modified=None):
        self.name = name
        self.files = files  # [Entry], card order
        self.mode = mode
        self.created = created or tod_now()
        self.modified = modified or self.created

    def file(self, name):
        for f in self.files:
            if f.name == name:
                return f
        return None

    def kb(self):
        return sum((len(f.data) + 1023) // 1024 for f in self.files)


def icon_title(iconsys):
    """icon.sys title (Shift-JIS at 0xC0) as ASCII; full-width letters / digits mapped"""
    if not iconsys or len(iconsys) < 0x104 or iconsys[:4] != b"PS2D":
        return ""
    brk = struct.unpack_from("<H", iconsys, 6)[0]
    raw = iconsys[0xC0:0x104].split(b"\0", 1)[0]
    out, i = [], 0
    while i < len(raw):
        if i == brk and i:
            out.append(" / ")
        b = raw[i]
        if b < 0x80:
            out.append(chr(b) if 0x20 <= b < 0x7F else "?")
            i += 1
            continue
        try:
            ch = raw[i:i + 2].decode("shift_jis")
            ch = {"\u3000": " "}.get(ch, ch)
            if "\uff01" <= ch <= "\uff5e":
                ch = chr(ord(ch) - 0xFEE0)
            out.append(ch if ch.isascii() else "?")
        except UnicodeDecodeError:
            out.append("?")
        i += 2
    return "".join(out).strip()


# ---- PCSX2 / raw image -------------------------------------------------------------------
class ImageCard:
    def __init__(self, path, data=None):
        self.path = path
        if data is None:
            with open(path, "rb") as f:
                data = f.read()
        if len(data) == SIZE_ECC:
            self.raw_page = PAGE + SPARE
        elif len(data) == SIZE_RAW:
            self.raw_page = PAGE
        else:
            raise CardError("%s: %d bytes is not an 8 MB card image" % (path, len(data)))
        self.img = bytearray(data)
        sb = self.read_cluster(0)
        if sb[:28] != MAGIC:
            raise CardError("%s: not formatted (no superblock; export --format --force writes a formatted card)" % path)
        (self.page_len, self.ppc, self.ppb, _, self.clusters, self.alloc_offset, self.alloc_end,
         self.root_cluster, self.backup1, self.backup2) = struct.unpack_from("<HHHHIIIIII", sb, 0x28)
        if self.page_len != PAGE or self.ppc != PPC:
            raise CardError("%s: unsupported geometry page %d x %d" % (path, self.page_len, self.ppc))
        self.ifc = [x for x in struct.unpack_from("<32I", sb, 0x50)]
        self.card_type, self.card_flags = sb[0x150], sb[0x151]
        self.dirty = set()

    # raw access
    def _page_off(self, page):
        return page * self.raw_page

    def read_page(self, page):
        o = self._page_off(page)
        return bytes(self.img[o:o + PAGE])

    def write_page(self, page, data):
        assert len(data) == PAGE
        o = self._page_off(page)
        self.img[o:o + PAGE] = data
        if self.raw_page > PAGE:
            self.img[o + PAGE:o + PAGE + SPARE] = spare_for(data)

    def read_cluster(self, c):
        return b"".join(self.read_page(c * PPC + i) for i in range(PPC))

    def write_cluster(self, c, data):
        assert len(data) == CLUSTER
        for i in range(PPC):
            self.write_page(c * PPC + i, data[i * PAGE:(i + 1) * PAGE])

    # FAT (entries relative to alloc_offset, reached through the indirect FAT clusters)
    def _fat_loc(self, n):
        per = CLUSTER // 4
        fat_index = n // per
        ifc = self.ifc[fat_index // per]
        ifc_data = self.read_cluster(ifc)
        fat_cluster = struct.unpack_from("<I", ifc_data, (fat_index % per) * 4)[0]
        return fat_cluster, (n % per) * 4

    def fat(self, n):
        c, o = self._fat_loc(n)
        return struct.unpack_from("<I", self.read_cluster(c), o)[0]

    def set_fat(self, n, v):
        c, o = self._fat_loc(n)
        b = bytearray(self.read_cluster(c))
        struct.pack_into("<I", b, o, v)
        self.write_cluster(c, bytes(b))

    def chain(self, first):
        out, n, seen = [], first, set()
        while True:
            if n in seen or n >= self.alloc_end:
                raise CardError("bad FAT chain from cluster %d" % first)
            seen.add(n)
            out.append(n)
            v = self.fat(n)
            if v == FAT_EOC:
                return out
            if not v & FAT_USED:
                raise CardError("FAT chain from %d runs into a free cluster" % first)
            n = v & 0x7FFFFFFF

    def read_chain(self, first, length):
        data = b"".join(self.read_cluster(self.alloc_offset + n) for n in self.chain(first))
        return data[:length]

    # directories: 512-byte entries, 2 per cluster
    @staticmethod
    def parse_dirent(b):
        mode, length = struct.unpack_from("<H2xI", b, 0)
        created = b[8:16]
        cluster, dir_entry = struct.unpack_from("<II", b, 0x10)
        modified = b[0x18:0x20]
        attr = struct.unpack_from("<I", b, 0x20)[0]
        name = b[0x40:0x60].split(b"\0", 1)[0].decode("latin-1")
        return dict(mode=mode, length=length, created=created, cluster=cluster, dir_entry=dir_entry,
                    modified=modified, attr=attr, name=name)

    @staticmethod
    def make_dirent(mode, length, created, cluster, dir_entry, modified, name, attr=0):
        b = bytearray(PAGE)
        struct.pack_into("<H2xI", b, 0, mode, length)
        b[8:16] = created
        struct.pack_into("<II", b, 0x10, cluster, dir_entry)
        b[0x18:0x20] = modified
        struct.pack_into("<I", b, 0x20, attr)
        nb = name.encode("latin-1")
        if len(nb) > 31:
            raise CardError("name too long: %s" % name)
        b[0x40:0x40 + len(nb)] = nb
        return bytes(b)

    def read_dir(self, first, count=None):
        clusters = self.chain(first)
        raw = b"".join(self.read_cluster(self.alloc_offset + n) for n in clusters)
        ents = [self.parse_dirent(raw[i:i + PAGE]) for i in range(0, len(raw), PAGE)]
        if count is None:
            count = ents[0]["length"]
        return ents[:count]

    def _dir_slot(self, first, index):
        """(absolute page) of entry `index` of the directory starting at `first`"""
        clusters = self.chain(first)
        c = clusters[index // 2]
        return (self.alloc_offset + c) * PPC + index % 2

    def root(self):
        return self.read_dir(self.root_cluster)

    def list(self):
        out = []
        for e in self.root()[2:]:
            if not e["mode"] & M_EXISTS or not e["mode"] & M_DIR:
                continue
            files = []
            for f in self.read_dir(e["cluster"], e["length"])[2:]:
                if not f["mode"] & M_EXISTS or not f["mode"] & M_FILE:
                    continue
                data = self.read_chain(f["cluster"], f["length"]) if f["length"] else b""
                files.append(Entry(f["name"], data, f["mode"], f["created"], f["modified"]))
            out.append(SaveDir(e["name"], files, e["mode"], e["created"], e["modified"]))
        return out

    # allocation
    def free_clusters(self):
        return [n for n in range(self.alloc_end) if not self.fat(n) & FAT_USED]

    def _fat_table(self):
        """the whole FAT as a list (fast path for allocation)"""
        per = CLUSTER // 4
        tab = []
        for k in range((self.alloc_end + per - 1) // per):
            ifc = self.ifc[k // per]
            fc = struct.unpack_from("<I", self.read_cluster(ifc), (k % per) * 4)[0]
            tab.extend(struct.unpack("<%dI" % per, self.read_cluster(fc)))
        return tab[:self.alloc_end]

    def alloc(self, n, taken):
        tab = self._fat_table()
        got = [i for i, v in enumerate(tab) if not v & FAT_USED and i not in taken][:n]
        if len(got) < n:
            raise CardError("card full: %d clusters needed, %d free" % (n, len(got)))
        taken.update(got)
        return got

    def write_chain(self, clusters, data):
        for i, c in enumerate(clusters):
            nxt = FAT_EOC if i == len(clusters) - 1 else (clusters[i + 1] | FAT_USED)
            self.set_fat(c, nxt)
            chunk = data[i * CLUSTER:(i + 1) * CLUSTER]
            self.write_cluster(self.alloc_offset + c, chunk.ljust(CLUSTER, b"\0"))

    def free_chain(self, first):
        for n in self.chain(first):
            self.set_fat(n, FAT_FREE)

    def remove_dir(self, name):
        root = self.root()
        for i, e in enumerate(root):
            if i >= 2 and e["mode"] & M_EXISTS and e["name"] == name:
                for f in self.read_dir(e["cluster"], e["length"])[2:]:
                    if f["mode"] & M_EXISTS and f["length"]:
                        self.free_chain(f["cluster"])
                self.free_chain(e["cluster"])
                page = self._dir_slot(self.root_cluster, i)
                b = bytearray(self.read_page(page))
                struct.pack_into("<H", b, 0, e["mode"] & ~M_EXISTS)
                self.write_page(page, bytes(b))
                return True
        return False

    def add_dir(self, sd):
        root = self.root()
        if any(i >= 2 and e["mode"] & M_EXISTS and e["name"] == sd.name for i, e in enumerate(root)):
            raise CardError("%s already on the card" % sd.name)
        taken = set()
        # the root's slot: a deleted entry, else a new one (maybe a new root cluster)
        slot = next((i for i, e in enumerate(root) if i >= 2 and not e["mode"] & M_EXISTS), None)
        root_clusters = self.chain(self.root_cluster)
        if slot is None:
            slot = len(root)
            if slot >= 2 * len(root_clusters):
                extra = self.alloc(1, taken)[0]
                self.set_fat(root_clusters[-1], extra | FAT_USED)
                self.set_fat(extra, FAT_EOC)
                self.write_cluster(self.alloc_offset + extra, b"\0" * CLUSTER)
        n_ents = 2 + len(sd.files)
        dclusters = self.alloc((n_ents + 1) // 2, taken)
        fchains = [self.alloc((len(f.data) + CLUSTER - 1) // CLUSTER, taken) if f.data else [] for f in sd.files]
        # the directory: "." points back at its entry in the root, ".." is unused
        now = tod_now()
        ents = [self.make_dirent(sd.mode, n_ents, sd.created, self.root_cluster, slot, sd.modified, "."),
                self.make_dirent(MODE_DOTDOT, 0, sd.created, 0, 0, sd.modified, "..")]
        for f, ch in zip(sd.files, fchains):
            ents.append(self.make_dirent(f.mode, len(f.data), f.created, ch[0] if ch else FAT_EOC, 0,
                                         f.modified, f.name))
            self.write_chain(ch, f.data) if ch else None
        blob = b"".join(ents)
        self.write_chain(dclusters, blob)
        # the root entry and the root's "." count / time
        page = self._dir_slot(self.root_cluster, slot)
        self.write_page(page, self.make_dirent(sd.mode, n_ents, sd.created, dclusters[0], 0, sd.modified, sd.name))
        if slot >= len(root):
            p0 = self._dir_slot(self.root_cluster, 0)
            dot = bytearray(self.read_page(p0))
            struct.pack_into("<I", dot, 4, slot + 1)
            dot[0x18:0x20] = now
            self.write_page(p0, bytes(dot))

    def save(self, path=None):
        path = path or self.path
        tmp = path + ".tmp"
        with open(tmp, "wb") as f:
            f.write(self.img)
            f.flush()
            os.fsync(f.fileno())
        os.replace(tmp, path)

    # checks
    def verify(self):
        problems = []
        if self.raw_page > PAGE:
            bad = 0
            for p in range(PAGES):
                o = p * self.raw_page
                page = bytes(self.img[o:o + PAGE])
                spare = bytes(self.img[o + PAGE:o + PAGE + 12])
                if spare == b"\xff" * 12 and page == b"\xff" * PAGE:
                    continue  # erased
                if spare != spare_for(page)[:12]:
                    bad += 1
                    if bad <= 5:
                        problems.append("page %d: ECC %s, computed %s" % (p, spare.hex(), spare_for(page)[:12].hex()))
            if bad > 5:
                problems.append("... %d pages with ECC differences in all" % bad)
        for sd in self.root()[2:]:
            if sd["mode"] & M_EXISTS:
                try:
                    for f in self.read_dir(sd["cluster"], sd["length"])[2:]:
                        if f["mode"] & M_EXISTS and f["length"]:
                            n = len(self.chain(f["cluster"]))
                            if n != (f["length"] + CLUSTER - 1) // CLUSTER:
                                problems.append("%s/%s: %d clusters for %d bytes" % (sd["name"], f["name"], n, f["length"]))
                except CardError as e:
                    problems.append("%s: %s" % (sd["name"], e))
        return problems


def format_image(ecc=True):
    """a blank formatted 8 MB card"""
    raw_page = PAGE + SPARE if ecc else PAGE
    img = bytearray(b"\xff" * (raw_page * PAGES))
    card = ImageCard.__new__(ImageCard)
    card.path, card.raw_page, card.img, card.dirty = None, raw_page, img, set()
    # superblock
    sb = bytearray(b"\xff" * CLUSTER)
    sb[0:0x154] = b"\0" * 0x154
    sb[0:28] = MAGIC
    sb[0x1C:0x1C + len(VERSION)] = VERSION
    struct.pack_into("<HHHHIIIIII", sb, 0x28, PAGE, PPC, PPB, 0xFF00, CLUSTERS, ALLOC_OFFSET, ALLOC_END, 0,
                     BACKUP1, BACKUP2)
    ifc = [IFC_CLUSTER] + [0] * 31
    struct.pack_into("<32I", sb, 0x50, *ifc)
    struct.pack_into("<32I", sb, 0xD0, *([0xFFFFFFFF] * 32))
    sb[0x150] = 2
    sb[0x151] = CARD_FLAGS
    card.write_cluster(0, bytes(sb))
    # indirect FAT and FAT
    card.write_cluster(IFC_CLUSTER, struct.pack("<256I", *([FAT_FIRST + i for i in range(FAT_CLUSTERS)] +
                                                          [0] * (256 - FAT_CLUSTERS))))
    per = CLUSTER // 4
    for k in range(FAT_CLUSTERS):
        ents = []
        for i in range(per):
            n = k * per + i
            ents.append(FAT_EOC if n == 0 else FAT_FREE)
        card.write_cluster(FAT_FIRST + k, struct.pack("<256I", *ents))
    # root directory: "." and ".." in relative cluster 0
    now = tod_now()
    root = (ImageCard.make_dirent(MODE_DIR, 2, now, 0, 0, now, ".") +
            ImageCard.make_dirent(MODE_DOTDOT, 0, now, 0, 0, now, ".."))
    card.write_cluster(ALLOC_OFFSET, root)
    return ImageCard("<new>", bytes(img))


# ---- PCSX2 folder memory card ---------------------------------------------------------
class FolderCard:
    """PCSX2 folder card: one host folder per save directory. PCSX2's own bookkeeping
    files (_pcsx2_*) are skipped on import and left alone on export; PCSX2 indexes
    files it finds without them."""

    def __init__(self, path):
        self.path = path

    def list(self):
        out = []
        for name in sorted(os.listdir(self.path)):
            p = os.path.join(self.path, name)
            if name.startswith("_pcsx2_") or not os.path.isdir(p):
                continue
            files = []
            for fn in sorted(os.listdir(p)):
                fp = os.path.join(p, fn)
                if fn.startswith("_pcsx2_") or not os.path.isfile(fp):
                    continue
                with open(fp, "rb") as f:
                    files.append(Entry(fn, f.read()))
            out.append(SaveDir(name, _rg_order(files)))
        return out

    def remove_dir(self, name):
        p = os.path.join(self.path, name)
        if not os.path.isdir(p):
            return False
        for fn in os.listdir(p):
            if not fn.startswith("_pcsx2_"):
                os.remove(os.path.join(p, fn))
        return True

    def add_dir(self, sd):
        p = os.path.join(self.path, sd.name)
        if os.path.isdir(p) and any(not n.startswith("_pcsx2_") for n in os.listdir(p)):
            raise CardError("%s already on the card" % sd.name)
        os.makedirs(p, exist_ok=True)
        for f in sd.files:
            _write_atomic(os.path.join(p, f.name), f.data)

    def save(self, path=None):
        pass


def _rg_order(files):
    """the order the game creates its files in: icon.sys, the icon, the data"""
    rank = lambda f: (0 if f.name == "icon.sys" else 2 if f.name.startswith("BASCUS-") else 1, f.name)
    return sorted(files, key=rank)


def _write_atomic(path, data):
    tmp = path + "%~tmp"
    with open(tmp, "wb") as f:
        f.write(data)
        f.flush()
        os.fsync(f.fileno())
    os.replace(tmp, path)


# ---- the port's card (saves/cardN, docs/SAVES.md) ---------------------------------------
HEX = "0123456789ABCDEF"


def _enc_name(name, meta=False):
    """the port's host-name escaping (src/ps2/padmc/mccard.c enc_name)"""
    base = name.split(".", 1)[0].upper()
    resv = base in ("CON", "PRN", "AUX", "NUL") or (len(base) == 4 and base[:3] in ("COM", "LPT")
                                                    and base[3] in "123456789")
    out = []
    raw = name.encode("latin-1")
    for i, b in enumerate(raw):
        esc = b < 0x20 or b >= 0x7F or chr(b) in '<>:"/\\|?*%'
        if meta and b == 0x20:
            esc = True
        if i == len(raw) - 1 and chr(b) in ". ":
            esc = True
        if i == 0 and resv:
            esc = True
        out.append("%" + HEX[b >> 4] + HEX[b & 15] if esc else chr(b))
    return "".join(out)


def _dec_name(s):
    out, i = bytearray(), 0
    while i < len(s):
        h = s[i + 1:i + 3]
        if s[i] == "%" and len(h) == 2 and all(c in "0123456789abcdefABCDEF" for c in h):
            out.append(int(s[i + 1:i + 3], 16))
            i += 3
        else:
            out += s[i].encode("latin-1")
            i += 1
    return out.decode("latin-1")


class PortCard:
    """<saves>/card<N>/ plus the metadata file <saves>/card<N>.card"""

    def __init__(self, saves, slot):
        self.saves = saves
        self.slot = slot
        self.dir = os.path.join(saves, "card%d" % slot)
        self.meta = os.path.join(saves, "card%d.card" % slot)
        legacy = os.path.join(saves, "slot%d" % (slot - 1))
        if not os.path.isdir(self.dir) and os.path.isdir(legacy):
            self.dir, self.meta = legacy, legacy + ".card"
        self.records = []  # [seq, kind, attr, ctime, mtime, path]
        self.header = {"formatted": "1", "seq": "0"}
        if os.path.isfile(self.meta):
            with open(self.meta, "r", encoding="latin-1") as f:
                for line in f:
                    p = line.split()
                    if len(p) == 7 and p[0] == "E":
                        self.records.append([int(p[1]), p[2], int(p[3], 16), bytes.fromhex(p[4]),
                                             bytes.fromhex(p[5]), _dec_name(p[6])])
                    elif len(p) == 2 and p[0] in ("formatted", "seq"):
                        self.header[p[0]] = p[1]

    def exists(self):
        return os.path.isdir(self.dir)

    def _rec(self, path):
        for r in self.records:
            if r[5] == path:
                return r
        return None

    def list(self):
        if not os.path.isdir(self.dir):
            return []
        out = []
        dirs = []
        for hn in os.listdir(self.dir):
            if "%~" in hn or not os.path.isdir(os.path.join(self.dir, hn)):
                continue
            name = _dec_name(hn)
            r = self._rec("/" + name)
            dirs.append((r[0] if r else 1 << 30, name, hn, r))
        for _, name, hn, r in sorted(dirs):
            files = []
            hp = os.path.join(self.dir, hn)
            fl = []
            for fh in os.listdir(hp):
                if "%~" in fh or not os.path.isfile(os.path.join(hp, fh)):
                    continue
                fname = _dec_name(fh)
                fr = self._rec("/%s/%s" % (name, fname))
                fl.append((fr[0] if fr else 1 << 30, fname, fh, fr))
            for _, fname, fh, fr in sorted(fl):
                with open(os.path.join(hp, fh), "rb") as f:
                    data = f.read()
                if fr:
                    files.append(Entry(fname, data, fr[2], fr[3], fr[4]))
                else:
                    files.append(Entry(fname, data))
            if r:
                out.append(SaveDir(name, files, r[2], r[3], r[4]))
            else:
                out.append(SaveDir(name, _rg_order(files)))
        return out

    def free_kb(self, total=8000):
        used = 0
        sds = self.list()
        for sd in sds:
            used += (2 + len(sd.files) + 1) // 2 + sd.kb()
        used += (2 + len(sds) + 1) // 2 - 1
        return total - used

    def remove_dir(self, name):
        hp = os.path.join(self.dir, _enc_name(name))
        if not os.path.isdir(hp):
            return False
        for fh in os.listdir(hp):
            os.remove(os.path.join(hp, fh))
        os.rmdir(hp)
        pre = "/" + name
        self.records = [r for r in self.records if r[5] != pre and not r[5].startswith(pre + "/")]
        return True

    def add_dir(self, sd):
        hp = os.path.join(self.dir, _enc_name(sd.name))
        if os.path.isdir(hp):
            raise CardError("%s already on the card" % sd.name)
        if self.free_kb() < (2 + len(sd.files) + 1) // 2 + sd.kb() + 1:
            raise CardError("not enough room on card%d (%d KB free)" % (self.slot, self.free_kb()))
        os.makedirs(hp)
        seq = max([int(self.header.get("seq", "0"))] + [r[0] + 1 for r in self.records])
        if not self._rec("/"):
            now = tod_now()
            self.records.insert(0, [seq, "d", MODE_DIR, now, now, "/"])
            seq += 1
        self.records.append([seq, "d", sd.mode, sd.created, sd.modified, "/" + sd.name])
        seq += 1
        for f in sd.files:
            _write_atomic(os.path.join(hp, _enc_name(f.name)), f.data)
            self.records.append([seq, "f", f.mode, f.created, f.modified, "/%s/%s" % (sd.name, f.name)])
            seq += 1
        self.header["seq"] = str(seq)

    def save(self, path=None):
        os.makedirs(self.dir, exist_ok=True)
        if not self._rec("/"):
            now = tod_now()
            self.records.insert(0, [max([r[0] + 1 for r in self.records] + [0]), "d", MODE_DIR, now, now, "/"])
        lines = ["RGMC 1", "formatted %s" % self.header.get("formatted", "1"), "seq %s" % self.header.get("seq", "0")]
        for r in self.records:
            path = "/".join(_enc_name(c, meta=True) for c in r[5].split("/"))
            lines.append("E %u %s %04X %s %s %s" % (r[0], r[1], r[2], r[3].hex().upper(), r[4].hex().upper(),
                                                     path or "/"))
        tmp = self.meta + "%~tmp"
        with open(tmp, "w", encoding="latin-1", newline="\n") as f:
            f.write("\n".join(lines) + "\n")
        os.replace(tmp, self.meta)


# ---- the game's save header (docs/SAVES.md "Save file") -------------------------------
def check_save(data):
    """Rogue Galaxy save file checks, as SaveHeaderValidate_3e5100 does them"""
    out = []
    if len(data) < 0x800:
        return ["%d bytes: shorter than the 0x800-byte header" % len(data)]
    ver, sub = struct.unpack_from("<hh", data, 4)
    plen = struct.unpack_from("<i", data, 0x10)[0]
    hlen = struct.unpack_from("<i", data, 0x30)[0]
    if not 0 < hlen <= 0x800:
        out.append("header length %d out of range" % hlen)
    if not 0 < plen <= RG_DATA_SIZE:
        out.append("payload length %d out of range" % plen)
    if ver != 0x25:
        out.append("version %#x (the US release writes 0x25)" % ver)
    if not out:
        if hashlib.md5(data[0x50:0x50 + hlen]).digest() != data[0x40:0x50]:
            out.append("header digest (MD5 at +0x40) does not match")
        if hashlib.md5(data[0x50:0x50 + plen]).digest() != data[0x20:0x30]:
            out.append("payload digest (MD5 at +0x20) does not match")
    return out


# ---- command line -----------------------------------------------------------------------
def open_card(path):
    """a .ps2 image, a PCSX2 folder card, or one of the port's cards (saves/cardN)"""
    if os.path.isdir(path):
        if os.path.isfile(os.path.join(path, "_pcsx2_superblock")):
            return FolderCard(path)
        base, leaf = os.path.split(os.path.normpath(path))
        if leaf[:4] == "card" and leaf[4:].isdigit():
            return PortCard(base, int(leaf[4:]))
        return FolderCard(path)
    return ImageCard(path)


def pick(dirs, globs):
    globs = globs or [RG_GLOB]
    return [d for d in dirs if any(fnmatch.fnmatchcase(d.name, g) for g in globs)]


def cmd_list(a):
    c = open_card(a.card)
    for sd in c.list():
        ic = sd.file("icon.sys")
        print("%-32s %s %5d KB  %s" % (sd.name, tod_str(sd.modified), sd.kb(), icon_title(ic.data) if ic else "(no icon.sys)"))
    if isinstance(c, ImageCard):
        print("free: %d clusters" % len(c.free_clusters()))


def _exists_conflict(dst, sel):
    names = {d.name for d in dst.list()}
    return [s.name for s in sel if s.name in names]


def cmd_import(a):
    src = open_card(a.card)
    dst = PortCard(a.saves, a.slot)
    sel = pick(src.list(), a.save)
    clash = _exists_conflict(dst, sel)
    if clash and not a.force:
        raise CardError("already on card%d: %s (use --force; the old copy goes to backups)" % (a.slot, ", ".join(clash)))
    for name in clash:
        _backup_port_dir(dst, name)
    print("import %s -> %s" % (a.card, dst.dir))
    copy_dirs_checked(src, dst, a.save)


def copy_dirs_checked(src, dst, globs):
    sel = pick(src.list(), globs)
    if not sel:
        raise CardError("no save matches %s" % ", ".join(globs or [RG_GLOB]))
    for sd in sel:
        dst.remove_dir(sd.name)
        dst.add_dir(sd)
        ic = sd.file("icon.sys")
        print("  %-24s %4d KB  %s" % (sd.name, sd.kb(), icon_title(ic.data) if ic else ""))
    dst.save()


def cmd_export(a):
    src = PortCard(a.saves, a.slot)
    if not src.exists():
        raise CardError("no card%d under %s" % (a.slot, a.saves))
    if a.format and os.path.exists(a.card) and not a.force:
        raise CardError("%s exists (use --force to replace it with a blank card)" % a.card)
    if a.format:
        dst = format_image(not a.no_ecc)
        dst.path = a.card
    else:
        dst = open_card(a.card)
    sel = pick(src.list(), a.save)
    clash = _exists_conflict(dst, sel)
    if clash and not a.force:
        raise CardError("already on %s: %s (use --force)" % (a.card, ", ".join(clash)))
    print("export %s -> %s" % (src.dir, a.card))
    copy_dirs_checked(src, dst, a.save)


def cmd_format(a):
    if os.path.exists(a.image) and not a.force:
        raise CardError("%s exists (use --force)" % a.image)
    c = format_image(not a.no_ecc)
    c.save(a.image)
    print("formatted %s (%d bytes)" % (a.image, len(c.img)))


def cmd_verify(a):
    c = ImageCard(a.image)
    probs = c.verify()
    print("%s: %s, %d save directories, %d free clusters" % (
        a.image, "with ECC" if c.raw_page > PAGE else "no ECC", len(c.list()), len(c.free_clusters())))
    for p in probs:
        print("  " + p)
    return 1 if probs else 0


def cmd_check(a):
    paths = []
    if os.path.isdir(a.save):
        for fn in sorted(os.listdir(a.save)):
            if fn.startswith("BASCUS-"):
                paths.append(os.path.join(a.save, fn))
    else:
        paths.append(a.save)
    rc = 0
    for p in paths:
        with open(p, "rb") as f:
            probs = check_save(f.read())
        print("%s: %s" % (p, "ok" if not probs else "; ".join(probs)))
        rc |= 1 if probs else 0
    return rc


def _backup_port_dir(card, name):
    """copy a port save directory into saves/backups/cardN/NAME/<stamp>-import"""
    src = os.path.join(card.dir, _enc_name(name))
    if not os.path.isdir(src):
        return
    stamp = time.strftime("%Y-%m-%d_%H%M%S") + "_import"
    dst = os.path.join(card.saves, "backups", "card%d" % card.slot, _enc_name(name), stamp)
    os.makedirs(dst, exist_ok=True)
    for fn in os.listdir(src):
        with open(os.path.join(src, fn), "rb") as f:
            _write_atomic(os.path.join(dst, fn), f.read())


def cmd_restore(a):
    card = PortCard(a.saves, a.slot)
    bdir = os.path.join(a.saves, "backups", "card%d" % a.slot, _enc_name(a.name))
    snaps = sorted(s for s in os.listdir(bdir) if "%~" not in s) if os.path.isdir(bdir) else []
    if a.list or not snaps:
        for s in snaps:
            ic = os.path.join(bdir, s, "icon.sys")
            title = icon_title(open(ic, "rb").read()) if os.path.isfile(ic) else ""
            print("%s  %s" % (s, title))
        if not snaps:
            raise CardError("no backups of %s in %s" % (a.name, bdir))
        return 0
    snap = a.snapshot or snaps[-1]
    sp = os.path.join(bdir, snap)
    if not os.path.isdir(sp):
        raise CardError("no snapshot %s (have: %s)" % (snap, ", ".join(snaps)))
    files = []
    for fh in os.listdir(sp):
        with open(os.path.join(sp, fh), "rb") as f:
            files.append(Entry(_dec_name(fh), f.read()))
    _backup_port_dir(card, a.name)
    old = {d.name: d for d in card.list()}.get(a.name)
    card.remove_dir(a.name)
    sd = SaveDir(a.name, _rg_order(files))
    if old:
        sd.created = old.created
    card.add_dir(sd)
    card.save()
    print("restored %s from %s" % (a.name, sp))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    sub = ap.add_subparsers(dest="cmd", required=True)
    saves_default = os.environ.get("RG_SAVES", "saves")

    def port_opts(p):
        p.add_argument("--saves", default=saves_default, help="the port's saves folder (default $RG_SAVES or saves)")
        p.add_argument("--slot", type=int, default=1, choices=(1, 2), help="memory card slot (default 1)")

    p = sub.add_parser("list")
    p.add_argument("card")
    p = sub.add_parser("import")
    p.add_argument("card")
    p.add_argument("--save", action="append", help="directory name or glob (default %s)" % RG_GLOB)
    p.add_argument("--force", action="store_true")
    port_opts(p)
    p = sub.add_parser("export")
    p.add_argument("card")
    p.add_argument("--save", action="append")
    p.add_argument("--format", action="store_true", help="write a new blank card image first")
    p.add_argument("--no-ecc", action="store_true", help="with --format: 8,388,608-byte image without ECC")
    p.add_argument("--force", action="store_true")
    port_opts(p)
    p = sub.add_parser("format")
    p.add_argument("image")
    p.add_argument("--no-ecc", action="store_true")
    p.add_argument("--force", action="store_true")
    p = sub.add_parser("verify")
    p.add_argument("image")
    p = sub.add_parser("check")
    p.add_argument("save")
    p = sub.add_parser("restore")
    p.add_argument("name")
    p.add_argument("--snapshot")
    p.add_argument("--list", action="store_true")
    port_opts(p)
    a = ap.parse_args(argv)
    try:
        return {"list": cmd_list, "import": cmd_import, "export": cmd_export, "format": cmd_format,
                "verify": cmd_verify, "check": cmd_check, "restore": cmd_restore}[a.cmd](a) or 0
    except (CardError, OSError) as e:
        print("ps2card: %s" % e, file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
