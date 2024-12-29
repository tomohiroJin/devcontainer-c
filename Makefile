# ディレクトリ定義
BUILD_DIR = build

# デフォルトターゲット
all: build

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

# ビルドしてテストを実行
bt: clean build test