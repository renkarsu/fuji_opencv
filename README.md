# fuji_opencv

* 本リポジトリでは、src/fopencv.ccとinclude/fopencv/fopencv.hで構成されるライブラリを提供する
* sampleフォルダのfopencv-main.ccは、ライブラリを使用した場合の例を提供する

* ヘッダファイルは常にプリコンパイルしてincludeフォルダに置くこと

* テンプレートヘッダライブラリであるref/cimg.hppを見ながら、fopencv.ccとfopen.hに適用していく。ただし、cimg.hppの難しい設計で作るのは大変かつ無駄も多いので、"だえう"の画像処理解説サイトやref/daeu-main.ccを参考に、自分なりの簡易版cimg.hppを設計していく。

* 11702: Def of the CImg

[]constructor（cimgクラス内での型宣言の後）
[]method for construction(12613行目から)
- e.g. clear()
[]operator(12613行目の直前辺りと12963行目から, 23163)
[]Instance Characteristics method(14359行目から)
- e.g. height()
[]Instance Checking
- e.g. is_shared()

* 17175-23161は飛ばす

[]Math???: 23191
[]Vector / Matrix Operations: 30250
[]Value Manipulation: 32248
[] Color Base Management: 34495
[]Geometric / Spatial Manipulation: 35434
[]Filtering / Transforms: 39669

* skip

[]Data Input: 53090
[]Data Output: 57583

* 61072: CImg構造体のdef終了
