
# Google Test Framework #

This is a complied version of the GoogleTest framework. The full version can be found [here](https://github.com/google/googletest).

## Instructions for Writing Tests ##
- In general, use [Google's Guide](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) for reference.
- Put tests in gTest/, with extension .cc

**However, write tests in the format:**
```
TEST( <test name>, <testing what?>) {
       EXPECT_EQ(1, 1); //Assertion that 1 == 1
   }
```


**For format, see:** gTest/exampleTest.cc

## Instructions for Running Tests ##

**To run:** `cd gTest/` **and run**
`g++ -I googletest/include -pthread exampleTest.cc libgtest.a -o test_executable`

**Then do:**
`./test_executable` to run the tests.
