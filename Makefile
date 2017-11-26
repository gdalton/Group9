
all:
	g++ *.cpp
	./a.out


test: get-test-suite
	cd googletest && \
	g++ -Igoogletest/include -pthread ../tests/exampleTest.cc libgtest.a -o test_executable && \
	./test_executable


get-test-suite:
	git clone https://github.com/google/googletest.git
	cd googletest && \
	g++ -Igoogletest/include -Igoogletest -c googletest/src/gtest-all.cc && \
	ar -rv libgtest.a gtest-all.o

