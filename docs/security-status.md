# 検証結果と残存脆弱性

調査日: 2026-11-05 (Asia/Tokyo)、追跡: [Issue #6](https://github.com/tomohiroJin/devcontainer-c/issues/6)。

## 実行結果

- クリーンビルド成功。最終ローカル image ID: `sha256:2af72b92a7c16415a7dedc69cca4bee2cb4cf559bcb5f6de5f4663405b2693e2`。未公開のローカルイメージのため registry digest はない。
- GCC 14.2.0 / Clang 19.1.7 の configure/build/CTest は各 50/50 成功。C++20 を維持。
- CMake 3.31.6、cppcheck 2.17.1、GoogleTest Debian package 1.16.0-1、Boost 1.83、OpenSSL 3.5.7 系。
- JSON/bash/YAML 構文、推奨拡張一覧の一致、git diff --check を確認。
- `cppcheck --enable=warning,performance,portability --error-exitcode=1 --std=c++20 --suppress=missingIncludeSystem -Isrc src` は exit 1。既存の学習コードに `duplInheritedMember` 1件（ProfessorEH::setAge）、`returnByReference` 3件（getName/getSchool/getSubject）。環境更新で学習用 API の意味を変えないため記録のみとし、CI の失敗条件には加えていない。
- VS Code GUI の補完・デバッグ・保存時整形と Dev Containers UI からの再オープンは本セッションでは未実施。直接 Docker build/run と両コンパイラの動作を検証済み。

## Trivy 監査

Trivy 0.76.2、DB UpdatedAt `2026-11-05T13:09:41.435406326Z`。`trivy image --image-src docker --scanners vuln --skip-db-update --cache-dir /tmp/c-trivy-cache --format json --output /tmp/c-final-trivy.json devcontainer-c:issue6` を実行。OS Debian 13.7、239 package、言語固有 lockfile 0。C++ ライブラリは Debian package として検査される。

最終結果（package ごとの重複を含む）: CRITICAL 1, HIGH 113, LOW 960, MEDIUM 506, UNKNOWN 12。全深刻度で修正版が報告された検知は 0 件。修正版のある HIGH/CRITICAL は 0 件。HIGH/CRITICAL は 50 個の CVE に集約される。未修正はゼロではない。

生 JSON の SHA256: `4a07256ff8583add152aebb83fdcee43f8779de116fbc6c8dcae597259e9bb56`。以後の CI は全件 JSON・package 一覧・image inspect を artifact として保存する。

全 Boost モジュールからヘッダー package に絞ったことで、HIGH は 134 → 113、CRITICAL は 2 → 1 に減少し、不要な OpenSSH client の CVE-2026-60002 を除去した。残存 CRITICAL の libxml2 は LLVM 系依存に含まれ、調査時の Debian/Trivy に修正版がない。

## 残件の扱い

以下全行の担当: Repository maintainer (`tomohiroJin`)。次回確認期限: **2026-11-12**。追跡先: **Issue #6（未完了のまま）**。各行とも監査時は修正版未提供。毎週の CI で再検査し、Debian security 更新が出た時点で再ビルドする。例外の恒久除外やリスク受容を行ったものではない。

暫定運用: 開発専用・非 root のコンテナで利用し、ホストの秘密情報や本番資格情報をマウントしない。libxml2 を含むツールには信頼できない XML を入力しない。各 CVE の実利用経路・影響は maintainer が Debian tracker とベンダー情報で確認する。深刻度は検知元の判定であり全件がこのサンプルコードから到達可能だと断定しない。

| CVE | 深刻度 | package | 状態 |
| --- | --- | --- | --- |
| [CVE-2026-6653](https://security-tracker.debian.org/tracker/CVE-2026-6653) | CRITICAL | libxml2 | 修正版未提供 |
| [CVE-2013-7445](https://security-tracker.debian.org/tracker/CVE-2013-7445) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2019-19449](https://security-tracker.debian.org/tracker/CVE-2019-19449) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2019-19814](https://security-tracker.debian.org/tracker/CVE-2019-19814) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2021-3847](https://security-tracker.debian.org/tracker/CVE-2021-3847) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2021-3864](https://security-tracker.debian.org/tracker/CVE-2021-3864) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2024-21803](https://security-tracker.debian.org/tracker/CVE-2024-21803) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2024-58015](https://security-tracker.debian.org/tracker/CVE-2024-58015) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2025-40025](https://security-tracker.debian.org/tracker/CVE-2025-40025) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2025-69720](https://security-tracker.debian.org/tracker/CVE-2025-69720) | HIGH | libncurses6, libncursesw6, libtinfo6, ncurses-base, ncurses-bin | 修正版未提供 |
| [CVE-2026-113351](https://security-tracker.debian.org/tracker/CVE-2026-113351) | HIGH | libexpat1 | 修正版未提供 |
| [CVE-2026-117610](https://security-tracker.debian.org/tracker/CVE-2026-117610) | HIGH | libexpat1 | 修正版未提供 |
| [CVE-2026-118370](https://security-tracker.debian.org/tracker/CVE-2026-118370) | HIGH | libexpat1 | 修正版未提供 |
| [CVE-2026-119373](https://security-tracker.debian.org/tracker/CVE-2026-119373) | HIGH | libsqlite3-0 | 修正版未提供 |
| [CVE-2026-12064](https://security-tracker.debian.org/tracker/CVE-2026-12064) | HIGH | curl, libcurl3t64-gnutls, libcurl4t64 | 修正版未提供 |
| [CVE-2026-15308](https://security-tracker.debian.org/tracker/CVE-2026-15308) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 |
| [CVE-2026-16742](https://security-tracker.debian.org/tracker/CVE-2026-16742) | HIGH | libsystemd0, libudev1 | 修正版未提供 |
| [CVE-2026-19445](https://security-tracker.debian.org/tracker/CVE-2026-19445) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 |
| [CVE-2026-19553](https://security-tracker.debian.org/tracker/CVE-2026-19553) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 |
| [CVE-2026-23102](https://security-tracker.debian.org/tracker/CVE-2026-23102) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-31568](https://security-tracker.debian.org/tracker/CVE-2026-31568) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-46279](https://security-tracker.debian.org/tracker/CVE-2026-46279) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-54369](https://security-tracker.debian.org/tracker/CVE-2026-54369) | HIGH | libacl1 | 修正版未提供 |
| [CVE-2026-72042](https://security-tracker.debian.org/tracker/CVE-2026-72042) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-7210](https://security-tracker.debian.org/tracker/CVE-2026-7210) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 |
| [CVE-2026-74860](https://security-tracker.debian.org/tracker/CVE-2026-74860) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-76642](https://security-tracker.debian.org/tracker/CVE-2026-76642) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 |
| [CVE-2026-76844](https://security-tracker.debian.org/tracker/CVE-2026-76844) | HIGH | zlib1g | 修正版未提供 |
| [CVE-2026-78408](https://security-tracker.debian.org/tracker/CVE-2026-78408) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 |
| [CVE-2026-78409](https://security-tracker.debian.org/tracker/CVE-2026-78409) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 |
| [CVE-2026-78410](https://security-tracker.debian.org/tracker/CVE-2026-78410) | HIGH | bsdutils, libblkid1, liblastlog2-2, libmount1, libsmartcols1, libuuid1, login, mount, util-linux | 修正版未提供 |
| [CVE-2026-82049](https://security-tracker.debian.org/tracker/CVE-2026-82049) | HIGH | libpython3.13, libpython3.13-minimal, libpython3.13-stdlib, python3.13, python3.13-minimal | 修正版未提供 |
| [CVE-2026-8458](https://security-tracker.debian.org/tracker/CVE-2026-8458) | HIGH | curl, libcurl3t64-gnutls, libcurl4t64 | 修正版未提供 |
| [CVE-2026-86138](https://security-tracker.debian.org/tracker/CVE-2026-86138) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-86139](https://security-tracker.debian.org/tracker/CVE-2026-86139) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-86140](https://security-tracker.debian.org/tracker/CVE-2026-86140) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-86142](https://security-tracker.debian.org/tracker/CVE-2026-86142) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-86143](https://security-tracker.debian.org/tracker/CVE-2026-86143) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-86144](https://security-tracker.debian.org/tracker/CVE-2026-86144) | HIGH | libxml2 | 修正版未提供 |
| [CVE-2026-89675](https://security-tracker.debian.org/tracker/CVE-2026-89675) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-90315](https://security-tracker.debian.org/tracker/CVE-2026-90315) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-9538](https://security-tracker.debian.org/tracker/CVE-2026-9538) | HIGH | libperl5.40, perl, perl-base, perl-modules-5.40 | 修正版未提供 |
| [CVE-2026-96512](https://security-tracker.debian.org/tracker/CVE-2026-96512) | HIGH | sudo | 修正版未提供 |
| [CVE-2026-98118](https://security-tracker.debian.org/tracker/CVE-2026-98118) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-98364](https://security-tracker.debian.org/tracker/CVE-2026-98364) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-98466](https://security-tracker.debian.org/tracker/CVE-2026-98466) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-98715](https://security-tracker.debian.org/tracker/CVE-2026-98715) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-98853](https://security-tracker.debian.org/tracker/CVE-2026-98853) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-98999](https://security-tracker.debian.org/tracker/CVE-2026-98999) | HIGH | linux-libc-dev | 修正版未提供 |
| [CVE-2026-99109](https://security-tracker.debian.org/tracker/CVE-2026-99109) | HIGH | linux-libc-dev | 修正版未提供 |
