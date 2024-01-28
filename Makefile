TEST = tests
EXTERNAL = external
TESTS = $(wildcard $(TEST)/*.c)
TESTBINS = $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))
CRITERION_URL_LIB = https://github.com/Snaipe/Criterion/releases/download/v2.3.3/criterion-v2.3.3-linux-x86_64.tar.bz2
raylib_URL_LIB = https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_linux_amd64.tar.gz


$(TEST)/bin/%: $(TEST)/%.c
	gcc $< -o $@ -I"./external/criterion-v2.3.3/include/" -L"./external/criterion-v2.3.3/lib/" -lcriterion

$(TEST)/bin:
	mkdir $@

$(TEST)/images:
	mkdir $@

$(BUILD)/:
	mkdir $@

$(EXTERNAL):
	mkdir $@

install_criterion:$(EXTERNAL)
	cd ./external && curl -L $(CRITERION_URL_LIB) -o criterion-v2.3.3.tar.bz2 && tar -xjf criterion-v2.3.3.tar.bz2 && rm criterion-v2.3.3.tar.bz2
install_raylib:$(EXTERNAL)
	cd ./external && mkdir raylib-5.0 && cd raylib-5.0 && curl -L $(raylib_URL_LIB) -o raylib-5.0.tar.gz && tar -xzvf raylib-5.0.tar.gz --strip-components=1 && rm raylib-5.0.tar.gz
# build_criterion:
# 	cd ./external/criterion-v2.3.3 && mkdir build && cd build/ && cmake .. && make -j5

build:
	@$(CC) -ggdb -o hangman_game src/main.c

run:
	@./hangman_game

test: $(TEST)/bin $(TESTBINS) $(TEST)/images
	export LD_LIBRARY_PATH=./external/criterion-v2.3.3/lib/; \
	for test in $(TESTBINS); do ./$$test --verbose; done
clean_test:
	rm -r $(TEST)/bin
	rm -r $(TEST)/images