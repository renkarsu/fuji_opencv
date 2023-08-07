#include "fimg.hpp"

int main() {
  //   FImg<unsigned char> image();は関数宣言になる。
  // 画像の幅と高さを指定してImageクラスのインスタンスを作成
  FImg<unsigned char> image;

  // 画像のピクセル値を設定して表示
  for (int y = 0; y < image.height(); y++) {
    for (int x = 0; x < image.width(); x++) {
      // image.setPixel(x, y, x + y);
      // std::cout << image.getPixel(x, y) << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
