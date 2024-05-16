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

// Constructor test case
TEST_F(ETFeederTest, ConstructorTestID) {
    SetUp("et_feeder/chakra.0.et");
    std::shared_ptr<Chakra::ETFeederNode> node = trace->getNextIssuableNode();
    uint64_t firstNodeID = node->id(); 
    ASSERT_EQ(firstNodeID, 216);

    node = trace->getNextIssuableNode();
    uint64_t secondNodeID = node->id(); 
    ASSERT_EQ(secondNodeID, 432);
}

// Constructor test case
TEST_F(ETFeederTest, ConstructorTestValues) {
    SetUp("et_feeder/chakra.0.et");
    std::shared_ptr<Chakra::ETFeederNode> node = trace->getNextIssuableNode();
    ChakraProtoMsg::NodeType firstNodeType = node->type(); 
    ASSERT_EQ(firstNodeType, ChakraProtoMsg::COMP_NODE);
    ASSERT_TRUE(node->is_cpu_op());

    std::string attr = "rf_id";
    ChakraProtoMsg::AttributeProto rf_id = node->get_other_attr(attr);
    ASSERT_EQ(rf_id.int64_val(), 2);
    // std::cout << node->getChakraNode()->Utf8DebugString();
    
    node = trace->getNextIssuableNode();
    uint64_t secondNodeType = node->type(); 
    ASSERT_EQ(secondNodeType, ChakraProtoMsg::COMM_COLL_NODE);
    ASSERT_TRUE(node->is_cpu_op());

    rf_id = node->get_other_attr(attr);
    ASSERT_EQ(rf_id.int64_val(), 110);
}

TEST_F(ETFeederTest, ConstructorTestETFeeder) {
    SetUp("et_feeder/chakra.0.et");
    std::shared_ptr<Chakra::ETFeederNode> node = trace->getNextIssuableNode();
    std::vector<std::shared_ptr<Chakra::ETFeederNode>> children = node->getChildren(); 
    ASSERT_EQ(children[0]->id(), 217);
    ASSERT_EQ(children[1]->id(), 430);
    ASSERT_EQ(children[2]->id(), 435);
}

TEST_F(ETFeederTest, RemoveTest) {
    SetUp("et_feeder/chakra.0.et");
    std::shared_ptr<Chakra::ETFeederNode> node = trace->lookupNode(216);
    ASSERT_EQ(node->id(), 216);
    trace->removeNode(216);
    node = trace->lookupNode(216);
    // ASSERT_EQ(node->id(), 5);
}

TEST_F(ETFeederTest, RemoveTestAndGetNext) {
    SetUp("et_feeder/llama_chakra.3.et");
    std::shared_ptr<Chakra::ETFeederNode> node = trace->lookupNode(5);
    ASSERT_EQ(node->id(), 5);
    trace->removeNode(5);
    node = trace->getNextIssuableNode();
    ASSERT_EQ(node->id(), 5);
}

// Add more test cases as needed

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}