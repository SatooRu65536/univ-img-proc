# 画像処理及び演習
画像処理及び演習 で使用するリポジトリです

## 環境構築
### OpenCV のインストール
```shell
brew install opencv
```

### VSCode の設定
拡張機能　[`C/C++`](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) をインストール

### 設定ファイルの作成
`cmd + shift + p` から `C/C++: 構成の編集(JSON)` を選択すると `.vscode/c_cpp_properties.json` が作成される

includePath に `/opt/homebrew/**` を追加する
```diff
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "${workspaceFolder}/**",
+                "/opt/homebrew/**"
            ],
            "defines": [],
            "macFrameworkPath": [
                "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
            ],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-arm64"
        }
    ],
    "version": 4
}

```

### コンパイル
```shell
g++ [filePath] -O3 -std=c++11 `pkg-config --cflags --libs opencv4`
```

### 実行
```shell
./a.out
```

まとめてコンパイル&実行することもできます
```shell
g++ -O3 $1 -std=c++11 `pkg-config --cflags --libs opencv4` && ./a.out
```

## おまけ
### エイリアスを設定する
`~/.zshrc` を開いて以下を追加する
```zsh
alias gpp='(){g++ -O3 $1 -std=c++11 `pkg-config --cflags --libs opencv4` && ./a.out}'
```

### 実行
楽にコンパイル&実行することができます
```shell
gpp [filePath]
```
