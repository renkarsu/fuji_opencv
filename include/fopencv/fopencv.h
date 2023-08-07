#ifndef FUJI_OPENCV_FOPENCV_H_
#define FUJI_OPENCV_FOPENCV_H_

// テンプレートは全てヘッダに書かないといけないことを考えると、本当は、
// テンプレート使わずに、普通にヘッダと実装分けて作った方が良くね。

// TODO:
// マクロ名を大文字にする
// 関数名をgoogleに合わせる
// getter(accessor)やsetter(mutator)は、変数名のように名前を付けてもかまいません。
// これらは、実際のメンバ変数と紐づけられますが、必須ではありません。
// たとえば、int count()とvoid set_count(int count)です。

// TODO: テンプレートヘッダライブラリにするのか否か
// DIFINITION:
// テンプレートを使用して作るライブラリ。宣言と実装は全てヘッダに書く。

//  クラス定義内でメンバ関数を定義した場合、暗黙にインライン関数となる

/*Google Coding Style
# Topic
- description
- define
- pros
- cons
- result

*/

/*宣言の順序
似ている宣言は1つにまとめ、パブリックな部分を先におきます。

クラスの定義は、通常はpublic:セクションから始め、protected:、private:と続けます。
空になるセクションは省略してください。

型と型エイリアス (typedef, using, enum, ネストされた構造体とクラス, friend 型)
静的定数
ファクトリ関数
コンストラクタと代入演算子
デストラクタ
その他すべての関数 (static と非static メンバ関数、friend関数)
データメンバ(静的と非静的)
*/

#include <iostream>
#include <vector>

// Detect/configure OS variables.
//
// Define 'cimg_OS' to: '0' for an unknown OS (will try to minize library
// dependencies).
//                      '1' for a Unix-like OS (Linux, Solaris, BSD, MacOSX,
//                      Irix, ...). '2' for Microsoft Windows. (auto-detection
//                      is performed if 'cimg_OS' is not set by the user).
#ifndef cimg_OS
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(linux) || \
    defined(__linux) || defined(__linux__) || defined(sun) ||                  \
    defined(__sun) || defined(BSD) || defined(__OpenBSD__) ||                  \
    defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) ||   \
    defined(sgi) || defined(__sgi) || defined(__OSX__) ||                      \
    defined(__MACOSX__) || defined(__APPLE__) || defined(__CYGWIN__)
#define cimg_OS 1
#elif defined(_MSC_VER) || defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32__) || defined(WIN64) || defined(_WIN64) ||  \
    defined(__WIN64__)
#define cimg_OS 2
#else
#define cimg_OS 0
#endif
#elif !(cimg_OS == 0 || cimg_OS == 1 || cimg_OS == 2)
#error CImg Library: Invalid configuration variable 'cimg_OS'.
#error (correct values are '0 = unknown OS', '1 = Unix-like OS', '2 = Microsoft Windows').
#endif

// Include OS-specific headers.
#if cimg_OS == 1
#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#elif cimg_OS == 2
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif
#include <io.h>
#include <process.h>
#include <shlobj.h>
enum { FALSE_WIN = 0 };
#endif

#if cimg_OS == 2

#define cimg_uint64 unsigned __int64
#define cimg_int64 __int64
#define cimg_ulong UINT_PTR
#define cimg_long INT_PTR
#ifdef _MSC_VER
#define cimg_fuint64 "%I64u"
#define cimg_fint64 "%I64d"
#else
#define cimg_fuint64 "%llu"
#define cimg_fint64 "%lld"
#endif

#else

#if UINTPTR_MAX == 0xffffffff || defined(__arm__) || defined(_M_ARM) || \
    ((ULONG_MAX) == (UINT_MAX))
#define cimg_uint64 unsigned long long
#define cimg_int64 long long
#define cimg_fuint64 "%llu"
#define cimg_fint64 "%lld"
#else
#define cimg_uint64 unsigned long
#define cimg_int64 long
#define cimg_fuint64 "%lu"
#define cimg_fint64 "%ld"
#endif

#if defined(__arm__) || defined(_M_ARM)
#define cimg_ulong unsigned long long
#define cimg_long long long
#else
#define cimg_ulong unsigned long
#define cimg_long long
#endif

#endif

#ifndef cimg_max_buf_size
#if UINTPTR_MAX == 0xffffffff
#define cimg_max_buf_size ((cimg_ulong)3 * 1024 * 1024 * 1024)
#else
#define cimg_max_buf_size ((cimg_ulong)16 * 1024 * 1024 * 1024)
#endif
#endif

// 通常はRGB, RGB, ..., の目盛りレイアウトだが、CIMGではRRR..., GGG...,
// BBB....としている。
class FOpencv {
 public:
  FOpencv();
  ~FOpencv();

  // Return 'dx*dy*dz*dc' as a 'size_t' and check no overflow occurs.
  static size_t safe_size(const unsigned int dx, const unsigned int dy,
                          const unsigned int dz, const unsigned int dc);

  //! Return display width.
  /**
     \note The width of the display (i.e. the width of the pixel data buffer
  associated to the CImgDisplay instance) may be different from the actual width
  of the associated window.
  **/
  int width() const { return (int)width_; }

  //! Return display height.
  /**
     \note The height of the display (i.e. the height of the pixel data buffer
  associated to the CImgDisplay instance) may be different from the actual
  height of the associated window.
  **/
  int height() const { return (int)height_; }

 private:
  // const uint width = tmp_uintとかしなくても
  // プライベート変数にして、getterとsetterでアクセスすればよい？
  // 本家の実装では、spectrumという変数名
  unsigned int width_, height_, depth_, spectrum_;
  bool is_shared_;
  unsigned *data_;
};

#endif  // FUJI_OPENCV_FOPENCV_H_
