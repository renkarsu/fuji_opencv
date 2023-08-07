@rem BATの基本１
@rem https://language-and-engineering.hatenablog.jp/entry/20130502/PatternsOfMSDOSorBAT
@rem BATの基本２
@rem https://qiita.com/tomotagwork/items/5b9e08f28d5925d96b5f
@rem このファイルの生成元
@rem https://sun0range.com/information-technology/delete-file-and-directory-bat
@rem 【設定定義箇所↓】の後の改行は、なぜか入れないとremが途中で停止する

@rem 文字コード：(UTF8->65001, Shift-JIS->932)
chcp 65001

echo off
setlocal enabledelayedexpansion
cd %~dp0

rem 【設定定義箇所↓】

mkdir bin
mkdir include
mkdir src
mkdir INPUT
mkdir TEMP
mkdir OUTPUT
