#include "fopencv/fopencv.h"

FOpencv::FOpencv()
    : width_(0),
      height_(0),
      depth_(0),
      spectrum_(0),
      is_shared_(false),
      data_(0) {}

FOpencv::~FOpencv() {
  if (!is_shared_) delete[] data_;
}

// static メンバの実装では、static付けなくてよい
size_t FOpencv::safe_size(const unsigned int dx, const unsigned int dy,
                          const unsigned int dz, const unsigned int dc) {
  if (!(dx && dy && dz && dc)) return 0;
  size_t siz = (size_t)dx, osiz = siz;
  if ((dy == 1 || (siz *= dy) > osiz) &&
      ((osiz = siz), dz == 1 || (siz *= dz) > osiz) &&
      ((osiz = siz), dc == 1 || (siz *= dc) > osiz) &&
      ((osiz = siz),
       sizeof(unsigned) == 1 || (siz * sizeof(unsigned)) > osiz)) {
    if (siz > cimg_max_buf_size) {
      std::cout << "exceeds maximum allowed buffer size.\n";
    }
    return siz;
  }

  return 0;
}
