# 検証結果と残存脆弱性

最終再確認日: 2026-11-19 (Asia/Tokyo)、対象コミット: `786c0e51bde3a6a6f5e0d361294c358bbcd8e83a`（PR #7 マージ後の main）、追跡: [Issue #6](https://github.com/tomohiroJin/devcontainer-c/issues/6)。

## 2026-11-19 の再確認

前回の確認期限 2026-11-12 を過ぎたため、マージ後の main で再確認した。結果は同日の main CI（[run 44555632184](https://github.com/tomohiroJin/devcontainer-c/actions/runs/44555632184)）と独立した手元の再ビルドの両方で一致した。

### ビルドとテスト

- ベース `debian:trixie-slim@sha256:a72b4433de1cf7d6bae0c4cee74d0547f58601a643b3375f070c51600d63b6b2` からクリーンビルド成功。同日時点でも `trixie-slim` タグの digest は変わっておらず、Dependabot の docker 更新対象はまだない。
- apt upgrade でベースの `zlib1g` が Debian security 更新 `1:1.3.dfsg+really1.3.1-1+deb13u1` に更新された。
- GCC 14.2.0 / Clang 19.1.7 の configure/build/CTest は各 50/50 成功（`scripts/verify-env.sh`）。
- 手元ビルドは CI と取得経路だけが異なる。セッションのネットワーク制約のため、作業用 Dockerfile のコピーで apt の取得先を https にし、proxy CA secret を `mode=0444` で渡した。導入パッケージの指定は同一で、package 数も CI と同じ 234。

### VS Code

補完・定義ジャンプ、デバッグ、保存時整形、clang-tidy 診断、Dev Containers UI からの再オープンは、maintainer が VS Code 上で確認済み（2026-11-19 に報告）。

### Trivy 監査

Trivy 0.76.2、DB UpdatedAt `2026-11-19T13:02:29.533007734Z`。

```sh
trivy image --image-src docker --scanners vuln --format json --output trivy.json devcontainer-c:audit
python3 scripts/summarize-vulnerabilities.py trivy.json
```

| 深刻度 | 11-05（package 単位） | 11-19（package 単位） |
| --- | ---: | ---: |
| CRITICAL | 1 | 1 |
| HIGH | 112 | 173 |
| MEDIUM | 506 | 587 |
| LOW | 950 | 975 |
| UNKNOWN | 12 | 53 |
| 合計 | 1581 | 1789 |
| ユニーク ID | 615 | 650 |
| 修正版あり HIGH/CRITICAL | 0 | 0 |

- OS は Debian 13.7、234 package、言語固有 lockfile は 0。
- HIGH/CRITICAL は 66 個の CVE に集約される。前回の 50 個から 7 個が外れ、23 個が加わった。
- 修正版のある HIGH/CRITICAL は 0 件で、CI の失敗ゲートも成功。未修正はゼロではない。
- 手元の生 JSON の SHA256 は `608bd1ecf5ab7f58ae2806b390a9a77b0e6cbc0de3a1112eec89ed8f10d437fe`、ローカル image ID は `sha256:89ae52cde3e72c7721052e41bce07a09976f9e7999ed79aa95e0a2a8687c1642`。CI の値はビルドごとに変わる。

前回から外れた CVE:

| CVE | package | 理由 |
| --- | --- | --- |
| CVE-2026-76844 | zlib1g | Debian security 更新 deb13u1 で解消 |
| CVE-2026-98466, CVE-2026-98715, CVE-2026-98853, CVE-2026-99109 | linux-libc-dev | 現行 DB では検出なし |
| CVE-2025-40025 | linux-libc-dev | 深刻度が LOW に再評価 |
| CVE-2026-98999 | linux-libc-dev | 深刻度が MEDIUM に再評価 |

新たに加わった 23 個の内訳は Kerberos ライブラリ（libkrb5 系）14、linux-libc-dev 3、git 3、libsqlite3-0 2、libexpat1 1。いずれも監査時点で修正版は未提供。

### 言語依存の監査

リポジトリには npm・pip・Go・Cargo・Conan・vcpkg などの言語パッケージのマニフェストやロックファイルがない。C/C++ の依存はすべて Debian パッケージとして導入され、Trivy が Debian のセキュリティ情報で検査している（言語固有ファイル 0）。このため OSV-Scanner を別に回しても対象がなく、現時点では Trivy の OS パッケージ監査で代替する。言語パッケージマネージャーを導入した時点で OSV-Scanner を CI に追加する。

### 静的解析

初回に記録した cppcheck の既存警告 4 件（`duplInheritedMember` 1、`returnByReference` 3）は学習用コードの API に関わるため、環境更新の範囲外として記録のみとしている。CI の失敗条件には加えていない。

## 残件の扱い

以下全行の担当: Repository maintainer (`tomohiroJin`)。次回確認期限: **2026-11-26**。追跡先: **Issue #6**。毎週月曜の CI で再検査し、Debian security 更新が出た時点で再ビルドする。例外の恒久除外やリスク受容を行ったものではない。

暫定運用: 開発専用・非 root のコンテナで利用し、ホストの秘密情報や本番資格情報をマウントしない。libxml2 を含むツールには信頼できない XML を入力しない。各 CVE の実利用経路・影響は maintainer が Debian tracker とベンダー情報で確認する。深刻度は検知元の判定であり、全件がこのサンプルコードから到達可能だと断定しない。

| CVE | 深刻度 | package | 状態 | 前回比 |
| --- | --- | --- | --- | --- |
| [CVE-2026-6653](https://security-tracker.debian.org/tracker/CVE-2026-6653) | CRITICAL | libxml2 | 修正版未提供 | 継続 |
| [CVE-2013-7445](https://security-tracker.debian.org/tracker/CVE-2013-7445) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2019-19449](https://security-tracker.debian.org/tracker/CVE-2019-19449) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2019-19814](https://security-tracker.debian.org/tracker/CVE-2019-19814) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2021-3847](https://security-tracker.debian.org/tracker/CVE-2021-3847) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2021-3864](https://security-tracker.debian.org/tracker/CVE-2021-3864) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2024-21803](https://security-tracker.debian.org/tracker/CVE-2024-21803) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2024-21963](https://security-tracker.debian.org/tracker/CVE-2024-21963) | HIGH | linux-libc-dev | 修正版未提供 | 新規 |
| [CVE-2024-58015](https://security-tracker.debian.org/tracker/CVE-2024-58015) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2025-69720](https://security-tracker.debian.org/tracker/CVE-2025-69720) | HIGH | libncursesw6, libtinfo6, ncurses-base, ncurses-bin | 修正版未提供 | 継続 |
| [CVE-2026-0004](https://security-tracker.debian.org/tracker/CVE-2026-0004) | HIGH | linux-libc-dev | 修正版未提供 | 新規 |
| [CVE-2026-105437](https://security-tracker.debian.org/tracker/CVE-2026-105437) | HIGH | git, git-man | 修正版未提供 | 新規 |
| [CVE-2026-107364](https://security-tracker.debian.org/tracker/CVE-2026-107364) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-111760](https://security-tracker.debian.org/tracker/CVE-2026-111760) | HIGH | git, git-man | 修正版未提供 | 新規 |
| [CVE-2026-112315](https://security-tracker.debian.org/tracker/CVE-2026-112315) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112316](https://security-tracker.debian.org/tracker/CVE-2026-112316) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112317](https://security-tracker.debian.org/tracker/CVE-2026-112317) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112318](https://security-tracker.debian.org/tracker/CVE-2026-112318) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112319](https://security-tracker.debian.org/tracker/CVE-2026-112319) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112320](https://security-tracker.debian.org/tracker/CVE-2026-112320) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112321](https://security-tracker.debian.org/tracker/CVE-2026-112321) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112322](https://security-tracker.debian.org/tracker/CVE-2026-112322) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-112323](https://security-tracker.debian.org/tracker/CVE-2026-112323) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-113351](https://security-tracker.debian.org/tracker/CVE-2026-113351) | HIGH | libexpat1 | 修正版未提供 | 継続 |
| [CVE-2026-114466](https://security-tracker.debian.org/tracker/CVE-2026-114466) | HIGH | git, git-man | 修正版未提供 | 新規 |
| [CVE-2026-115506](https://security-tracker.debian.org/tracker/CVE-2026-115506) | HIGH | libexpat1 | 修正版未提供 | 新規 |
| [CVE-2026-117610](https://security-tracker.debian.org/tracker/CVE-2026-117610) | HIGH | libexpat1 | 修正版未提供 | 継続 |
| [CVE-2026-118370](https://security-tracker.debian.org/tracker/CVE-2026-118370) | HIGH | libexpat1 | 修正版未提供 | 継続 |
| [CVE-2026-118380](https://security-tracker.debian.org/tracker/CVE-2026-118380) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-119079](https://security-tracker.debian.org/tracker/CVE-2026-119079) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-119373](https://security-tracker.debian.org/tracker/CVE-2026-119373) | HIGH | libsqlite3-0 | 修正版未提供 | 継続 |
| [CVE-2026-119374](https://security-tracker.debian.org/tracker/CVE-2026-119374) | HIGH | libsqlite3-0 | 修正版未提供 | 新規 |
| [CVE-2026-119379](https://security-tracker.debian.org/tracker/CVE-2026-119379) | HIGH | libsqlite3-0 | 修正版未提供 | 新規 |
| [CVE-2026-12064](https://security-tracker.debian.org/tracker/CVE-2026-12064) | HIGH | curl, libcurl3t64-gnutls, libcurl4t64 | 修正版未提供 | 継続 |
| [CVE-2026-15308](https://security-tracker.debian.org/tracker/CVE-2026-15308) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 | 継続 |
| [CVE-2026-16742](https://security-tracker.debian.org/tracker/CVE-2026-16742) | HIGH | libsystemd0, libudev1 | 修正版未提供 | 継続 |
| [CVE-2026-19445](https://security-tracker.debian.org/tracker/CVE-2026-19445) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 | 継続 |
| [CVE-2026-19553](https://security-tracker.debian.org/tracker/CVE-2026-19553) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 | 継続 |
| [CVE-2026-23102](https://security-tracker.debian.org/tracker/CVE-2026-23102) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-31568](https://security-tracker.debian.org/tracker/CVE-2026-31568) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-46279](https://security-tracker.debian.org/tracker/CVE-2026-46279) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-54369](https://security-tracker.debian.org/tracker/CVE-2026-54369) | HIGH | libacl1 | 修正版未提供 | 継続 |
| [CVE-2026-71199](https://security-tracker.debian.org/tracker/CVE-2026-71199) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-71200](https://security-tracker.debian.org/tracker/CVE-2026-71200) | HIGH | libgssapi-krb5-2, libk5crypto3, libkrb5-3, libkrb5support0 | 修正版未提供 | 新規 |
| [CVE-2026-72042](https://security-tracker.debian.org/tracker/CVE-2026-72042) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-7210](https://security-tracker.debian.org/tracker/CVE-2026-7210) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 | 継続 |
| [CVE-2026-74860](https://security-tracker.debian.org/tracker/CVE-2026-74860) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-76642](https://security-tracker.debian.org/tracker/CVE-2026-76642) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 | 継続 |
| [CVE-2026-78408](https://security-tracker.debian.org/tracker/CVE-2026-78408) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 | 継続 |
| [CVE-2026-78409](https://security-tracker.debian.org/tracker/CVE-2026-78409) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 | 継続 |
| [CVE-2026-78410](https://security-tracker.debian.org/tracker/CVE-2026-78410) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 | 継続 |
| [CVE-2026-82049](https://security-tracker.debian.org/tracker/CVE-2026-82049) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 | 継続 |
| [CVE-2026-8458](https://security-tracker.debian.org/tracker/CVE-2026-8458) | HIGH | curl, libcurl3t64-gnutls, libcurl4t64 | 修正版未提供 | 継続 |
| [CVE-2026-86138](https://security-tracker.debian.org/tracker/CVE-2026-86138) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-86139](https://security-tracker.debian.org/tracker/CVE-2026-86139) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-86140](https://security-tracker.debian.org/tracker/CVE-2026-86140) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-86142](https://security-tracker.debian.org/tracker/CVE-2026-86142) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-86143](https://security-tracker.debian.org/tracker/CVE-2026-86143) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-86144](https://security-tracker.debian.org/tracker/CVE-2026-86144) | HIGH | libxml2 | 修正版未提供 | 継続 |
| [CVE-2026-89675](https://security-tracker.debian.org/tracker/CVE-2026-89675) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-90315](https://security-tracker.debian.org/tracker/CVE-2026-90315) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-9538](https://security-tracker.debian.org/tracker/CVE-2026-9538) | HIGH | libperl5.40, perl, perl-base, perl-modules-5.40 | Debian が修正を延期 (fix_deferred) | 継続 |
| [CVE-2026-96512](https://security-tracker.debian.org/tracker/CVE-2026-96512) | HIGH | sudo | 修正版未提供 | 継続 |
| [CVE-2026-98118](https://security-tracker.debian.org/tracker/CVE-2026-98118) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-98364](https://security-tracker.debian.org/tracker/CVE-2026-98364) | HIGH | linux-libc-dev | 修正版未提供 | 継続 |
| [CVE-2026-99272](https://security-tracker.debian.org/tracker/CVE-2026-99272) | HIGH | linux-libc-dev | 修正版未提供 | 新規 |

## 初回監査の記録（2026-11-05）

Trivy 0.76.2、DB UpdatedAt `2026-11-05T13:09:41.435406326Z`。最終ローカル image ID `sha256:7644ba54e40ac298cd16a77b7b346a0826b60955477cafe2ed7d64309fb604b0`、生 JSON の SHA256 `879904c0846827d7fc7b8831b7365f905d583c3512c45d3190783bb08abd3955`。

初回の全 Boost モジュールからヘッダー package への変更時は HIGH 134 → 113、CRITICAL 2 → 1 となり、不要な OpenSSH client の CVE-2026-60002 を除去した。レビューで未使用の LLDB を外した最終像は 234 package（239 → 234）、HIGH 112、CRITICAL 1。GDB が libpython3.13 に依存するため、LLDB 除去で Python 関連 CVE 全件を除去できるわけではない。残存 CRITICAL の libxml2 は LLVM 系依存に含まれ、調査時の Debian/Trivy に修正版がない。
