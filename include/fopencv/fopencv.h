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

/**Detect/configure OS variables.

Define 'cimg_OS' to: '0' for an unknown OS (will try to minize library
dependencies).
'1' for a Unix-like OS (Linux, Solaris, BSD, MacOSX, Irix, ...).
'2' for Microsoft Windows.
(auto-detection is performed if 'cimg_OS' is not set by the user).
*/
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

/**
  \par Image structure

  The \c CImg<T> structure contains \e six fields:
  - \c width_ defines the number of \a columns of the image (size along the
    X-axis).
  - \c height_ defines the number of \a rows of the image (size along the
    Y-axis).
  - \c depth_ defines the number of \a slices of the image (size along the
    Z-axis).
  - \c spectrum_ defines the number of \a channels of the image (size along the
    C-axis).
  - \c data_ defines a \a pointer to the \a pixel \a data (of type \c T).
  - \c is_shared_ is a boolean that tells if the memory buffer \c data is shared
    with another image.

  \par Image declaration and construction

  Declaring an image can be done by using one of the several available
  constructors. Here is a list of the most used:

  - Construct images from arbitrary dimensions:
  - <tt>CImg<char> img;</tt> declares an empty image.
  - <tt>CImg<unsigned char> img(128,128);</tt> declares a 128x128
    greyscale image with \c unsigned \c char pixel values.
  - <tt>CImg<double> img(3,3);</tt> declares a 3x3 matrix with \c double
    coefficients.
  - <tt>CImg<unsigned char> img(256,256,1,3);</tt> declares a 256x256x1x3
    (color) image (colors are stored as an image with three channels).
  - <tt>CImg<double> img(128,128,128);</tt> declares a 128x128x128
    volumetric and greyscale image (with \c double pixel values).
  - <tt>CImg<> img(128,128,128,3);</tt> declares a 128x128x128 volumetric
    color image (with \c float pixels, which is the default value of the
    template parameter \c T).
  - \b Note: images pixels are <b>not automatically initialized to 0</b>.
    You may use the function \c fill() to do it, or use the specific constructor
    taking 5 parameters like this: <tt>CImg<> img(128,128,128,3,0);</tt>
    declares a 128x128x128 volumetric color image with all pixel values to 0.

  - Construct images from filenames:
  - <tt>CImg<unsigned char> img("image.jpg");</tt> reads a JPEG color
    image from the file "image.jpg".
  - <tt>CImg<float> img("analyze.hdr");</tt> reads a volumetric image
    (ANALYZE7.5 format) from the file "analyze.hdr".
  - \b Note: You need to install <a
    href="http://www.imagemagick.org">ImageMagick</a> to be able to read common
    compressed image formats (JPG,PNG, ...) (See \ref cimg_files_io).

  - Construct images from C-style arrays:
  - <tt>CImg<int> img(data_buffer,256,256);</tt> constructs a 256x256
    greyscale image from a \c int* buffer \c data_buffer (of size
    256x256=65536).
  - <tt>CImg<unsigned char> img(data_buffer,256,256,1,3);</tt> constructs
    a 256x256 color image from a \c unsigned \c char* buffer \c data_buffer
    (where R,G,B channels follow each others).

  The complete list of constructors can be found <a
  href="#constructors">here</a>.
 */

// 通常はRGB, RGB, ..., の目盛りレイアウトだが、CIMGではRRR..., GGG...,
// BBB....としている。
class FOpencv {
 public:
  //! Simple iterator type, to loop through each pixel value of an image
  //! instance.
  /**
     \note
     - The \c CImg<T>::iterator type is defined to be a <tt>T*</tt>.
     - You will seldom have to use iterators in %CImg, most classical operations
       being achieved (often in a faster way) using methods of \c CImg<T>.
     \par Example
     \code
     // Load image from file
     CImg<float> img("reference.jpg");
     // Set all pixels to '0', with a CImg iterator.
     for (CImg<float>::iterator it = img.begin(), it<img.end(); ++it) *it = 0;
     // Do the same with a built-in method
     img.fill(0);
     \endcode
 **/
  typedef unsigned* iterator;

  //! Simple const iterator type, to loop through each pixel value of a \c const
  //! image instance.
  /**
     \note
     - The \c CImg<T>::const_iterator type is defined to be a \c const \c T*.
     - You will seldom have to use iterators in %CImg, most classical operations
       being achieved (often in a faster way) using methods of \c CImg<T>.
     \par Example
     \code
     // Load image from file float sum = 0;
     const CImg<float> img("reference.jpg");
     // Compute sum of all pixel values, with a CImg iterator.
     for (CImg<float>::iterator it = img.begin(), it<img.end(); ++it) sum+=*it;
     // Do the same with a built-in method
     const float sum2 = img.sum();
     \endcode
  **/
  typedef const unsigned* const_iterator;

  //! Pixel value type.
  /**
     Refer to the type of the pixel values of an image instance.
     \note
     - The \c CImg<T>::value_type type of a \c CImg<T> is defined to be a \c T.
     - \c CImg<T>::value_type is actually not used in %CImg methods.
       It has been mainly defined for compatibility with STL naming conventions.
  **/
  typedef unsigned value_type;

  FOpencv();
  ~FOpencv();

  // Return 'dx*dy*dz*dc' as a 'size_t' and check no overflow occurs.
  static size_t safe_size(const unsigned dx, const unsigned dy,
                          const unsigned dz, const unsigned dc);

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

  // NOTE: Instance Characteristics in CImg<T>.

  //@}
  //-------------------------------------
  //
  //! \name Instance Characteristics
  //@{
  //-------------------------------------

  //! Return the type of image pixel values as a C string.
  /**
    Return a \c char* string containing the usual type name of the image pixel
    values (i.e. a stringified version of the template parameter \c T).
    \note
    - The returned string does not contain any spaces.
    - If the pixel type \c T does not correspond to a registered type, the
      string <tt>"unknown"</tt> is returned.
  **/
  static const char* pixel_type() { return cimg::type<T>::string(); }

  //! Return the number of image columns.
  /**
    Return the image width, i.e. the image dimension along the X-axis.
    \note
    - The width() of an empty image is equal to \c 0.
    - width() is typically equal to \c 1 when considering images as \e vectors
      for matrix calculations.
    - width() returns an \c int, although the image width is internally stored
      as an \c unsigned \c int.
      Using an \c int is safer and prevents arithmetic traps possibly 
      encountered when doing calculations involving \c unsigned \c int 
      variables. 
      Access to the initial \c unsigned \c int variable is possible
      (though not recommended) by <tt>(*this)._width</tt>.
  **/
  int width() const { return (int)width_; }

  //! Return the number of image rows.
  /**
    Return the image height, i.e. the image dimension along the Y-axis.
    \note
    - The height() of an empty image is equal to \c 0.
    - height() returns an \c int, although the image height is internally
      stored as an \c unsigned \c int. 
      Using an \c int is safer and prevents arithmetic traps possibly 
      encountered when doing calculations involving \c unsigned \c int 
      variables. 
      Access to the initial \c unsigned \c int variable is possible 
      (though not recommended) by <tt>(*this)._height</tt>.
  **/
  int height() const { return (int)height_; }

  //! Return the number of image slices.
  /**
    Return the image depth, i.e. the image dimension along the Z-axis.
    \note
    - The depth() of an empty image is equal to \c 0.
    - depth() is typically equal to \c 1 when considering usual 2D images.
      When depth()\c > \c 1, the image is said to be \e volumetric.
    - depth() returns an \c int, although the image depth is internally stored
      as an \c unsigned \c int.
      Using an \c int is safer and prevents arithmetic traps possibly
      encountered when doing calculations involving \c unsigned \c
      int variables.
      Access to the initial \c unsigned \c int variable is possible
      (though not recommended) by <tt>(*this)._depth</tt>.
  **/
  int depth() const { return (int)depth_; }

  //! Return the number of image channels.
  /**
    Return the number of image channels, i.e. the image dimension along the
    C-axis.
    \note
    - The spectrum() of an empty image is equal to \c 0.
    - spectrum() is typically equal to \c 1 when considering scalar-valued
      images, to \c 3 for RGB-coded color images, and to \c 4 for RGBA-coded
      color images (with alpha-channel).
      The number of channels of an image instance is not limited.
      The meaning of the pixel values is not linked up to the number of channels
      (e.g. a 4-channel image may indifferently stands for a RGBA or CMYK color
      image).
    - spectrum() returns an \c int, although the image spectrum is internally
      stored as an \c unsigned \c int.
      Using an \c int is safer and prevents arithmetic traps possibly
      encountered when doing calculations involving \c unsigned \c int
      variables.
      Access to the initial \c unsigned \c int variable is possible
      (though not recommended) by <tt>(*this)._spectrum</tt>.
  **/
  int spectrum() const { return (int)spectrum_; }

  //! Return the total number of pixel values.
  /**
    Return <tt>width()*\ref height()*\ref depth()*\ref spectrum()</tt>,
    i.e. the total number of values of type \c T in the pixel buffer of the
    image instance.
    \note
    - The size() of an empty image is equal to \c 0.
    - The allocated memory size for a pixel buffer of a non-shared \c CImg<T>
      instance is equal to <tt>size()*sizeof(T)</tt>.
      \par Example
      \code
      // Construct new 100x100 color
      const CImg<float> img(100,100,1,3);
      // Test succeeds
      image if (img.size()==30000)
      std::printf("Pixel buffer uses %lu bytes",
                   img.size()*sizeof(float));
     \endcode
  **/
  ulongT size() const { return (ulongT)width_ * height_ * depth_ * spectrum_; }

  //! Return a pointer to the first pixel value.
  /**
    Return a \c T*, or a \c const \c T* pointer to the first value in the pixel
    buffer of the image instance, whether the instance is \c const or not.
    \note
    - The data() of an empty image is equal to \c 0 (null pointer).
    - The allocated pixel buffer for the image instance starts from \c data()
      and goes to <tt>data()+\ref size() - 1</tt> (included).
    - To get the pointer to one particular location of the pixel buffer, use
      data(unsigned int,unsigned int,unsigned int,unsigned int) instead.
  **/
  unsigned* data() { return data_; }

  //! Return a pointer to the first pixel value \const.
  const unsigned* data() const { return data_; }

 private:
  // const uint width = tmp_uintとかしなくても
  // プライベート変数にして、getterとsetterでアクセスすればよい？
  // 本家の実装では、spectrumという変数名
  unsigned width_, height_, depth_, spectrum_;
  bool is_shared_;
  unsigned* data_;
};

#endif  // FUJI_OPENCV_FOPENCV_H_
