#include "gtest/gtest.h"
#include "../mainHeader.h"


TEST(smokeTesting, displayServicesList) { // @todo I'm not sure how to test this
    UserInterface ui;
    
    ASSERT_TRUE(ui.runProviderMenu()) << "Failed to see provider menu?";
    ASSERT_TRUE(ui.runManagerMenu()) << "Failed to see manager menu?";
}

/*TEST(unitTests, emailReports) { //@todo can't really test this rn
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(unitTests, displayAllMembers) { //@todo can't really test this rn
    ASSERT_TRUE(false) << "Not implemented";
}*/

TEST(unitTests, runInInteractiveMode) { //@todo can't really test this rn
    UserInterface ui;
	ASSERT_TRUE(ui.login()) << "Failed to launch interactive?";
}

/*
TEST(unitTests, userlogin) {
    UserInterface ui;
	ASSERT_TRUE(ui.login()) << "Login failure?";
}
*/
