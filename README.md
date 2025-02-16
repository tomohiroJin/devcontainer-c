# devcontainer-c

`devcontainer-c` は、Visual Studio Code (VS Code) 上で C++ の開発環境を構築するためのリポジトリです。  
このリポジトリには、Dev Container 機能を使用して、CMake、Google Test、Boost などのツールやライブラリが事前に設定されています。

## **特徴**

- **CMake のサポート**: ビルドシステムとして CMake を使用し、柔軟なビルド構成を提供します。
- **Google Test の統合**: ユニットテストフレームワークとして Google Test を組み込み、テスト駆動開発をサポートします。
- **Boost ライブラリの利用**: 高機能な C++ ライブラリである Boost をインストール済みで、さまざまな機能を簡単に利用できます。
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
make test TEST=test_fizzbuzz  # FizzBuzz のテストのみ実行
make test TEST=test_factory   # Factory のテストのみ実行
```

---

## **依存関係**

このプロジェクトは、以下のツールやライブラリに依存しています。

- [CMake](https://cmake.org/): ビルドシステム
- [Google Test](https://github.com/google/googletest): ユニットテストフレームワーク
- [Boost](https://www.boost.org/): C++ ライブラリ

これらは、Dev Container 内で自動的にインストールされます。

---

## **ライセンス**

このプロジェクトは、MIT ライセンスの下で公開されています。詳細は、`LICENSE` ファイルをご覧ください。
