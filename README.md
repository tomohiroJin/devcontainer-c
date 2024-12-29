# devcontainer-c

`devcontainer-c` は、Visual Studio Code (VS Code) 上で C 言語の開発環境を構築するためのリポジトリです。このリポジトリには、Dev Container 機能を使用して、CMake、Google Test、Boost などのツールやライブラリが事前に設定されています。

## 特徴

- **CMake のサポート**: ビルドシステムとして CMake を使用し、柔軟なビルド構成を提供します。
- **Google Test の統合**: ユニットテストフレームワークとして Google Test を組み込み、テスト駆動開発をサポートします。
- **Boost ライブラリの利用**: 高機能な C++ ライブラリである Boost をインストール済みで、さまざまな機能を簡単に利用できます。
- **VS Code 拡張機能のプリインストール**: C/C++ 開発に役立つ拡張機能が事前にインストールされています。

## セットアップ手順

1. **リポジトリのクローン**:

   ```bash
   git clone https://github.com/tomohiroJin/devcontainer-c.git
   cd devcontainer-c
   ```

2. **VS Code でリポジトリを開く**:

   VS Code を起動し、`devcontainer-c` ディレクトリを開きます。

3. **Dev Container のビルドと起動**:

   VS Code のコマンドパレット（`Ctrl+Shift+P` または `Cmd+Shift+P`）を開き、「Dev Containers: Reopen in Container」を選択します。これにより、定義された開発環境が構築され、コンテナ内でプロジェクトが開かれます。

## 使用方法

- **ビルド**:

  ターミナルで以下のコマンドを実行して、プロジェクトをビルドします。

  ```bash
  make
  ```

- **クリーンビルド**:

  以前のビルド成果物を削除し、再度ビルドを行う場合は、以下のコマンドを実行します。

  ```bash
  make clean
  make
  ```

- **テストの実行**:

  ビルド後、以下のコマンドでテストを実行できます。

  ```bash
  make test
  ```

- **クリーンビルドしてテストの実行**:

  クリーン、ビルド、テストの順で実行できます。

  ```bash
  make bt
  ```

## 依存関係

このプロジェクトは、以下のツールやライブラリに依存しています。

- [CMake](https://cmake.org/): ビルドシステム
- [Google Test](https://github.com/google/googletest): ユニットテストフレームワーク
- [Boost](https://www.boost.org/): C++ ライブラリ

これらは、Dev Container 内で自動的にインストールされます。

## ライセンス

このプロジェクトは、MIT ライセンスの下で公開されています。詳細は、`LICENSE` ファイルをご覧ください。
