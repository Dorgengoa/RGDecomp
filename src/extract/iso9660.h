// SPDX-License-Identifier: CC0-1.0
// Read-only ISO 9660 reader for PS2 DVD images, including dual-layer (DVD9) discs.
//
// A PS2 DVD9 image is two ISO 9660 volumes back to back: layer 0 starts at sector 0, and
// layer 1 starts at (layer-0 volume space size - 16) with its own volume descriptors, so
// its primary volume descriptor sits exactly at the layer-0 volume size. Extents inside
// the layer-1 volume are relative to the layer-1 start. Both layers also carry a UDF 1.02
// bridge, which this reader ignores: on Rogue Galaxy the UDF allocation descriptors
// overflow for files larger than 1 GiB (30-bit extent length), so ISO 9660 is the
// authoritative view.
#pragma once

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

namespace rgx {

constexpr uint32_t kSectorSize = 2048;

// Large-file-safe read-only file handle (64-bit offsets on every platform).
class IsoFile {
public:
    IsoFile() = default;
    ~IsoFile();
    IsoFile(const IsoFile&) = delete;
    IsoFile& operator=(const IsoFile&) = delete;

    bool open(const std::filesystem::path& p, std::string& err);
    uint64_t size() const { return size_; }
    // Reads exactly n bytes at off; false on short read or I/O error.
    bool read_at(uint64_t off, void* dst, size_t n);
    bool seek(uint64_t off);
    // Sequential read; returns bytes read (short only at EOF or error).
    size_t read(void* dst, size_t n);
    bool error() const;

private:
    std::FILE* f_ = nullptr;
    uint64_t size_ = 0;
};

struct Extent {
    uint64_t lba = 0;   // absolute sector on the disc image
    uint64_t size = 0;  // bytes
};

struct IsoEntry {
    std::string path;  // normalised: "/DIR/NAME.EXT", no ";1" version suffix
    uint64_t size = 0;
    std::vector<Extent> extents;  // in file order; >1 only for ISO 9660 multi-extent files
    int layer = 0;
};

struct IsoVolume {
    int layer = 0;
    uint64_t base_lba = 0;       // absolute sector where this volume's sector 0 is
    uint64_t volume_blocks = 0;  // volume space size from the PVD
    std::string system_id;
    std::string volume_id;
};

struct IsoImage {
    std::vector<IsoVolume> volumes;
    std::vector<IsoEntry> files;        // all layers, in directory order, layer 0 first
    std::vector<std::string> dirs;      // normalised directory paths, all layers
    bool has_udf_bridge = false;
    uint64_t unparsed_tail_bytes = 0;  // data past the last volume that isn't a volume
};

// Parses every ISO 9660 volume in the image. Returns false with a message on malformed data.
bool read_iso_tree(IsoFile& f, IsoImage& out, std::string& err);

// Reads a (small) file's full contents.
bool read_entry(IsoFile& f, const IsoEntry& e, std::string& data, uint64_t max_size = 1 << 20);

}  // namespace rgx
