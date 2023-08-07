#include <iostream>
#include <vector>

class Image {
 public:
  Image(int width, int height) : width(width), height(height) {
    // 画像データを初期化（すべてのピクセルを0に設定）
    data.resize(width, std::vector<int>(height, 0));
  }

  // ピクセルの値を設定する関数
  void setPixel(int x, int y, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
      data[x][y] = value;
    }
  }

  // ピクセルの値を取得する関数
  int getPixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
      return data[x][y];
    }
    // 範囲外の場合は0を返す（デフォルト値）
    return 0;
  }

  // 画像の幅を取得する関数
  int getWidth() const { return width; }

  // 画像の高さを取得する関数
  int getHeight() const { return height; }

 private:
  int width;                           // 画像の幅
  int height;                          // 画像の高さ
  std::vector<std::vector<int>> data;  // 画像データを格納する2次元配列
};

int main() {
  // 画像の幅と高さを指定してImageクラスのインスタンスを作成
  Image image(10, 8);

  // 画像のピクセル値を設定して表示
  for (int y = 0; y < image.getHeight(); y++) {
    for (int x = 0; x < image.getWidth(); x++) {
      image.setPixel(x, y, x + y);
      std::cout << image.getPixel(x, y) << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
