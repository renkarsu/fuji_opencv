#include <process.h>
#include <windows.h>

#include <iostream>
#include <vector>

int main() {
  std::cout << "Start: \"fopencv-main.exe\".\n";
  std::cerr << "Start: \"fopencv-main.exe\".\n";

  // LPCTSTR a;
  // LPCWSTR b;
  // const WCHAR *bb;
  // const wchar_t *bbb;
  // const TCHAR *c;
  // HANDLE k;

  std::cout << "End:   \"fopencv-main.exe\".\n";
  std::cerr << "End:   \"fopencv-main.exe\".\n";
  // TODO: 
  // __FILE__から、"\"が最後に出てくる場所を探して、
  // その地点から後ろを持ってくれば、fopencv-main.cを確保できる。
  // そこから、fopencv-main.cをfopencv-main.exeに置換すれば、
  // fopencv-main.exeだけ確保できる。
  // std::cout << __FILE__ << std::endl;
  return 0;
}
