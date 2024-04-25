#include <gtest/gtest.h>
#include "et_feeder.h"



class ETFeederTest : public ::testing::Test {
protected:
    ETFeederTest() {}  // Default constructor
    virtual ~ETFeederTest() {}

    // Overloaded SetUp function
    void SetUp(const std::string& filename) {
        trace = new Chakra::ETFeeder(filename);
    }

    virtual void TearDown() {
        delete trace;
    }

    Chakra::ETFeeder* trace;
};

// Example test case
TEST_F(ETFeederTest, MyTestCaseName) {
    SetUp("et_feeder/chakra.0.et");
    std::shared_ptr<Chakra::ETFeederNode> node = trace->getNextIssuableNode();
    uint64_t ceva = node->id(); 
    std::cout << ceva << '\n';
    std::cout << node->type() << '\n';

    node = trace->getNextIssuableNode();
    ceva = node->id(); 
    std::cout << ceva << '\n';
    std::cout << node->type() << '\n';

    node = trace->getNextIssuableNode();
    ceva = node->id(); 
    std::cout << ceva << '\n';
    std::cout << node->type() << '\n';
    // Your test logic here
    // ...
}

// Add more test cases as needed

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}