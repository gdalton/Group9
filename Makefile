
all:
	g++ *.cpp
	./a.out

setuptest:
	rm -rf testdir/*
	mkdir -p testdir/accounts
	cp accounts/* testdir/accounts/
	sed --silent 's/\r$///' testdir/accounts/*.txt
	cp directory.txt testdir/
	sed --silent 's/\r$///' testdir/directory.txt

test: 	
	make setuptest
	cd googletest && \
	g++ -g $(addprefix ../, $(filter-out accountManager.cpp main.cpp, $(wildcard *.cpp))) ../tests/accountManagerLocal.cpp ../tests/common.cpp -Igoogletest/include -pthread $(addprefix ../, $(filter-out tests/manualTests.cc, $(wildcard tests/*.cc))) libgtest.a -o ../testdir/test_executable.out && \
	cd ../testdir/ && \
	./test_executable.out

manualtest:
	make setuptest
	
	cd googletest && \
	g++ $(addprefix ../, $(filter-out accountManager main.cpp, $(wildcard *.cpp))) ../tests/accountManagerLocal.cpp ../tests/common.cpp -Igoogletest/include -pthread ../tests/*.cc libgtest.a -o ../testdir/test_executable.out && \
	cd ../testdir/ && \
	./test_executable.out

get-test-suite:
	git clone https://github.com/google/googletest.git
	cd googletest && \
	g++ -Igoogletest/include -Igoogletest -c googletest/src/gtest-all.cc && \
	ar -rv libgtest.a gtest-all.o

