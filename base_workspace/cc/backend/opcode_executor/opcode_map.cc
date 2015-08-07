#include "cc/backend/opcode_executor/opcode_map.h"

#include <map>
#include <vector>
#include "cc/backend/opcode_executor/opcode_handlers.h"

namespace backend {
namespace opcode_executor {

using std::vector;

std::map<uint16_t, OpcodeHandler> CreateOpcodeMap() {
  return {
        {0x06, LoadN},
        {0x0e, LoadN},
        {0x16, LoadN},
        {0x1e, LoadN},
        {0x26, LoadN},
        {0x2e, LoadN},
        {0x7f, LoadRR8Bit},
        {0x78, LoadRR8Bit},
        {0x79, LoadRR8Bit},
        {0x7a, LoadRR8Bit},
        {0x7b, LoadRR8Bit},
        {0x7c, LoadRR8Bit},
        {0x7d, LoadRR8Bit},
        {0x40, LoadRR8Bit},
        {0x41, LoadRR8Bit},
        {0x42, LoadRR8Bit},
        {0x43, LoadRR8Bit},
        {0x44, LoadRR8Bit},
        {0x45, LoadRR8Bit},
        {0x48, LoadRR8Bit},
        {0x49, LoadRR8Bit},
        {0x4a, LoadRR8Bit},
        {0x4b, LoadRR8Bit},
        {0x4c, LoadRR8Bit},
        {0x4d, LoadRR8Bit},
        {0x50, LoadRR8Bit},
        {0x51, LoadRR8Bit},
        {0x52, LoadRR8Bit},
        {0x53, LoadRR8Bit},
        {0x54, LoadRR8Bit},
        {0x55, LoadRR8Bit},
        {0x58, LoadRR8Bit},
        {0x59, LoadRR8Bit},
        {0x5a, LoadRR8Bit},
        {0x5b, LoadRR8Bit},
        {0x5c, LoadRR8Bit},
        {0x5d, LoadRR8Bit},
        {0x60, LoadRR8Bit},
        {0x61, LoadRR8Bit},
        {0x62, LoadRR8Bit},
        {0x63, LoadRR8Bit},
        {0x64, LoadRR8Bit},
        {0x65, LoadRR8Bit},
        {0x68, LoadRR8Bit},
        {0x69, LoadRR8Bit},
        {0x6a, LoadRR8Bit},
        {0x6b, LoadRR8Bit},
        {0x6c, LoadRR8Bit},
        {0x6d, LoadRR8Bit},
        {0x7e, LoadRR8BitAddress},
        {0x46, LoadRR8BitAddress},
        {0x4e, LoadRR8BitAddress},
        {0x56, LoadRR8BitAddress},
        {0x5e, LoadRR8BitAddress},
        {0x66, LoadRR8BitAddress},
        {0x6e, LoadRR8BitAddress}, 
        {0x70, LoadRR8BitIntoAddress},
        {0x71, LoadRR8BitIntoAddress},
        {0x72, LoadRR8BitIntoAddress},
        {0x73, LoadRR8BitIntoAddress},
        {0x74, LoadRR8BitIntoAddress},
        {0x75, LoadRR8BitIntoAddress}, 
        {0x36, Load8BitLiteral},
        {0x0A, LoadAN},
        {0x1A, LoadAN}, 
        {0xFA, LoadAN16BitLiteral},
        {0x3E, LoadAN8BitLiteral},
        {0x47, LoadNA},
        {0x4F, LoadNA},
        {0x57, LoadNA},
        {0x5F, LoadNA},
        {0x67, LoadNA},
        {0x6F, LoadNA}, 
        {0x02, LoadNAAddress},
        {0x12, LoadNAAddress},
        {0x77, LoadNAAddress}, 
        {0xEA, LoadNA16BitLiteral},
        {0xF2, LoadAC},
        {0xE2, LoadCA},
        {0x3A, LoadDecAHL},
        {0x32, LoadDecHLA},
        {0x2A, LoadIncAHL},
        {0x22, LoadIncHLA},
        {0xE0, LoadHNA},
        {0xF0, LoadHAN},
        {0x01, LoadNN},
        {0x11, LoadNN},
        {0x21, LoadNN},
        {0x31, LoadNN}, 
        {0xF9, LoadSPHL},
        {0xF8, LoadHLSP},
        {0x08, LoadNNSP},
        {0xF5, Push},
        {0xC5, Push},
        {0xD5, Push},
        {0xE5, Push}, 
        {0xF1, Pop},
        {0xC1, Pop},
        {0xD1, Pop},
        {0xE1, Pop}, 
        {0x87, Add8Bit},
        {0x80, Add8Bit},
        {0x81, Add8Bit},
        {0x82, Add8Bit},
        {0x83, Add8Bit},
        {0x84, Add8Bit},
        {0x85, Add8Bit}, 
        {0x86, Add8BitAddress},
        {0xC6, Add8BitLiteral},
        {0x8F, ADC8Bit},
        {0x88, ADC8Bit},
        {0x89, ADC8Bit},
        {0x8A, ADC8Bit},
        {0x8B, ADC8Bit},
        {0x8C, ADC8Bit},
        {0x8D, ADC8Bit},
        {0x8E, ADC8BitAddress},
        {0xCE, ADC8BitLiteral},
        {0x97, Sub8Bit},
        {0x90, Sub8Bit},
        {0x91, Sub8Bit},
        {0x92, Sub8Bit},
        {0x93, Sub8Bit},
        {0x94, Sub8Bit},
        {0x95, Sub8Bit}, 
        {0x96, Sub8BitAddress},
        {0xD6, Sub8BitLiteral},
        {0x9F, SBC8Bit},
        {0x98, SBC8Bit},
        {0x99, SBC8Bit},
        {0x9A, SBC8Bit},
        {0x9B, SBC8Bit},
        {0x9C, SBC8Bit},
        {0x9D, SBC8Bit}, 
        {0x9E, SBC8BitAddress},
        {0xDE, SBC8BitLiteral},
        {0xA7, And8Bit},
        {0xA0, And8Bit},
        {0xA1, And8Bit},
        {0xA2, And8Bit},
        {0xA3, And8Bit},
        {0xA4, And8Bit},
        {0xA5, And8Bit}, 
        {0xA6, And8BitAddress},
        {0xE6, And8BitLiteral},
        {0xB7, Or8Bit},
        {0xB0, Or8Bit},
        {0xB1, Or8Bit},
        {0xB2, Or8Bit},
        {0xB3, Or8Bit},
        {0xB4, Or8Bit},
        {0xB5, Or8Bit}, 
        {0xB6, Or8BitAddress},
        {0xF6, Or8BitLiteral},
        {0xAF, Xor8Bit},
        {0xA8, Xor8Bit},
        {0xA9, Xor8Bit},
        {0xAA, Xor8Bit},
        {0xAB, Xor8Bit},
        {0xAC, Xor8Bit},
        {0xAD, Xor8Bit}, 
        {0xAE, Xor8BitAddress},
        {0xEE, Xor8BitLiteral},
        {0xBF, Cp8Bit},
        {0xB8, Cp8Bit},
        {0xB9, Cp8Bit},
        {0xBA, Cp8Bit},
        {0xBB, Cp8Bit},
        {0xBC, Cp8Bit},
        {0xBD, Cp8Bit}, 
        {0xBE, Cp8BitAddress},
        {0xFE, Cp8BitLiteral},
        {0x3C, Inc8Bit},
        {0x04, Inc8Bit},
        {0x0C, Inc8Bit},
        {0x14, Inc8Bit},
        {0x1C, Inc8Bit},
        {0x24, Inc8Bit},
        {0x2C, Inc8Bit}, 
        {0x34, Inc8BitAddress},
        {0x3D, Dec8Bit},
        {0x05, Dec8Bit},
        {0x0D, Dec8Bit},
        {0x15, Dec8Bit},
        {0x1D, Dec8Bit},
        {0x25, Dec8Bit},
        {0x2D, Dec8Bit}, 
        {0x35, Dec8BitAddress},
        {0x09, Add16Bit},
        {0x19, Add16Bit},
        {0x29, Add16Bit},
        {0x39, Add16Bit}, 
        {0xE8, AddSPLiteral},
        {0x03, Inc16Bit},
        {0x13, Inc16Bit},
        {0x23, Inc16Bit},
        {0x33, Inc16Bit}, 
        {0x0B, Dec16Bit},
        {0x1B, Dec16Bit},
        {0x2B, Dec16Bit},
        {0x3B, Dec16Bit}, 
        {0xCB37, Swap},
        {0xCB30, Swap},
        {0xCB31, Swap},
        {0xCB32, Swap},
        {0xCB33, Swap},
        {0xCB34, Swap},
        {0xCB35, Swap}, 
        {0xCB36, SwapAddress},
        {0x27, DAA},
        {0x2F, CPL},
        {0x3F, CCF},
        {0x37, SCF},
        {0x00, NOP},
        {0x76, Halt},
        {0x1000, Stop},
        {0xF3, DI},
        {0xFB, EI},
        {0x07, RLCA},
        {0x17, RLA},
        {0x0F, RRCA},
        {0x1F, RRA},
        {0xCB07, RLC},
        {0xCB00, RLC},
        {0xCB01, RLC},
        {0xCB02, RLC},
        {0xCB03, RLC},
        {0xCB04, RLC},
        {0xCB05, RLC}, 
        {0xCB06, RLCAddress},
        {0xCB17, RL},
        {0xCB10, RL},
        {0xCB11, RL},
        {0xCB12, RL},
        {0xCB13, RL},
        {0xCB14, RL},
        {0xCB15, RL}, 
        {0xCB16, RLAddress},
        {0xCB0F, RRC},
        {0xCB08, RRC},
        {0xCB09, RRC},
        {0xCB0A, RRC},
        {0xCB0B, RRC},
        {0xCB0C, RRC},
        {0xCB0D, RRC}, 
        {0xCB0E, RRCAddress},
        {0xCB1F, RR},
        {0xCB18, RR},
        {0xCB19, RR},
        {0xCB1A, RR},
        {0xCB1B, RR},
        {0xCB1C, RR},
        {0xCB1D, RR}, 
        {0xCB1E, RRAddress},
        {0xCB27, SLA},
        {0xCB20, SLA},
        {0xCB21, SLA},
        {0xCB22, SLA},
        {0xCB23, SLA},
        {0xCB24, SLA},
        {0xCB25, SLA}, 
        {0xCB26, SLAAddress},
        {0xCB2F, SRA},
        {0xCB28, SRA},
        {0xCB29, SRA},
        {0xCB2A, SRA},
        {0xCB2B, SRA},
        {0xCB2C, SRA},
        {0xCB2D, SRA}, 
        {0xCB2E, SRAAddress},
        {0xCB3F, SRL},
        {0xCB38, SRL},
        {0xCB39, SRL},
        {0xCB3A, SRL},
        {0xCB3B, SRL},
        {0xCB3C, SRL},
        {0xCB3D, SRL}, 
        {0xCB3E, SRLAddress},
        {0xCB47, Bit},
        {0xCB40, Bit},
        {0xCB41, Bit},
        {0xCB42, Bit},
        {0xCB43, Bit},
        {0xCB44, Bit},
        {0xCB45, Bit}, 
        {0xCB46, BitAddress},
        {0xCBC7, Set},
        {0xCBC0, Set},
        {0xCBC1, Set},
        {0xCBC2, Set},
        {0xCBC3, Set},
        {0xCBC4, Set},
        {0xCBC5, Set},
        {0xCBC6, Set}, 
        {0xCB87, Res},
        {0xCB80, Res},
        {0xCB81, Res},
        {0xCB82, Res},
        {0xCB83, Res},
        {0xCB84, Res},
        {0xCB85, Res},
        {0xCB86, Res}, 
        {0xC3, Jump},
        {0xC2, JumpConditional},
        {0xCA, JumpConditional},
        {0xD2, JumpConditional},
        {0xDA, JumpConditional}, 
        {0xE9, JumpHL},
        {0x18, JumpRelative},
        {0x20, JumpRelativeConditional},
        {0x28, JumpRelativeConditional},
        {0x30, JumpRelativeConditional},
        {0x38, JumpRelativeConditional}, 
        {0xCD, Call},
        {0xC4, CallConditional},
        {0xCC, CallConditional},
        {0xD4, CallConditional},
        {0xDC, CallConditional}, 
        {0xC7, Restart},
        {0xCF, Restart},
        {0xD7, Restart},
        {0xDF, Restart},
        {0xE7, Restart},
        {0xEF, Restart},
        {0xF7, Restart},
        {0xFF, Restart}, 
        {0xC9, Return},
        {0xC0, ReturnConditional},
        {0xC8, ReturnConditional},
        {0xD0, ReturnConditional},
        {0xD8, ReturnConditional}, 
        {0xD9, ReturnInterrupt},
  };
}

} // namespace opcodes
} // namespace backend
