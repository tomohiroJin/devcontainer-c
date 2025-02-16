# ディレクトリ定義
BUILD_DIR = build

# `.PHONY` を指定し、ターゲットが確実に実行されるようにする
.PHONY: all build test clean bt

# `-j` オプション付きで並列ビルド可能に
build:
	mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) -- -j$(nproc)

# 全テスト実行
test: build
	@if [ -z "$(TEST)" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure; \
	else \
		cd $(BUILD_DIR) && ctest -R $(TEST) --output-on-failure; \
	fi

# クリーンターゲット
clean:
	rm -rf $(BUILD_DIR)

# フルビルド + テスト
all: clean build test
