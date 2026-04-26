.PHONY: format
format:
	clang-format -i kernel/*.cpp kernel/*.hpp
	clang-format -i MokaLoaderPkg/*.c MokaLoaderPkg/*.hpp

.PHONY: build
build:
	./build.sh
