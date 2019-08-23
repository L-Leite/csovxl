# csovxl

A command line tool to decompresses Voxel configuration files (with '.vxl' extension) used by Nexon's Counter-Strike Online (CSO).

The Voxel ('.vxl') files contain CSO's Studio game mode data - such as voxels information and Lua scripts.

Tested on:
- GNU/Linux - GCC 9.1.0 (64 bits)
- Windows 10 - MinGW 9.2.0 (64 bits)

## Usage

You can decompress the Voxel file with:

```sh
./csovxl 01553060153843999001.vxl
```

Where `01553060153843999001.vxl` is the Voxel file.

After running the program, a file named `01553060153843999001.dec_data` will be created with the decompressed Voxel file's data.

## Libraries used

csovxl uses the following libraries:

- [GSL Lite](https://github.com/martinmoene/gsl-lite), MIT license.
- [LZMA SDK](https://www.7-zip.org/sdk.html), Public domain.

## License

csovxl is distributed under the GNU GPLv3 license.
