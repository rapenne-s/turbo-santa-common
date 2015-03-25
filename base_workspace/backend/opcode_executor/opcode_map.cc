#include "back_end/config.h"

#include "back_end/opcode_executor/opcode_map.h"

#include <map>
#include <vector>

namespace back_end {
namespace opcodes {

using std::map;
using std::vector;
using registers::GB_CPU;
using namespace handlers;


map<unsigned short, Opcode> CreateOpcodeMap(GB_CPU* cpu) {
  unsigned short* rA = (unsigned short*) &cpu->flag_struct.rA;
  unsigned short* rB = (unsigned short*) &cpu->bc_struct.rB;
  unsigned short* rC = (unsigned short*) &cpu->bc_struct.rC;
  unsigned short* rD = (unsigned short*) &cpu->de_struct.rD;
  unsigned short* rE = (unsigned short*) &cpu->de_struct.rE;
  unsigned short* rH = (unsigned short*) &cpu->hl_struct.rH;
  unsigned short* rL = (unsigned short*) &cpu->hl_struct.rL;
  unsigned short* rAF = &cpu->rAF;
  unsigned short* rBC = &cpu->rBC;
  unsigned short* rDE = &cpu->rDE;
  unsigned short* rHL = &cpu->rHL;
  unsigned short* rSP = &cpu->rSP;

const vector<vector<Opcode>> opcodes = {
    ToList1({{0x06, rB, 8},
            {0x0e, rC, 8},
            {0x16, rD, 8},
            {0x1e, rE, 8},
            {0x26, rH, 8},
            {0x2e, rL, 8}}, LoadN),
    ToList2({{0x7f, rA, rA, 4},
            {0x78, rA, rB, 4},
            {0x79, rA, rC, 4},
            {0x7a, rA, rD, 4},
            {0x7b, rA, rE, 4},
            {0x7c, rA, rH, 4},
            {0x7d, rA, rL, 4},
            {0x40, rB, rB, 4},
            {0x41, rB, rC, 4},
            {0x42, rB, rD, 4},
            {0x43, rB, rE, 4},
            {0x44, rB, rH, 4},
            {0x45, rB, rL, 4},
            {0x48, rC, rB, 4},
            {0x49, rC, rC, 4},
            {0x4a, rC, rD, 4},
            {0x4b, rC, rE, 4},
            {0x4c, rC, rH, 4},
            {0x4d, rC, rL, 4},
            {0x50, rD, rB, 4},
            {0x51, rD, rC, 4},
            {0x52, rD, rD, 4},
            {0x53, rD, rE, 4},
            {0x54, rD, rH, 4},
            {0x55, rD, rL, 4},
            {0x58, rE, rB, 4},
            {0x59, rE, rC, 4},
            {0x5a, rE, rD, 4},
            {0x5b, rE, rE, 4},
            {0x5c, rE, rH, 4},
            {0x5d, rE, rL, 4},
            {0x60, rH, rB, 4},
            {0x61, rH, rC, 4},
            {0x62, rH, rD, 4},
            {0x63, rH, rE, 4},
            {0x64, rH, rH, 4},
            {0x65, rH, rL, 4},
            {0x68, rL, rB, 4},
            {0x69, rL, rC, 4},
            {0x6a, rL, rD, 4},
            {0x6b, rL, rE, 4},
            {0x6c, rL, rH, 4},
            {0x6d, rL, rL, 4}}, LoadRR8Bit),
    ToList2({{0x7e, rA, rHL, 8},
            {0x46, rB, rHL, 8},
            {0x4e, rC, rHL, 8},
            {0x56, rD, rHL, 8},
            {0x5e, rE, rHL, 8},
            {0x66, rH, rHL, 8},
            {0x6e, rL, rHL, 8}}, LoadRR8BitAddress),
    ToList2({{0x70, rHL, rB, 8},
            {0x71, rHL, rC, 8},
            {0x72, rHL, rD, 8},
            {0x73, rHL, rE, 8},
            {0x74, rHL, rH, 8},
            {0x75, rHL, rL, 8}}, LoadRR8BitIntoAddress),
    ToList1({{0x36, rHL, 12}}, Load8BitLiteral),
    ToList1({{0x0A, rBC, 8},
            {0x1A, rDE, 8}}, LoadAN),
    ToList1({{0xFA, nullptr, 16}}, LoadAN16BitLiteral),
    ToList1({{0x3E, nullptr, 8}}, LoadAN8BitLiteral),
    ToList1({{0x47, rB, 4},
            {0x4F, rC, 4},
            {0x57, rD, 4},
            {0x5F, rE, 4},
            {0x67, rH, 4},
            {0x6F, rL, 4}}, LoadNA),
    ToList1({{0x02, rBC, 8},
            {0x12, rDE, 8},
            {0x77, rHL, 8}}, LoadNAAddress),
    ToList1({{0xEA, nullptr, 8}}, LoadNA16BitLiteral),
    ToList1({{0xF2, nullptr, 8}}, LoadAC),
    ToList1({{0xE2, nullptr, 8}}, LoadCA),
    ToList1({{0x3A, rHL, 8}}, LoadDecAHL),
    ToList1({{0x32, rHL, 8}}, LoadDecHLA),
    ToList1({{0x2A, rHL, 8}}, LoadIncAHL),
    ToList1({{0x22, rHL, 8}}, LoadIncHLA),
    ToList1({{0xE0, nullptr, 12}}, LoadHNA),
    ToList1({{0xF0, nullptr, 12}}, LoadHAN),
    ToList1({{0x01, rBC, 12},
            {0x11, rDE, 12},
            {0x21, rHL, 12},
            {0x31, rSP, 12}}, LoadNN),
    ToList1({{0xF9, nullptr, 8}}, LoadSPHL),
    ToList1({{0xF8, nullptr, 12}}, LoadHLSP),
    ToList1({{0x08, nullptr, 20}}, LoadNNSP),
    ToList1({{0xF5, rAF, 16},
            {0xC5, rBC, 16},
            {0xD5, rDE, 16},
            {0xE5, rHL, 16}}, Push),
    ToList1({{0xF1, rAF, 12},
            {0xC1, rBC, 12},
            {0xD1, rDE, 12},
            {0xE1, rHL, 12}}, Pop),
    ToList1({{0x87, rA, 4},
            {0x80, rB, 4},
            {0x81, rC, 4},
            {0x82, rD, 4},
            {0x83, rE, 4},
            {0x84, rH, 4},
            {0x85, rL, 4}}, Add8Bit),
    ToList1({{0x86, rHL, 8}}, Add8BitAddress),
    ToList1({{0xC6, nullptr, 8}}, Add8BitLiteral),
    ToList1({{0x8F, rA, 4},
            {0x88, rB, 4},
            {0x89, rC, 4},
            {0x8A, rD, 4},
            {0x8B, rE, 4},
            {0x8C, rH, 4},
            {0x8D, rL, 4}}, ADC8Bit),
    ToList1({{0x8E, rHL, 8}}, ADC8BitAddress),
    ToList1({{0xCE, nullptr, 8}}, ADC8BitLiteral),
    ToList1({{0x97, rA, 4},
            {0x90, rB, 4},
            {0x91, rC, 4},
            {0x92, rD, 4},
            {0x93, rE, 4},
            {0x94, rH, 4},
            {0x95, rL, 4}}, Sub8Bit),
    ToList1({{0x96, rHL, 8}}, Sub8BitAddress),
    ToList1({{0xD6, nullptr, 8}}, Sub8BitLiteral),
    ToList1({{0x9F, rA, 4},
            {0x98, rB, 4},
            {0x99, rC, 4},
            {0x9A, rD, 4},
            {0x9B, rE, 4},
            {0x9C, rH, 4},
            {0x9D, rL, 4}}, SBC8Bit),
    ToList1({{0x9E, rHL, 8}}, SBC8BitAddress),
    ToList1({{0xDE, nullptr, 8}}, SBC8BitLiteral),
    ToList1({{0xA7, rA, 4},
            {0xA0, rB, 4},
            {0xA1, rC, 4},
            {0xA2, rD, 4},
            {0xA3, rE, 4},
            {0xA4, rH, 4},
            {0xA5, rL, 4}}, And8Bit),
    ToList1({{0xA6, rHL, 8}}, And8BitAddress),
    ToList1({{0xE6, nullptr, 8}}, And8BitLiteral),
    ToList1({{0xB7, rA, 4},
            {0xB0, rB, 4},
            {0xB1, rC, 4},
            {0xB2, rD, 4},
            {0xB3, rE, 4},
            {0xB4, rH, 4},
            {0xB5, rL, 4}}, Or8Bit),
    ToList1({{0xB6, rHL, 8}}, Or8BitAddress),
    ToList1({{0xF6, nullptr, 8}}, Or8BitLiteral),
    ToList1({{0xAF, rA, 4},
            {0xA8, rB, 4},
            {0xA9, rC, 4},
            {0xAA, rD, 4},
            {0xAB, rE, 4},
            {0xAC, rH, 4},
            {0xAD, rL, 4}}, Xor8Bit),
    ToList1({{0xAE, rHL, 8}}, Xor8BitAddress),
    ToList1({{0xEE, nullptr, 8}}, Xor8BitLiteral),
    ToList1({{0xBF, rA, 4},
            {0xB8, rB, 4},
            {0xB9, rC, 4},
            {0xBA, rD, 4},
            {0xBB, rE, 4},
            {0xBC, rH, 4},
            {0xBD, rL, 4}}, Cp8Bit),
    ToList1({{0xBE, rHL, 8}}, Cp8BitAddress),
    ToList1({{0xFE, nullptr, 8}}, Cp8BitLiteral),
    ToList1({{0x3C, rA, 4},
            {0x04, rB, 4},
            {0x0C, rC, 4},
            {0x14, rD, 4},
            {0x1C, rE, 4},
            {0x24, rH, 4},
            {0x2C, rL, 4}}, Inc8Bit),
    ToList1({{0x34, rHL, 12}}, Inc8BitAddress),
    ToList1({{0x3D, rA, 4},
            {0x05, rB, 4},
            {0x0D, rC, 4},
            {0x15, rD, 4},
            {0x1D, rE, 4},
            {0x25, rH, 4},
            {0x2D, rL, 4}}, Dec8Bit),
    ToList1({{0x35, rHL, 12}}, Dec8BitAddress),
    ToList1({{0x09, rBC, 8},
            {0x19, rDE, 8},
            {0x29, rHL, 8},
            {0x39, rSP, 8}}, Add16Bit),
    ToList1({{0xE8, nullptr, 16}}, AddSPLiteral),
    ToList1({{0x03, rBC, 8},
            {0x13, rDE, 8},
            {0x23, rHL, 8},
            {0x33, rSP, 8}}, Inc16Bit),
    ToList1({{0x0B, rBC, 8},
            {0x1B, rDE, 8},
            {0x2B, rHL, 8},
            {0x3B, rSP, 8}}, Dec16Bit),
    ToList1({{0xCB37, rA, 8},
            {0xCB30, rB, 8},
            {0xCB31, rC, 8},
            {0xCB32, rD, 8},
            {0xCB33, rE, 8},
            {0xCB34, rH, 8},
            {0xCB35, rL, 8}}, Swap),
    ToList1({{0xCB36, rHL, 16}}, SwapAddress),
    ToList1({{0x27, nullptr, 4}}, DAA),
    ToList1({{0x2F, nullptr, 4}}, CPL),
    ToList1({{0x3F, nullptr, 4}}, CCF),
    ToList1({{0x37, nullptr, 4}}, SCF),
    ToList1({{0x00, nullptr, 4}}, NOP),
    ToList1({{0x76, nullptr, 4}}, Halt),
    ToList1({{0x1000, nullptr, 4}}, Stop),
    ToList1({{0xF3, nullptr, 4}}, DI),
    ToList1({{0xFB, nullptr, 4}}, EI),
    ToList1({{0x07, nullptr, 4}}, RLCA),
    ToList1({{0x17, nullptr, 4}}, RLA),
    ToList1({{0x0F, nullptr, 4}}, RRCA),
    ToList1({{0x1F, nullptr, 4}}, RRA),
    ToList1({{0xCB07, rA, 8},
            {0xCB00, rB, 8},
            {0xCB01, rC, 8},
            {0xCB02, rD, 8},
            {0xCB03, rE, 8},
            {0xCB04, rH, 8},
            {0xCB05, rL, 8}}, RLC),
    ToList1({{0xCB06, rHL, 16}}, RLCAddress),
    ToList1({{0xCB17, rA, 8},
            {0xCB10, rB, 8},
            {0xCB11, rC, 8},
            {0xCB12, rD, 8},
            {0xCB13, rE, 8},
            {0xCB14, rH, 8},
            {0xCB15, rL, 8}}, RL),
    ToList1({{0xCB16, rHL, 16}}, RLAddress),
    ToList1({{0xCB0F, rA, 8},
            {0xCB08, rB, 8},
            {0xCB09, rC, 8},
            {0xCB0A, rD, 8},
            {0xCB0B, rE, 8},
            {0xCB0C, rH, 8},
            {0xCB0D, rL, 8}}, RRC),
    ToList1({{0xCB0E, rHL, 16}}, RRCAddress),
    ToList1({{0xCB1F, rA, 8},
            {0xCB18, rB, 8},
            {0xCB19, rC, 8},
            {0xCB1A, rD, 8},
            {0xCB1B, rE, 8},
            {0xCB1C, rH, 8},
            {0xCB1D, rL, 8}}, RR),
    ToList1({{0xCB1E, rHL, 16}}, RRAddress),
    ToList1({{0xCB27, rA, 8},
            {0xCB20, rB, 8},
            {0xCB21, rC, 8},
            {0xCB22, rD, 8},
            {0xCB23, rE, 8},
            {0xCB24, rH, 8},
            {0xCB25, rL, 8}}, SLA),
    ToList1({{0xCB26, rHL, 16}}, SLAAddress),
    ToList1({{0xCB2F, rA, 8},
            {0xCB28, rB, 8},
            {0xCB29, rC, 8},
            {0xCB2A, rD, 8},
            {0xCB2B, rE, 8},
            {0xCB2C, rH, 8},
            {0xCB2D, rL, 8}}, SRA),
    ToList1({{0xCB2E, rHL, 16}}, SRAAddress),
    ToList1({{0xCB3F, rA, 8},
            {0xCB38, rB, 8},
            {0xCB39, rC, 8},
            {0xCB3A, rD, 8},
            {0xCB3B, rE, 8},
            {0xCB3C, rH, 8},
            {0xCB3D, rL, 8}}, SRL),
    ToList1({{0xCB3E, rHL, 16}}, SRLAddress),
    ToList1({{0xCB47, rA, 8},
            {0xCB40, rB, 8},
            {0xCB41, rC, 8},
            {0xCB42, rD, 8},
            {0xCB43, rE, 8},
            {0xCB44, rH, 8},
            {0xCB45, rL, 8}}, Bit),
    ToList1({{0xCB46, rHL, 16}}, BitAddress),
    ToList1({{0xCBC7, rA, 8},
            {0xCBC0, rB, 8},
            {0xCBC1, rC, 8},
            {0xCBC2, rD, 8},
            {0xCBC3, rE, 8},
            {0xCBC4, rH, 8},
            {0xCBC5, rL, 8},
            {0xCBC6, rHL, 16}}, Set),
    ToList1({{0xCB87, rA, 8},
            {0xCB80, rB, 8},
            {0xCB81, rC, 8},
            {0xCB82, rD, 8},
            {0xCB83, rE, 8},
            {0xCB84, rH, 8},
            {0xCB85, rL, 8},
            {0xCB86, rHL, 16}}, Res),
    ToList1({{0xC3, nullptr, 12}}, Jump),
    /* TODO: pass in the proper register to JP cc,nn */
    ToList1({{0xC2, nullptr, 12},
            {0xCA, nullptr, 12},
            {0xD2, nullptr, 12},
            {0xDA, nullptr, 12}}, JumpConditional),
    ToList1({{0xE9, rHL, 4}}, JumpHL),
    ToList1({{0x18, nullptr, 8}}, JumpRelative),
    /* TODO: pass in the proper register to JR cc,nn */
    ToList1({{0x20, nullptr, 8},
            {0x28, nullptr, 8},
            {0x30, nullptr, 8},
            {0x38, nullptr, 8}}, JumpRelativeConditional),
    ToList1({{0xCD, nullptr, 12}}, Call),
    /* TODO: pass in the proper register to CALL cc,nn */
    ToList1({{0xC4, nullptr, 12},
            {0xCC, nullptr, 12},
            {0xD4, nullptr, 12},
            {0xDC, nullptr, 12}}, CallConditional),
    ToList1({{0xC7, nullptr, 32},
            {0xCF, nullptr, 32},
            {0xD7, nullptr, 32},
            {0xDF, nullptr, 32},
            {0xE7, nullptr, 32},
            {0xEF, nullptr, 32},
            {0xF7, nullptr, 32},
            {0xFF, nullptr, 32}}, Restart),
    ToList1({{0xC9, nullptr, 8}}, Return),
    /* TODO: pass in the proper register to RET cc */
    ToList1({{0xC0, nullptr, 8},
            {0xC8, nullptr, 8},
            {0xD0, nullptr, 8},
            {0xD8, nullptr, 8}}, ReturnConditional),
    ToList1({{0xD9, nullptr, 8}}, ReturnInterrupt),
    // XXX: This should be removed before distribution!!!
    ToList1({{0xDD, nullptr, 8}}, HaltAndCatchFire)
};

  return ToMap(Flatten(opcodes));
}

} // namespace opcodes
} // namespace back_end