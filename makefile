APP=hash_table_testcases
MODULE=hash_table
COPTS=-fprofile-arcs -ftest-coverage
export COV_OUTPUT=./cov_out

ifndef GTEST_DIR
	GTEST_DIR=${HOME}/googletest/googletest/
else
	GTEST_DIR=${GTEST_DIR}
endif

          
$(APP): gtest_main.o $(APP).o libgtest.a $(MODULE).o
	g++ $(COPTS) -g -isystem $(GTEST_DIR)/include -pthread -o $(APP) gtest_main.o $(APP).o $(MODULE).o libgtest.a
              
gtest_main.o: gtest_main.c
	g++ -g -isystem $(GTEST_DIR)/include -pthread -c gtest_main.c
                  
$(APP).o:  $(APP).c  $(MODULE).h
	g++ $(COPTS) -g -isystem $(GTEST_DIR)/include -pthread -c $(APP).c
                      
$(MODULE).o: $(MODULE).c $(MODULE).h
	g++ $(COPTS) -c -g $(MODULE).c
                          
libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
                                  
clean:
	rm -f *.o *.a *.gcno *.gcda *.gcov ${APP}
                                     
run:
	./$(APP)

debug:
	gdb ./$(APP)

report:
	lcov -rc lcov_branch_coverage=1 -c -i -d . -o .coverage.base
	lcov -rc lcov_branch_coverage=1 -c -d . -o .coverage.run
	lcov -rc lcov_branch_coverage=1 -d . -a .coverage.base -a .coverage.run -o .coverage.total
	genhtml --branch-coverage --highlight --legend --output-directory out -o ${COV_OUTPUT} .coverage.total
	rm -f .coverage.base .coverage.run .coverage.total                             
                                          
