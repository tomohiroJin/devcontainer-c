# 開発環境の保守

調査日: 2026-11-05 (Asia/Tokyo)。対象: Issue #6、開始時 HEAD `58239e664b19136f31a8eb557b8bdf8db1f22be5`。

## 更新方針

| 対象 | 変更前 | 採用 | 理由・公式情報 |
| --- | --- | --- | --- |
| Debian | bookworm | trixie-slim (Debian 13) | 安定版。通常サポート 2028-08-09、LTS 2030-06-30。[release](https://www.debian.org/releases/trixie/) |
| GCC | 12 | 14.2 系 | [trixie gcc](https://packages.debian.org/trixie/gcc) |
| LLVM | 16 | 19 系 | [clang](https://packages.debian.org/trixie/clang) / clang-format / clang-tidy / lldb を同じ配布元に統一 |
| CMake | bookworm版 | 3.31.6 系 | [cmake](https://packages.debian.org/trixie/cmake) |
| GoogleTest | apt + upstream 1.15.2 | Debian 1.16.0-1 | [libgtest-dev](https://packages.debian.org/trixie/libgtest-dev)。upstream 最新 release は調査時 v1.18.0。重複導入を廃止し Debian パッケージの修正提供を利用 |
| Boost | bookworm版の全モジュール | 1.83 系のヘッダー | [libboost-dev](https://packages.debian.org/trixie/libboost-dev) |
| OpenSSL | bookworm版 | 3.5 系 | [libssl-dev](https://packages.debian.org/trixie/libssl-dev) の security 更新を適用 |
| cppcheck | bookworm版 | 2.17.1 系 | [cppcheck](https://packages.debian.org/trixie/cppcheck) |
| Python 補助ツール | system pip、下限制約 | 削除 | 利用設定を外し、clang-tidy/cppcheck に集約。PEP 668 回避と未固定の間接依存を解消 |
| Dev Container Features | common-utils:2 / git:1 | 削除 | ユーザー作成と git を Dockerfile で提供し二重インストールを回避 |

Boost は現行コードがバイナリライブラリを利用していないため libboost-dev に絞り、MPI/Python/OpenSSH 等の不要な依存を外した。バイナリモジュールが必要になったときだけ対応する libboost-*-dev を追加する。

C++20 は学習コードの契約として維持。各ツールの upstream 最新版に無条件で揃えず、Debian stable の互換性とセキュリティバックポートを利用する。次回見直しは毎週の定期 CI と Dependabot、および次の Debian stable 公開時。apt とベースタグはセキュリティ更新を取り込むため可変。厳密に同じ依存は CI artifact のイメージID・dpkg一覧から追跡する。

## VS Code

必須は Microsoft の [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) と [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)、共通整形ルール用の [EditorConfig](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig)。Dev Container と extensions.json は同じ推奨一覧。CMake configurationProvider と compile_commands.json を利用し、固定 includePath/アーキテクチャ指定を削除。補完・デバッグ・clang-format・clang-tidy は C/C++ 拡張に集約する。cpptools pack/個別指定の重複、IntelliCode、flylint、別 formatter を外した。clangd と併用しない。

Marketplace の公開・validated フラグと最終更新日も確認済み（C/C++: 2026-11-02、CMake Tools: 2026-10-19）。

GitLens、Live Share、日本語パック等の利便性拡張は利用者が任意に導入する。拡張の自動最新版インストールは Dev Containers の標準動作であり、特定バージョンの固定はしていない。

## 再現と監査

VS Code の Dev Containers: Rebuild and Reopen in Container を実行。postCreateCommand は `bash scripts/verify-env.sh` を実行し、GCC と Clang の configure/build/CTest を検証する。手動確認では CMake configure 後の補完・定義ジャンプ、ブレークポイント、保存時整形（.clang-format）、clang-tidy 診断を確認する。

CI は push/PR/手動/毎週にイメージをクリーンビルドし、両コンパイラのテストと Trivy の OS/言語パッケージ監査を実行する。全深刻度の JSON、イメージ情報、dpkg一覧を artifact 保存する。修正版のある HIGH/CRITICAL は失敗にし、修正未提供も全件レポートに残す。残件は CVE・影響・回避策・担当・期限を既存 Issue #6 と security-status.md で追跡する。CI の成功を確認するまで脆弱性ゼロを保証しない。

ローカル例:

```sh
docker build --pull -t devcontainer-c:audit .devcontainer
docker run --rm -v "$PWD:/workspace" -w /workspace devcontainer-c:audit bash scripts/verify-env.sh
trivy image --scanners vuln --format json --output trivy.json devcontainer-c:audit
trivy image --scanners vuln --severity HIGH,CRITICAL --ignore-unfixed --exit-code 1 devcontainer-c:audit
```

ビルド proxy のカスタム CA が必要な環境では `--secret id=proxy_ca,src=/path/to/combined-ca.pem` を渡す。証明書はイメージに保存しない。

CI Actions は公式 release の commit SHA に固定: [checkout v7.0.1](https://github.com/actions/checkout/releases/tag/v7.0.1)、[upload-artifact v7.0.2](https://github.com/actions/upload-artifact/releases/tag/v7.0.2)、[trivy-action v0.36.0](https://github.com/aquasecurity/trivy-action/releases/tag/v0.36.0)。Trivy scanner は検証と同じ v0.76.2 を明示指定し、毎週の保守時に scanner 自体の更新も確認する。新規導入時に GitHub API の release/tag で確認した。GoogleTest の upstream 比較元は [latest release](https://github.com/google/googletest/releases/latest)。

実行済み検証・最終イメージの監査結果・残件は [security-status.md](security-status.md) に記録。
