
all:
	g++ *.cpp
	./a.out

clean-test:
	mkdir -p testdir/accounts
	rm -rf testdir/accounts/*
	cp accounts/* testdir/accounts/
	sed 's/\r$///' testdir/accounts/*.txt


test: 	
	cd googletest && \
	g++ $(addprefix ../, $(filter-out main.cpp, $(wildcard *.cpp))) -Igoogletest/include -pthread ../tests/*.cc libgtest.a -o ../testdir/test_executable.out && \
	cd ../testdir/ && \
	./test_executable.out


get-test-suite:
	git clone https://github.com/google/googletest.git
	cd googletest && \
	g++ -Igoogletest/include -Igoogletest -c googletest/src/gtest-all.cc && \
	ar -rv libgtest.a gtest-all.o

