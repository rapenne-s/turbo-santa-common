#include "back_end/opcode_executor/opcode_executor.h"
#include "back_end/memory/interrupt_flag.h"
#include "back_end/opcode_executor/opcode_handlers.h"
#include "back_end/opcode_executor/registers.h"
#include <glog/logging.h>

namespace back_end {
namespace handlers {

using std::unique_ptr;
using graphics::Screen;
using graphics::ScreenRaster;
using opcodes::CreateOpcodeMap;
using opcodes::Opcode;
using memory::MemoryMapper;
using memory::InterruptEnable;
using memory::InterruptFlag;

class NullScreen : public Screen {
 public:
  virtual void Draw(const ScreenRaster&) {}
}; 

OpcodeExecutor::OpcodeExecutor() :
    graphics_controller_(&memory_mapper_, new NullScreen()) {
  // TODO(Diego): It acutally starts at something like 0x100.
  cpu_.rPC = 0x0000;
  opcode_map = CreateOpcodeMap(&cpu_);
}

OpcodeExecutor::OpcodeExecutor(unsigned char* rom, long size) :
    graphics_controller_(&memory_mapper_, new NullScreen()) {
  cpu_.rPC = 0x0000;
  opcode_map = CreateOpcodeMap(&cpu_);
  memory_mapper_ = MemoryMapper(rom, size);
}

OpcodeExecutor::OpcodeExecutor(Screen* screen) : 
    memory_mapper_(true), graphics_controller_(&memory_mapper_, screen) {
  cpu_.rPC = 0x0000;
  opcode_map = CreateOpcodeMap(&cpu_);
}

unsigned int OpcodeExecutor::ReadInstruction() {
  HandleInterrupts(); // Before a fetch we must check for and handle interrupts.
  unsigned short instruction_ptr = cpu_.rPC;
  unsigned short opcode = memory_mapper_.Read(instruction_ptr);

  unsigned short opcode_msb = memory_mapper_.Read(instruction_ptr + 1);
  
  if (opcode_msb == 0xCB || (opcode_msb == 0x10 && opcode == 0x00)) {
    instruction_ptr++;
    opcode = opcode_msb << 8 | opcode;
  }
  cpu_.rPC = instruction_ptr;

  Opcode opcode_struct;
  auto opcode_iter = opcode_map.find(opcode);
  if (opcode_iter == opcode_map.end()) {
    LOG(FATAL) << "Opcode instruction, " << std::hex << opcode << " does not exist.";
  } else {
    opcode_struct = opcode_iter->second;
  }

  ExecutorContext context(&interrupt_master_enable_,
                          &cpu_.rPC,
                          &opcode_struct,
                          &memory_mapper_,
                          &cpu_);
  cpu_.rPC = opcode_struct.handler(&context);

  graphics_controller_.Tick(opcode_struct.clock_cycles);

  return context.opcode->clock_cycles;
}

// 1) Check interrupt_master_enable_ (IME)
// 2) Check to see if any interrupt flags that are enabled
// 3) Push PC (as if CALL was performed), set PC to interrupt address, disable IME
void OpcodeExecutor::HandleInterrupts() {
  if (interrupt_master_enable_ && CheckInterrupts()) {
    handlers::PushRegister(&memory_mapper_, &cpu_, &cpu_.rPC);
    interrupt_master_enable_ = false;

    InterruptFlag* interrupt_flag = memory_mapper_.interrupt_flag();
    InterruptEnable* interrupt_enable = memory_mapper_.interrupt_enable();
    if (interrupt_flag->v_blank() && interrupt_enable->v_blank()) {
      cpu_.rPC = 0x0040;
    } else if (interrupt_flag->lcd_stat() && interrupt_enable->lcd_stat()) {
      cpu_.rPC = 0x0048;
    } else if (interrupt_flag->timer() && interrupt_enable->timer()) {
      cpu_.rPC = 0x0050;
    } else if (interrupt_flag->serial() && interrupt_enable->serial()) {
      cpu_.rPC = 0x0058;
    } else if (interrupt_flag->joypad() && interrupt_enable->joypad()) {
      cpu_.rPC = 0x0060;
    }
  }
}

bool OpcodeExecutor::CheckInterrupts() {
  InterruptFlag* interrupt_flag = memory_mapper_.interrupt_flag();
  InterruptEnable* interrupt_enable = memory_mapper_.interrupt_enable();
  return (interrupt_flag->v_blank() && interrupt_enable->v_blank()) ||
      (interrupt_flag->lcd_stat() && interrupt_enable->lcd_stat()) ||
      (interrupt_flag->timer() && interrupt_enable->timer()) ||
      (interrupt_flag->serial() && interrupt_enable->serial()) ||
      (interrupt_flag->joypad() && interrupt_enable->joypad());
}

} // namespace handlers
} // namespace back_end
