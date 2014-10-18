#include <vector>
#include "back_end/opcode_executor/opcode_handlers.h"
#include "back_end/opcode_executor/opcode_executor.h"
#include "back_end/opcode_executor/opcodes.h"
#include "test_harness/test_harness.h"
#include "test_harness/test_harness_utils.h"

#include "third_party/gtest/include/gtest/gtest.h"

namespace back_end {
namespace handlers {

unsigned char GetRegisterValue(unsigned char* rom, int instruction_ptr, unsigned char opcode);

using std::vector;
using handlers::OpcodeExecutor;
using Register = test_harness::RegisterNameValuePair;

// The fixture gets instantiated once per test case. We would like to reuse the
// OpcodeExecutor. Also, this will get cleaned up when the test is over.
OpcodeExecutor* parser = new OpcodeExecutor(nullptr, 0);

class OpcodeHandlersTest : public test_harness::TestHarness {
    protected:
        OpcodeHandlersTest() : test_harness::TestHarness(parser) {}
};

TEST_F(OpcodeHandlersTest, Add8Bit) {
    SetRegisterState({{Register::A, 1}, {Register::B, 2}});
    EXPECT_EQ(0, get_instruction_ptr());
    ExecuteInstruction(0x80);
    EXPECT_EQ(1, get_instruction_ptr());
    EXPECT_REGISTER({{Register::A, 3}, {Register::B, 2}});
    EXPECT_EQ(1, get_instruction_ptr());
}

TEST_F(OpcodeHandlersTest, Add8BitDirect) {
    EXPECT_EQ(0, get_instruction_ptr());
    AssertRegisterState({{Register::A, 0}, {Register::B, 0}});
    SetRegisterState({{Register::A, 1}, {Register::B, 2}});
    EXPECT_REGISTER({{Register::A, 1}, {Register::B, 2}});

    get_rom_ptr()[get_instruction_ptr()] = 0x80;
    int actual_new_instruction_ptr = Add8Bit(get_rom_ptr(), get_instruction_ptr(), {0x80, nullptr, nullptr, nullptr});
    int expected_new_instruction_ptr = 1;
    EXPECT_EQ(expected_new_instruction_ptr, actual_new_instruction_ptr);
    EXPECT_REGISTER({{Register::A, 3}, {Register::B, 2}});
}

TEST_F(OpcodeHandlersTest, GetRegisterValue) {
    get_rom_ptr()[get_instruction_ptr()] = 0x80;
    SetRegisterState({{Register::B, 1}});

    int expected_register_value = 1;
    int actual_register_value = GetRegisterValue(get_rom_ptr(), get_instruction_ptr(), 0x80);
    EXPECT_EQ(expected_register_value, actual_register_value);
}

TEST_F(OpcodeHandlersTest, Cp8Bit) {
    SetRegisterState({{Register::A, 1}, {Register::B, 1}});
    ExecuteInstruction(0xb8);
    EXPECT_REGISTER({{Register::FZ, 1}, {Register::FN, 1}, {Register::FH, 0}, {Register::FC, 0}});

    SetRegisterState({{Register::A, 1}, {Register::B, 2}});
    ExecuteInstruction(0xb8);
    EXPECT_REGISTER({{Register::FZ, 0}, {Register::FN, 1}, {Register::FH, 1}, {Register::FC, 1}});
}

TEST_F(OpcodeHandlersTest, Sub8Bit) {
    SetRegisterState({{Register::A, 2}, {Register::B, 1}});
    EXPECT_EQ(0, get_instruction_ptr());
    ExecuteInstruction(0x90);
    EXPECT_EQ(1, get_instruction_ptr());
    EXPECT_REGISTER({{Register::A, 1}, {Register::B, 1}});
    EXPECT_EQ(1, get_instruction_ptr());
}

TEST_F(OpcodeHandlersTest, And8Bit) {
    SetRegisterState({{Register::A, 1}, {Register::B, 2}});
    ExecuteInstruction(0xA0);
    EXPECT_REGISTER({{Register::A, 0}, {Register::B, 2}});

    SetRegisterState({{Register::A, 2}, {Register::B, 2}});
    ExecuteInstruction(0xA0);
    EXPECT_REGISTER({{Register::A, 2}, {Register::B, 2}});

    SetRegisterState({{Register::A, 0}, {Register::B, 0}});
    ExecuteInstruction(0xA0);
    EXPECT_REGISTER({{Register::A, 0}, {Register::B, 0}});
}

TEST_F(OpcodeHandlersTest, Or8Bit) {
    SetRegisterState({{Register::A, 1}, {Register::B, 2}});
    ExecuteInstruction(0xB0);
    EXPECT_REGISTER({{Register::A, 3}, {Register::B, 2}});

    SetRegisterState({{Register::A, 2}, {Register::B, 2}});
    ExecuteInstruction(0xB0);
    EXPECT_REGISTER({{Register::A, 2}, {Register::B, 2}});

    SetRegisterState({{Register::A, 1}, {Register::B, 0}});
    ExecuteInstruction(0xB0);
    EXPECT_REGISTER({{Register::A, 1}, {Register::B, 0}});
}

TEST_F(OpcodeHandlersTest, Xor8Bit) {
    SetRegisterState({{Register::A, 1}, {Register::B, 2}});
    ExecuteInstruction(0xA8);
    EXPECT_REGISTER({{Register::A, 3}, {Register::B, 2}});

    SetRegisterState({{Register::A, 2}, {Register::B, 2}});
    ExecuteInstruction(0xA8);
    EXPECT_REGISTER({{Register::A, 0}, {Register::B, 2}});

    SetRegisterState({{Register::A, 0}, {Register::B, 0}});
    ExecuteInstruction(0xA8);
    EXPECT_REGISTER({{Register::A, 0}, {Register::B, 0}});
}

TEST_F(OpcodeHandlersTest, INC8Bit) {
    SetRegisterState({{Register::A, 1}});
    ExecuteInstruction(0x04);
    EXPECT_REGISTER({{Register::A, 2}});
}

TEST_F(OpcodeHandlersTest, Dec8Bit) {
    SetRegisterState({{Register::A, 1}});
    ExecuteInstruction(0x05);
    EXPECT_REGISTER({{Register::A, 0}});
}

} // namespace handlers
} // namespace back_end
