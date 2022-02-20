# l2bin-wrapper

![Apache-2.0 License](https://img.shields.io/github/license/savormix/l2bin-wrapper)
![MSVC C++](https://img.shields.io/github/languages/top/savormix/l2bin-wrapper)
![Lines of code](https://img.shields.io/tokei/lines/github/savormix/l2bin-wrapper)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/savormix/l2bin-wrapper)

An executable file to replace L2.bin with in order to control command line arguments passed by a region-specific launcher.

## Runtime Dependencies

[Visual C++ Redist](https://aka.ms/vs/17/release/vc_redist.x86.exe)

## Usage

- Rename original `L2.bin` to `L2.exe`
- Add the custom `L2.bin`
- Check `FileInfoMap-*.dat`, ensure that the line starting with `system\L2.bin:` ends with `:0`
- _Optional:_ Add plain text `L2_.ini` (if using l2.bin with l2.ini override)
- _Optional:_ Add plain text `User_.ini` (if using l2.bin with user.ini override)
- Open the launcher, login, start
