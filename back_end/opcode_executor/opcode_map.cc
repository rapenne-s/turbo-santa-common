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
  unsigned char* rA = &cpu->flag_struct.rA;
  unsigned char* rB = &cpu->bc_struct.rB;
  unsigned char* rC = &cpu->bc_struct.rC;
  unsigned char* rD = &cpu->de_struct.rD;
  unsigned char* rE = &cpu->de_struct.rE;
  unsigned char* rH = &cpu->hl_struct.rH;
  unsigned char* rL = &cpu->hl_struct.rL;
  unsigned char* rAF = (unsigned char*) &cpu->rAF;
  unsigned char* rBC = (unsigned char*) &cpu->rBC;
  unsigned char* rDE = (unsigned char*) &cpu->rDE;
  unsigned char* rHL = (unsigned char*) &cpu->rHL;
  unsigned char* rSP = (unsigned char*) &cpu->rSP;

  const vector<vector<Opcode>> opcodes = {
    ToList1({{0x06, rB},
            {0x0e, rC},
            {0x16, rD},
            {0x1e, rE},
            {0x26, rH},
            {0x2e, rL}}, LoadNN),
    ToList2({{0x7f, rA, rA},
            {0x78, rA, rB},
            {0x79, rA, rC},
            {0x7a, rA, rD},
            {0x7b, rA, rE},
            {0x7c, rA, rH},
            {0x7d, rA, rL},
            {0x7e, rA, rHL},
            {0x40, rB, rB},
            {0x41, rB, rC},
            {0x42, rB, rD},
            {0x43, rB, rE},
            {0x44, rB, rH},
            {0x45, rB, rL},
            {0x46, rB, rHL},
            {0x48, rC, rB},
            {0x49, rC, rC},
            {0x4a, rC, rD},
            {0x4b, rC, rE},
            {0x4c, rC, rH},
            {0x4d, rC, rL},
            {0x4e, rC, rHL},
            {0x50, rD, rB},
            {0x51, rD, rC},
            {0x52, rD, rD},
            {0x53, rD, rE},
            {0x54, rD, rH},
            {0x55, rD, rL},
            {0x56, rD, rHL},
            {0x58, rE, rB},
            {0x59, rE, rC},
            {0x5a, rE, rD},
            {0x5b, rE, rE},
            {0x5c, rE, rH},
            {0x5d, rE, rL},
            {0x5e, rE, rHL},
            {0x60, rH, rB},
            {0x61, rH, rC},
            {0x62, rH, rD},
            {0x63, rH, rE},
            {0x64, rH, rH},
            {0x65, rH, rL},
            {0x66, rH, rHL},
            {0x68, rL, rB},
            {0x69, rL, rC},
            {0x6a, rL, rD},
            {0x6b, rL, rE},
            {0x6c, rL, rH},
            {0x6d, rL, rL},
            {0x6e, rL, rHL},
            {0x70, rHL, rB},
            {0x71, rHL, rC},
            {0x72, rHL, rD},
            {0x73, rHL, rE},
            {0x74, rHL, rH},
            {0x75, rHL, rL}
    /* {0x36, rHL, n} */}, LoadRR),
    ToList1({{0x7F, rA},
            {0x0A, rBC},
            {0x1A, rDE},
            {0xFA, nullptr},
            {0x3E, nullptr}}, LoadAN),
    ToList1({{0x47, rB},
            {0x4F, rC},
            {0x57, rD},
            {0x5F, rE},
            {0x67, rH},
            {0x6F, rL},
            {0x02, rBC},
            {0x12, rDE},
            {0x77, rHL},
            {0xEA, nullptr}}, LoadNA),
    ToList1({{0xF2, nullptr}}, LoadAC),
    ToList1({{0xE2, nullptr}}, LoadCA),
    ToList1({{0x3A, rHL}}, LoadDecAHL),
    ToList1({{0x32, rHL}}, LoadDecHLA),
    ToList1({{0x2A, rHL}}, LoadIncAHL),
    ToList1({{0x22, rHL}}, LoadIncHLA),
    ToList1({{0xE0, nullptr}}, LoadHNA),
    ToList1({{0xF0, nullptr}}, LoadHAN),
    ToList1({{0x01, rBC},
            {0x11, rDE},
            {0x21, rHL},
            {0x31, rSP}}, LoadNN),
    ToList1({{0xF9, nullptr}}, LoadSPHL),
    ToList1({{0xF8, nullptr}}, LoadHLSP),
    ToList1({{0x08, nullptr}}, LoadNNSP),
    ToList1({{0xF5, rAF},
            {0xC5, rBC},
            {0xD5, rDE},
            {0xE5, rHL}}, Push),
    ToList1({{0xF1, rAF},
            {0xC1, rBC},
            {0xD1, rDE},
            {0xE1, rHL}}, Pop),
    ToList1({{0x87, rA},
            {0x80, rB},
            {0x81, rC},
            {0x82, rD},
            {0x83, rE},
            {0x84, rH},
            {0x85, rL},
            {0x86, rHL}}, Add8Bit),
    ToList1({{0xC6, nullptr}}, Add8BitLiteral),
    ToList1({{0x8F, rA},
            {0x88, rB},
            {0x89, rC},
            {0x8A, rD},
            {0x8B, rE},
            {0x8C, rH},
            {0x8D, rL},
            {0x8E, rHL}}, ADC8Bit),
    ToList1({{0xCE, nullptr}}, ADC8BitLiteral),
    ToList1({{0x97, rA},
            {0x90, rB},
            {0x91, rC},
            {0x92, rD},
            {0x93, rE},
            {0x94, rH},
            {0x95, rL},
            {0x96, rHL}}, Sub8Bit),
    ToList1({{0xD6, nullptr}}, Sub8BitLiteral),
    ToList1({{0x9F, rA},
            {0x98, rB},
            {0x99, rC},
            {0x9A, rD},
            {0x9B, rE},
            {0x9C, rH},
            {0x9D, rL},
            {0x9E, rHL}}, SBC8Bit),
    ToList1({{0xDE, nullptr}}, SBC8BitLiteral),
    ToList1({{0xA7, rA},
            {0xA0, rB},
            {0xA1, rC},
            {0xA2, rD},
            {0xA3, rE},
            {0xA4, rH},
            {0xA5, rL},
            {0xA6, rHL}}, And8Bit),
    ToList1({{0xE6, nullptr}}, And8BitLiteral),
    ToList1({{0xB7, rA},
            {0xB0, rB},
            {0xB1, rC},
            {0xB2, rD},
            {0xB3, rE},
            {0xB4, rH},
            {0xB5, rL},
            {0xB6, rHL}}, Or8Bit),
    ToList1({{0xF6, nullptr}}, Or8BitLiteral),
    ToList1({{0xAF, rA},
            {0xA8, rB},
            {0xA9, rC},
            {0xAA, rD},
            {0xAB, rE},
            {0xAC, rH},
            {0xAD, rL},
            {0xAE, rHL}}, Xor8Bit),
    ToList1({{0xEE, nullptr}}, Xor8BitLiteral),
    ToList1({{0xBF, rA},
            {0xB8, rB},
            {0xB9, rC},
            {0xBA, rD},
            {0xBB, rE},
            {0xBC, rH},
            {0xBD, rL},
            {0xBE, rHL}}, Cp8Bit),
    ToList1({{0xFE, nullptr}}, Cp8BitLiteral),
    ToList1({{0x3C, rA},
            {0x04, rB},
            {0x0C, rC},
            {0x14, rD},
            {0x1C, rE},
            {0x24, rH},
            {0x2C, rL},
            {0x34, rHL}}, Inc8Bit),
    ToList1({{0x3D, rA},
            {0x05, rB},
            {0x0D, rC},
            {0x15, rD},
            {0x1D, rE},
            {0x25, rH},
            {0x2D, rL},
            {0x35, rHL}}, Dec8Bit),
    ToList1({{0x09, rBC},
            {0x19, rDE},
            {0x29, rHL},
            {0x39, rSP}}, Add16Bit),
    ToList1({{0xE8, nullptr}}, AddSPLiteral),
    ToList1({{0x03, rBC},
            {0x13, rDE},
            {0x23, rHL},
            {0x33, rSP}}, Inc16Bit),
    ToList1({{0x0B, rBC},
            {0x1B, rDE},
            {0x2B, rHL},
            {0x3B, rSP}}, Dec16Bit),
    ToList1({{0xCB37, rA},
            {0xCB30, rB},
            {0xCB31, rC},
            {0xCB32, rD},
            {0xCB33, rE},
            {0xCB34, rH},
            {0xCB35, rL},
            {0xCB36, rHL}}, Swap),
    ToList1({{0x27, nullptr}}, DAA),
    ToList1({{0x2F, nullptr}}, CPL),
    ToList1({{0x3F, nullptr}}, CCF),
    ToList1({{0x37, nullptr}}, SCF),
    ToList1({{0x00, nullptr}}, NOP),
    ToList1({{0x76, nullptr}}, Halt),
    ToList1({{0x1000, nullptr}}, Stop),
    ToList1({{0xF3, nullptr}}, DI),
    ToList1({{0xFB, nullptr}}, EI),
    ToList1({{0x07, nullptr}}, RLCA),
    ToList1({{0x17, nullptr}}, RLA),
    ToList1({{0x0F, nullptr}}, RRCA),
    ToList1({{0x1F, nullptr}}, RRA),
    ToList1({{0xCB07, rA},
            {0xCB00, rB},
            {0xCB01, rC},
            {0xCB02, rD},
            {0xCB03, rE},
            {0xCB04, rH},
            {0xCB05, rL},
            {0xCB06, rHL}}, RLC),
    ToList1({{0xCB17, rA},
            {0xCB10, rB},
            {0xCB11, rC},
            {0xCB12, rD},
            {0xCB13, rE},
            {0xCB14, rH},
            {0xCB15, rL},
            {0xCB16, rHL}}, RL),
    ToList1({{0xCB0F, rA},
            {0xCB08, rB},
            {0xCB09, rC},
            {0xCB0A, rD},
            {0xCB0B, rE},
            {0xCB0C, rH},
            {0xCB0D, rL},
            {0xCB0E, rHL}}, RRC),
    ToList1({{0xCB1F, rA},
            {0xCB18, rB},
            {0xCB19, rC},
            {0xCB1A, rD},
            {0xCB1B, rE},
            {0xCB1C, rH},
            {0xCB1D, rL},
            {0xCB1E, rHL}}, RR),
    ToList1({{0xCB27, rA},
            {0xCB20, rB},
            {0xCB21, rC},
            {0xCB22, rD},
            {0xCB23, rE},
            {0xCB24, rH},
            {0xCB25, rL},
            {0xCB26, rHL}}, SLA),
    ToList1({{0xCB2F, rA},
            {0xCB28, rB},
            {0xCB29, rC},
            {0xCB2A, rD},
            {0xCB2B, rE},
            {0xCB2C, rH},
            {0xCB2D, rL},
            {0xCB2E, rHL}}, SRA),
    ToList1({{0xCB3F, rA},
            {0xCB38, rB},
            {0xCB39, rC},
            {0xCB3A, rD},
            {0xCB3B, rE},
            {0xCB3C, rH},
            {0xCB3D, rL},
            {0xCB3E, rHL}}, SRL),
    ToList1({{0xCB47, rA},
            {0xCB40, rB},
            {0xCB41, rC},
            {0xCB42, rD},
            {0xCB43, rE},
            {0xCB44, rH},
            {0xCB45, rL},
            {0xCB56, rHL}}, Bit),
    ToList1({{0xCBC7, rA},
            {0xCBC0, rB},
            {0xCBC1, rC},
            {0xCBC2, rD},
            {0xCBC3, rE},
            {0xCBC4, rH},
            {0xCBC5, rL},
            {0xCBC6, rHL}}, Set),
    ToList1({{0xCB87, rA},
            {0xCB80, rB},
            {0xCB81, rC},
            {0xCB82, rD},
            {0xCB83, rE},
            {0xCB84, rH},
            {0xCB85, rL},
            {0xCB86, rHL}}, Res),
    ToList1({{0xC3, nullptr}}, Jump),
    /* TODO: pass in the proper register to JP cc,nn */
    ToList1({{0xC2, nullptr},
            {0xCA, nullptr},
            {0xD2, nullptr},
            {0xDA, nullptr}}, JumpConditional),
    ToList1({{0xE9, rHL}}, JumpHL),
    ToList1({{0x18, nullptr}}, JumpRelative),
    /* TODO: pass in the proper register to JR cc,nn */
    ToList1({{0x20, nullptr},
            {0x28, nullptr},
            {0x30, nullptr},
            {0x38, nullptr}}, JumpRelativeConditional),
    ToList1({{0xCD, nullptr}}, Call),
    /* TODO: pass in the proper register to CALL cc,nn */
    ToList1({{0xC4, nullptr},
            {0xCC, nullptr},
            {0xD4, nullptr},
            {0xDC, nullptr}}, CallConditional),
    ToList1({{0xC7, nullptr},
            {0xCF, nullptr},
            {0xD7, nullptr},
            {0xDF, nullptr},
            {0xE7, nullptr},
            {0xEF, nullptr},
            {0xF7, nullptr},
            {0xFF, nullptr}}, Restart),
    ToList1({{0xC9, nullptr}}, Return),
    /* TODO: pass in the proper register to RET cc */
    ToList1({{0xC0, nullptr},
            {0xC8, nullptr},
            {0xD0, nullptr},
            {0xD8, nullptr}}, ReturnConditional),
    ToList1({{0xD9, nullptr}}, ReturnInterrupt)
  };

  return ToMap(Flatten(opcodes));
}

} // namespace opcodes
} // namespace back_end
