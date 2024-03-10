CC              := gcc
CXXFLAGS 		:= -Werror -Wextra -Wall -std=c++17
CXXCOV 			:= --coverage
VALGRIND_FLAGS  := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
SOURCES_FOR_TESTS :=Model/CreditCalculator/Calculator.cc \
						Model/DepositCalculator/Calculator.cc \
						Model/DepositCalculator/BaseCalculator/BaseCalculator.cc \
						Model/DepositCalculator/logger/logger.cc \
						Model/DepositCalculator/Parameters/Parameters.cc \
						Model/DepositCalculator/Result/Result.cc \
						Model/DepositCalculator/taxes/taxes.cc \
						Model/DepositCalculator/utility/utility.cc \
						Model/ExpressionCalculator/Calculation/Calculation.cc \
					 	Model/ExpressionCalculator/Calculation/CalculationHandlers.cc \
					 	Model/ExpressionCalculator/ExpressionTokenizer/ExpressionTokenizer.cc \
					 	Model/ExpressionCalculator/ExpressionTokenizer/Validator.cc \
					 	Model/ExpressionCalculator/ShuntingYard/ShuntingYard.cc \
					 	Model/ExpressionCalculator/StackManipulation/StackManipulation.cc \
					 	Model/ExpressionCalculator/Calculator.cc \
					 	Model/Model.cc \
	                  	Model/utility.cc \
					 	Controller/Controller.cc \
                        ../tests/model_tests.cc \
					 	../tests/tests.cc

APP_DESTINATION			:=../build/calculator_plus.app/Contents/MacOS/# will be different on another machine
APP_NAME				:=calculator_plus
CMAKE_BUILD_TYPE		:=Release # Release or Debug
SOURCE_PATH				:=./
DEST_PATH				:=../build
DIST_DIR :=archive

OS_NAME := $(shell uname -o 2>/dev/null || echo "Unknown")

OPEN_COMMAND := open

ifeq ($(OS_NAME), GNU/Linux)
    OPEN_COMMAND := xdg-open
	APP_DESTINATION:= ../build/
endif

all: dvi test gcov_report install run style_check

uninstall:
	@rm -rf ${DEST_PATH}
	@echo "Uninstall finished"

init_project:
	cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
     -S ${SOURCE_PATH} \
     -B ${DEST_PATH}

install: uninstall init_project
	cmake --build ${DEST_PATH} --target ${APP_NAME} -j 4

run:
	$(APP_DESTINATION)$(APP_NAME)
dvi:
	@$(OPEN_COMMAND) ../dvi/README.html

cppcheck:
	@find .. -type f -name "*.cc" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@find .. -type f -name "*.h" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@echo "Cppcheck is finished"
style:
	@find .. -type f -name "*.cc" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"
style_check:
	@find .. -type f -name "*.cc" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

gcov_report:

test: clean
	@${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES_FOR_TESTS) -lgtest -lstdc++ -lm  -o test.out
	@./test.out
	@make clean

test_valgrind:
	@${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES_FOR_TESTS) -lgtest -lstdc++ -lm  -o test.out
	@valgrind ${VALGRIND_FLAGS} ./test.out

install_brew:
	cd ~ && curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_brew_goinfre:
	cd ~/goinfre && mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew

install_qtcreator: #ubuntu root users only
	sudo apt update && sudo apt install qtcreator


dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/Controller ${DIST_DIR}/Controller
	cd ../ && cp -rf src/Model ${DIST_DIR}/Model
	cd ../ && cp -rf src/View ${DIST_DIR}/View
	cd ../ && cp -rf src/main.cc ${DIST_DIR}
	cd ../ && cp -rf src/Makefile ${DIST_DIR}
	cd ../ && cp -rf src/CMakeLists.txt ${DIST_DIR}
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}
dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist
	@echo "Clean finished"

clean_project:

clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find . -type f -name "*.a" -exec rm {} \;
clean_log:
	@find . -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find . -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find . -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find . -type f -name "*.gcda" -exec rm {} \;
	@find . -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find . -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report