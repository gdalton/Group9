
all:
	g++ *.cpp
	./a.out


test: 
	cd googletest && \
	g++ $(addprefix ../, $(filter-out main.cpp, $(wildcard *.cpp))) -Igoogletest/include -pthread ../tests/*.cc libgtest.a -o ../testdir/test_executable && \
	../testdir/test_executable


get-test-suite:
	git clone https://github.com/google/googletest.git
	cd googletest && \
	g++ -Igoogletest/include -Igoogletest -c googletest/src/gtest-all.cc && \
	ar -rv libgtest.a gtest-all.o

