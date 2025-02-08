# ディレクトリ定義
BUILD_DIR = build

# ビルドターゲット
build:
	mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

# テストターゲット
test:
	cd $(BUILD_DIR) && ctest --output-on-failure

# クリーンターゲット
clean:
	rm -rf $(BUILD_DIR)

# デフォルトターゲット
all: clean build test

# ビルドしてテストを実行
bt: build test