# CS300 Group 9 - ChocAn System

The is repository contains the code and test suites for
the CS300 group project.

## To Build and Run

Type `make all` to build and run.


## Instructions for Writing Tests ##
- In general, use [Google's Guide](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) for reference.
- Put tests in tests/, with extension .cc

**However, write tests in the format:**
```
TEST( <test name>, <testing what?>) {
       EXPECT_EQ(1, 1); //Assertion that 1 == 1
   }
```


**For format, see:** tests/exampleTest.cc

## Instructions for Running Tests ##

**To Install:**
Run `make get-test-suite` to install googletest.

**To run:***

Run `make test` to run the tests (only runs tests/exampleTest.cc at the moment).  

Verified to work on PSU Linux. 

