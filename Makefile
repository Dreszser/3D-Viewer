SHELL=/bin/sh
CXX=g++
CXXFLAGS=-Wall -Werror -Wextra -std=c++20 -g -O2
LFLAGS=-lcheck -lpthread -lsubunit 
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC

GZ_PRJ=model/ view/ controller/ common/ documentation/ party/ tests/ Doxyfile Makefile CMakeLists.txt resources.qrc

TEST_SRC=$(wildcard ./common/*.cc ./model/*.cc ./tests/*.cc)
TEST_OBJ=$(TEST_SRC:.cc=.o)

CEXE=s21_test

LTEST = -lgtest -lgtest_main
VG =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  LDFLAGS += -lrt -lsubunit
	LTEST += -lsubunit -lrt -pthread
	VG += @valgrind --tool=memcheck --leak-check=yes ./$(CEXE)
else ifeq ($(UNAME_S), Darwin)
	LTEST += -pthread
endif

all: rebuild

install:
	mkdir -p build
	cmake -DCMAKE_INSTALL_PREFIX=build -S . -B build
	make -C ./build/

rebuild: clean install

%.o: %.cc
	@$(CXX) $(CXXFLAGS) -c  $< -o $@

#============= DIST ==============================================================
dist:
	@tar cvzf 3D_Viewer.tar.gz $(GZ_PRJ)

#============= TEST ==============================================================
tests: clean $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(CEXE) $(LTEST)
	@rm -rf $(TEST_OBJ)
	$(VG)

#===========  DVI  ====================================================================

dvi: dvi_clean
	@doxygen Doxyfile

dvi_clean:
	@rm -rf docs/html/ docs/latex/

gcov_report: clean
	$(CXX) $(CXXFLAGS) --coverage $(TEST_SRC) -o $(CEXE) $(LTEST)
	-@./$(CEXE)
	@mkdir ./report
	@gcovr --exclude "tests/.*|model/facade.*|model/model.*|common/.*" \
	--exclude-unreachable-branches --exclude-throw-branches \
	-r . --object-directory=. --print-summary --html-details \
	report/index.html --html-medium-threshold 80 --html-high-threshold 95 \
	--html-title "3D_Viewer coverage report"
	@rm -rf *.gcda *.gcno *.info $(TEST_OBJ) $(CEXE) *.dSYM


uninstall:
	@rm -rf build

#=========== STYLE ====================================================================
format_check:
	clang-format --style=file:../materials/linters/.clang-format -n */*.cc */*.h

format:
	clang-format --style=file:../materials/linters/.clang-format -i */*.cc */*.h


#========== CLEAN ======================================================================
clean:
	@rm -rf *.o
	@rm -rf $(TEST_OBJ)
	@rm -rf *.out
	@rm -rf *.a
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.gcov
	@rm -rf *.log
	@rm -rf *.html
	@rm -rf *.css
	@rm -rf report
	@rm -rf *.dSYM
	@rm -rf *.info
	@rm -rf build
	@rm -rf *.gz
	@rm -rf *.dat*
	@rm -rf ./dvi/html ./dvi/latex
	@rm -rf $(CEXE)
	@rm -rf docs