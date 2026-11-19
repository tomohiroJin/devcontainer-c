# devcontainer-c

`devcontainer-c` は、Visual Studio Code (VS Code) 上で C++ の開発環境を構築するためのリポジトリです。  
このリポジトリには、Dev Container 機能を使用して、CMake、Google Test、Boost などのツールやライブラリが事前に設定されています。

## **特徴**

- **Debian trixie ベース**: OpenSSL 3.x を含むDebian 安定版のパッケージ群で構成。
- **C++20 対応ツールチェーン**: GCC 14 / Clang 19 をプリインストール。
- **CMake のサポート**: ビルドシステムとして CMake (3.20 以上) を使用し、柔軟なビルド構成を提供します。
- **Google Test の統合**: ユニットテストフレームワーク（Debian の libgtest-dev 1.16 系）を組み込み、テスト駆動開発をサポートします。
- **Boost ライブラリの利用**: Boost のヘッダーオンリー機能を libboost-dev で利用できます。Regex / Filesystem などバイナリが必要な機能は、対応する libboost-*-dev の追加が必要です。
- **clang-format / clang-tidy 同梱**: フォーマット・静的解析も標準で実行可能。
- **非 root ユーザー (`vscode`) で起動**: devcontainer のベストプラクティスに準拠。`sudo` は NOPASSWD で利用可能。
- **VS Code 拡張機能のプリインストール**: C/C++ 開発に役立つ拡張機能が事前にインストールされています。

---

## **セットアップ手順**

### **1. リポジトリのクローン**

```bash
git clone https://github.com/tomohiroJin/devcontainer-c.git
cd devcontainer-c
```

### **2. VS Code でリポジトリを開く**

VS Code を起動し、`devcontainer-c` ディレクトリを開きます。

### **3. Dev Container のビルドと起動**

VS Code のコマンドパレット（`Ctrl+Shift+P` または `Cmd+Shift+P`）を開き、「Dev Containers: Reopen in Container」を選択します。  
これにより、定義された開発環境が構築され、コンテナ内でプロジェクトが開かれます。

---

## **使用方法**

### **🔹 ビルド**

以下のコマンドでプロジェクトをビルドできます。

```bash
make build
```

### **🔹 並列ビルド（高速化）**

```bash
make -j4 build  # CPU に応じて `-j4` を `-j$(nproc)` に変更可能
```

### **🔹 クリーンビルド**

以前のビルド成果物を削除し、再ビルドする場合は以下を実行してください。

```bash
make clean
make build
```

### **🔹 全テストの実行**

```bash
make test
```

### **🔹 特定のテストのみ実行**

特定のテストを実行したい場合は、以下のように `TEST` 変数を指定します。

```bash
make test TEST=FizzBuzzTest  # FizzBuzz のテストのみ実行
make test TEST='Factory.*PatternTest'   # Factory のテストのみ実行
```

---

## **依存関係**

このプロジェクトは、以下のツールやライブラリに依存しています。

- [CMake](https://cmake.org/) 3.20 以上: ビルドシステム
- [Google Test](https://github.com/google/googletest) Debian 1.16 系: ユニットテストフレームワーク
- [Boost](https://www.boost.org/): ヘッダーオンリー機能（libboost-dev）
- GCC 14 / Clang 19 (C++20 対応)
- clang-format / clang-tidy / cppcheck（解析系ツール）

これらは、Dev Container 内で自動的にインストールされます。

---

## **ライセンス**

このプロジェクトは、MIT ライセンスの下で公開されています。詳細は、`LICENSE` ファイルをご覧ください。

## 保守と検証

更新理由・調査元・監査手順は [docs/maintenance.md](docs/maintenance.md) を参照してください。
コンテナ作成時は `bash scripts/show-versions.sh` でツールの版だけを確認します。
`bash scripts/verify-env.sh` で GCC / Clang の両方をビルド・テストします（手動・CI用）。意図的に失敗する学習用テストがあってもコンテナ作成は妨げません。
