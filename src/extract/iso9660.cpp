// SPDX-License-Identifier: CC0-1.0
#include "iso9660.h"

#include <cctype>
#include <cerrno>
#include <cstring>
#include <set>

namespace rgx {

// ---- IsoFile ----

IsoFile::~IsoFile() {
    if (f_) std::fclose(f_);
}

static bool seek64(std::FILE* f, uint64_t off) {
#ifdef _WIN32
    return _fseeki64(f, static_cast<long long>(off), SEEK_SET) == 0;
#else
    return fseeko(f, static_cast<off_t>(off), SEEK_SET) == 0;
#endif
}

static bool size64(std::FILE* f, uint64_t& out) {
#ifdef _WIN32
    if (_fseeki64(f, 0, SEEK_END) != 0) return false;
    long long s = _ftelli64(f);
#else
    if (fseeko(f, 0, SEEK_END) != 0) return false;
    off_t s = ftello(f);
#endif
    if (s < 0) return false;
    out = static_cast<uint64_t>(s);
    return seek64(f, 0);
}

bool IsoFile::open(const std::filesystem::path& p, std::string& err) {
#ifdef _WIN32
    f_ = _wfopen(p.c_str(), L"rb");
#else
    f_ = std::fopen(p.c_str(), "rb");
#endif
    if (!f_) {
        err = "cannot open '" + p.u8string() + "': " + std::strerror(errno);
        return false;
    }
    // We do our own large-block reads; avoid a second copy through the CRT buffer.
    std::setvbuf(f_, nullptr, _IONBF, 0);
    if (!size64(f_, size_)) {
        err = "cannot determine size of '" + p.u8string() + "'";
        return false;
    }
    return true;
}

bool IsoFile::seek(uint64_t off) { return seek64(f_, off); }

size_t IsoFile::read(void* dst, size_t n) { return std::fread(dst, 1, n, f_); }

bool IsoFile::error() const { return std::ferror(f_) != 0; }

bool IsoFile::read_at(uint64_t off, void* dst, size_t n) {
    if (off > size_ || n > size_ - off) return false;
    if (!seek64(f_, off)) return false;
    return std::fread(dst, 1, n, f_) == n;
}

// ---- parsing helpers ----

namespace {

uint32_t le32(const uint8_t* p) {
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
uint16_t le16(const uint8_t* p) { return uint16_t(p[0] | (p[1] << 8)); }

std::string trim_field(const uint8_t* p, size_t n) {
    std::string s(reinterpret_cast<const char*>(p), n);
    while (!s.empty() && (s.back() == ' ' || s.back() == '\0')) s.pop_back();
    return s;
}

bool is_pvd(const uint8_t* s) { return s[0] == 1 && std::memcmp(s + 1, "CD001", 5) == 0 && s[6] == 1; }

// Turns an ISO 9660 file identifier into a safe path component. Strips the ";N" version
// and a trailing '.' (the separator of an empty extension). Rejects anything that could
// escape the output directory or that Windows can't create.
bool normalise_name(const uint8_t* p, size_t n, bool is_dir, std::string& out, std::string& err) {
    std::string s(reinterpret_cast<const char*>(p), n);
    if (!is_dir) {
        size_t semi = s.rfind(';');
        if (semi != std::string::npos) s.resize(semi);
        if (!s.empty() && s.back() == '.') s.pop_back();
    }
    if (s.empty() || s == "." || s == "..") {
        err = "invalid file identifier '" + std::string(reinterpret_cast<const char*>(p), n) + "'";
        return false;
    }
    for (unsigned char c : s) {
        if (c < 0x20 || c >= 0x7f || std::strchr("<>:\"/\\|?*", c)) {
            err = "file identifier with unsupported character: '" + s + "'";
            return false;
        }
    }
    if (s.back() == ' ' || s.back() == '.') {
        err = "file identifier ends in space or dot: '" + s + "'";
        return false;
    }
    // Windows reserved device names (with or without extension).
    std::string stem = s.substr(0, s.find('.'));
    for (auto& ch : stem) ch = char(std::toupper(static_cast<unsigned char>(ch)));
    static const char* reserved[] = {"CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5",
                                     "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4",
                                     "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};
    for (const char* r : reserved) {
        if (stem == r) {
            err = "file identifier is a reserved device name: '" + s + "'";
            return false;
        }
    }
    out = s;
    return true;
}

struct Walker {
    IsoFile& f;
    IsoImage& img;
    const IsoVolume& vol;
    std::string& err;
    std::set<uint64_t> visited;
    size_t entries = 0;

    bool check_range(uint64_t rel_lba, uint64_t size, const std::string& what) {
        uint64_t abs = vol.base_lba + rel_lba;
        uint64_t end = abs * kSectorSize + size;
        if (rel_lba > vol.volume_blocks || end > f.size()) {
            err = what + " lies outside the image (sector " + std::to_string(abs) +
                  ", " + std::to_string(size) + " bytes); the image is truncated or corrupt";
            return false;
        }
        return true;
    }

    bool walk(uint64_t rel_lba, uint64_t size, const std::string& path, int depth) {
        if (depth > 64) {
            err = "directory nesting too deep at '" + path + "'";
            return false;
        }
        uint64_t abs = vol.base_lba + rel_lba;
        if (!visited.insert(abs).second) {
            err = "directory loop at '" + path + "'";
            return false;
        }
        if (size > (64u << 20)) {
            err = "directory '" + path + "' is implausibly large";
            return false;
        }
        if (!check_range(rel_lba, size, "directory '" + path + "'")) return false;
        std::vector<uint8_t> data(size_t((size + kSectorSize - 1) / kSectorSize * kSectorSize));
        if (!f.read_at(abs * kSectorSize, data.data(), data.size())) {
            err = "read error in directory '" + path + "'";
            return false;
        }

        IsoEntry pending;  // multi-extent file being accumulated
        bool have_pending = false;
        std::string pending_name;

        size_t o = 0;
        while (o < size) {
            uint8_t len = data[o];
            if (len == 0) {  // records never straddle sectors; skip to the next one
                o = (o / kSectorSize + 1) * kSectorSize;
                continue;
            }
            if (len < 34 || o + len > data.size()) {
                err = "malformed directory record in '" + path + "'";
                return false;
            }
            const uint8_t* r = &data[o];
            o += len;
            if (++entries > 1000000) {
                err = "too many directory entries";
                return false;
            }
            uint8_t ext_attr_len = r[1];
            uint64_t elba = le32(r + 2) + ext_attr_len;
            uint64_t esize = le32(r + 10);
            uint8_t flags = r[25];
            uint8_t name_len = r[32];
            if (33u + name_len > len) {
                err = "malformed directory record in '" + path + "'";
                return false;
            }
            if (name_len == 1 && (r[33] == 0 || r[33] == 1)) continue;  // "." and ".."
            if (r[26] != 0 || r[27] != 0) {
                err = "unsupported interleaved file: " + path;
                return false;
            }
            bool is_dir = (flags & 2) != 0;
            std::string name;
            if (!normalise_name(r + 33, name_len, is_dir, name, err)) {
                err += " in '" + (path.empty() ? std::string("/") : path) + "'";
                return false;
            }
            std::string child = path + "/" + name;
            if (have_pending && name != pending_name) {
                err = "unterminated multi-extent file '" + pending.path + "'";
                return false;
            }
            if (is_dir) {
                img.dirs.push_back(child);
                if (!walk(elba, esize, child, depth + 1)) return false;
                continue;
            }
            if (!check_range(elba, esize, "file '" + child + "'")) return false;
            if (!have_pending) {
                pending = IsoEntry();
                pending.path = child;
                pending.layer = vol.layer;
                pending_name = name;
                have_pending = true;
            }
            if (esize > 0) pending.extents.push_back(Extent{vol.base_lba + elba, esize});
            pending.size += esize;
            if (flags & 0x80) continue;  // more extents follow
            img.files.push_back(std::move(pending));
            have_pending = false;
        }
        if (have_pending) {
            err = "unterminated multi-extent file '" + pending.path + "'";
            return false;
        }
        return true;
    }
};

bool parse_volume(IsoFile& f, uint64_t base, int layer, IsoImage& img, std::string& err) {
    uint8_t s[kSectorSize];
    if (!f.read_at((base + 16) * kSectorSize, s, sizeof s) || !is_pvd(s)) {
        err = "no ISO 9660 primary volume descriptor at sector " + std::to_string(base + 16);
        return false;
    }
    if (le16(s + 128) != kSectorSize) {
        err = "unsupported ISO 9660 logical block size " + std::to_string(le16(s + 128));
        return false;
    }
    IsoVolume vol;
    vol.layer = layer;
    vol.base_lba = base;
    vol.volume_blocks = le32(s + 80);
    vol.system_id = trim_field(s + 8, 32);
    vol.volume_id = trim_field(s + 40, 32);
    // Look for a UDF bridge (BEA01/NSR02/NSR03) after the ISO 9660 descriptor set.
    for (uint64_t i = base + 17; i < base + 32; ++i) {
        uint8_t d[kSectorSize];
        if (!f.read_at(i * kSectorSize, d, sizeof d)) break;
        if (std::memcmp(d + 1, "NSR02", 5) == 0 || std::memcmp(d + 1, "NSR03", 5) == 0) img.has_udf_bridge = true;
    }
    img.volumes.push_back(vol);
    const uint8_t* root = s + 156;
    Walker w{f, img, img.volumes.back(), err};
    return w.walk(uint64_t(le32(root + 2)) + root[1], le32(root + 10), "", 0);
}

}  // namespace

bool read_iso_tree(IsoFile& f, IsoImage& img, std::string& err) {
    img = IsoImage();
    if (f.size() < 17ull * kSectorSize) {
        err = "file is too small to be a disc image";
        return false;
    }
    if (!parse_volume(f, 0, 0, img, err)) return false;

    // Dual-layer: layer 1 begins 16 sectors before the end of the layer-0 volume space, so
    // its PVD lands at sector V. Probe the conventional spot first, then a small window in
    // case an authoring tool padded differently.
    uint64_t v = img.volumes[0].volume_blocks;
    if (f.size() > v * kSectorSize) {
        uint8_t s[kSectorSize];
        int64_t found = -1;
        for (int64_t d = 0; d <= 32 && found < 0; ++d) {
            for (int64_t sign : {1, -1}) {
                int64_t cand = int64_t(v) - 16 + sign * d;
                if (cand <= 0) continue;  // cand 0 would be layer 0 itself
                if (f.read_at(uint64_t(cand + 16) * kSectorSize, s, sizeof s) && is_pvd(s)) {
                    found = cand;
                    break;
                }
                if (d == 0) break;
            }
        }
        if (found < 0) {
            // Trailing data that isn't a second volume (padding in some dumps). The image
            // hash check decides whether that's acceptable.
            img.unparsed_tail_bytes = f.size() - v * kSectorSize;
            return true;
        }
        if (!parse_volume(f, uint64_t(found), 1, img, err)) return false;
    }
    return true;
}

bool read_entry(IsoFile& f, const IsoEntry& e, std::string& data, uint64_t max_size) {
    if (e.size > max_size) return false;
    data.clear();
    data.reserve(size_t(e.size));
    for (const Extent& x : e.extents) {
        std::string chunk(size_t(x.size), '\0');
        if (!f.read_at(x.lba * kSectorSize, &chunk[0], chunk.size())) return false;
        data += chunk;
    }
    return true;
}

}  // namespace rgx
