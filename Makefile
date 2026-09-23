BUILD_DIR := build

.PHONY: all run clean

all:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) -j

run: all
	./$(BUILD_DIR)/representacao_mundo

clean:
	rm -rf $(BUILD_DIR)
