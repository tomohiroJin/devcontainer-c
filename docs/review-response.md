# PR #7 レビュー対応

対象: [レビューコメント](https://github.com/tomohiroJin/devcontainer-c/pull/7#issuecomment-6664551753)。確認日: 2026-11-05。各提案を現在のコード・ビルドコンテキスト・実測結果と照合した。

| 指摘番号 | 判断と対応 |
| --- | --- |
| 1. 監査件数が CI ログにない | 採用。全深刻度の Trivy JSON を集計するスクリプトを追加し、未修正を含む件数、ユニーク ID 数、修正版あり HIGH/CRITICAL、イメージID、JSON SHA256 をログと Job Summary に出す。生 JSON artifact と独立したセキュリティ失敗ゲートを維持。件数は監査時点のスナップショットであり、今後の CI で固定値と一致するとは限らない。 |
| 2. ベースが浮動で Dependabot に差分がない | 採用。`docker buildx imagetools inspect debian:trixie-slim` で公開 multi-architecture manifest の digest を独立確認し、FROM に固定した。既存 Docker Dependabot 設定で digest 更新をレビューする。apt は security 更新を取る可変運用を継続し、イメージID・package一覧を保存する。 |
| 3. 二重実行・実行上限なし | 採用。push は main のみに限定、ref ごとの concurrency と旧実行キャンセル、job の30分上限を設定。PR・手動・週次は継続。 |
| 4. .dockerignore のコンテキスト不一致 | 採用。実際の context は CI・Dev Containers とも `.devcontainer/`。参照されないルートの .dockerignore を削除した。context を拡大しない。 |
| 5. Boost説明とテスト名 | 採用。ヘッダーオンリーの範囲とバイナリモジュール追加方法を明記。README を実際の FizzBuzzTest / Factory.*PatternTest に修正。Makefile・検証スクリプトは `--no-tests=error` を指定し、タイプミスで0件成功になる動作も防止。Makefile の正規表現引数を引用符で保護。 |
| 6. BuildKit frontend の浮動タグ | 今回は固定しない。公式安定 major `docker/dockerfile:1` を維持。syntax directive の digest を Dependabot が更新することは確認できておらず、未更新の固定値を増やさない。base digest とは別に解決済み frontend digest をビルドログで追跡し、保守時の見直し事項を明記。 |
| 7. LLDB の利用根拠 | 採用。現在の拡張構成では GDB を使うため未使用の lldb を削除。依存数は239→234、HIGH は113→112。GDB が libpython3.13 に依存することも実測し、Python 関連脆弱性が全て消えるとは主張しない。 |
| 8. postCreate で学習用の失敗テストが作成エラーになる | 採用。ツール版表示専用の show-versions.sh を分離し、postCreate はこれだけを実行する。両コンパイラのビルド・全テストは verify-env.sh として手動・CI で維持。 |
| 9. GoogleTest include とメッセージが no-op | 採用。REQUIRED による探索失敗と GTest::gtest の include 伝播を利用し、空の GTEST_INCLUDE_DIRS と冗長な分岐を削除。解決した GTest_DIR を表示する。 |

## 検証

- digest 固定・LLDB 除去後の Docker build 成功。最終イメージは `sha256:7644ba54e40ac298cd16a77b7b346a0826b60955477cafe2ed7d64309fb604b0`。
- GCC 14.2 / Clang 19.1 の既存テストはそれぞれ50/50成功。README のフィルターはそれぞれ4/4成功し、不一致フィルターは `--no-tests=error` により失敗した。
- 版表示専用スクリプトを実行。GTest_DIR は `/usr/lib/x86_64-linux-gnu/cmake/GTest` と表示され、同じ imported target で両方のビルドが成功。
- Summary スクリプトは fixed/unfixed・同じ CVE の複数 package・該当深刻度0件を含む入力で検証し、stdout と Job Summary ファイルの一致、必須結果のない不正入力の失敗を確認。実際の新旧監査 JSON に対しても実行。
- 新イメージを Trivy 0.76.2 / DB `2026-11-05T13:09:41.435406326Z` で再検査。CRITICAL 1 / HIGH 112 / MEDIUM 506 / LOW 950 / UNKNOWN 12（総1581、重複あり）。全深刻度で修正版の報告は0件、修正版あり HIGH/CRITICAL の失敗ゲートは exit 0。残存リスクと50個の HIGH/CRITICAL CVE は [security-status.md](security-status.md) で追跡。
- actionlint、JSON/YAML、bash 構文、git diff --check は成功。
- VS Code GUI と更新後の GitHub Actions 実行はこのローカル確認には含まれない。初回に記録した学習用コードの cppcheck 警告4件も、このレビューで解消したものではない。
