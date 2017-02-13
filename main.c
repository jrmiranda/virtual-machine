/*
  16 bit Virtual Machine
  by JrMiranda
*/

#include <stdio.h>
#include <stdint.h>

#define NUM_REGS 32
#define MEM_SIZE 65536
#define PROGRAM_SIZE 1024

uint16_t regs[NUM_REGS] = {0};
uint16_t mem[MEM_SIZE] = {0};

uint16_t pc = 0;
uint32_t program[PROGRAM_SIZE] = {};

uint16_t instr, instr_type, instr_class, instr_op;

uint16_t offset0, offset1;
uint16_t *op0, *op1, *op2;
uint16_t imm = 0;

uint32_t fetch() {
  return program[pc++];
}

/*
  Stack
*/
void push() {

}

void pop() {

}

/*
  Decode Instructions
*/

void decode_reg_reg(int instr) {
  offset0 = (instr & 0x00F80000) >> 19;
  offset1 = (instr & 0x0007C000) >> 14;
  op0 = (regs + offset0);
  op1 = (regs + offset1);
}

void decode_reg_imm() {
  offset0 = (instr & 0x00F80000) >> 19;
  imm = (instr & 0x0007FFF8) >> 3;
  op0 = (regs + offset0);
  op1 = &imm;
}

void decode_reg_mem() {
  offset0 = (instr & 0x00F80000) >> 19;
  offset1 = (instr & 0x0007FFF8) >> 3;
  op0 = (regs + offset0);
  op1 = (mem + offset1);
}

void decode_mem_reg() {
  offset0 = (instr & 0x00FFFF00) >> 8;
  offset1 = (instr & 0x0007C000) >> 14;
  op0 = (mem + offset0);
  op1 = (regs + offset1);
}

void decode_reg() {
  offset0 = (instr & 0x00F80000) >> 19;
  op0 = (regs + offset0);
}

void decode_imm() {
  imm = (instr & 0x00FFFF00) >> 8;
  op0 = &imm;
}

void decode_mem() {
  offset0 = (instr & 0x00FFFF00) >> 8;
  op0 = (mem + offset0);
}

void decode(int instr) {
  instr_type = (instr & 0xE0000000) >> 29;
  instr_class = (instr & 0x18000000) >> 27;

  instr_op = (instr & 0x07000000) >> 25;

  switch (instr_type) {
    case 0:
      decode_reg_reg(instr);
      break;
    case 1:
      decode_reg_imm(instr);
      break;
    case 2:
      decode_reg_mem(instr);
      break;
    case 3:
      decode_mem_reg(instr);
      break;
    case 4:
      decode_reg(instr);
      break;
    case 5:
      decode_imm(instr);
      break;
    case 6:
      decode_mem(instr);
      break;
  }
}

/*
  Execute Instructions
*/
void data_instr() {
  switch (instr_op) {
    case 0:
    *op0 = *op1;
    break;
    case 1:
    push(op0);
    break;
    case 2:
    pop(op0);
    break;
  }
}

void arithmetic_instr() {
  switch (instr_op) {
    case 0:
    *op0 = *op0 + *op1;
    break;
    case 1:
    *op0 = *op0 - *op1;
    break;
    case 2:
    *op0 = *op0 + 1;
    break;
    case 3:
    *op0 = *op0 - 1;
    break;
  }
}

void logic_instr() {
  switch (instr_op) {
    case 0:
    *op0 = *op0 && *op1;
    break;
    case 1:
    *op0 = *op0 || *op1;
    break;
    case 2:
    *op0 = *op0 ^ *op1;
    break;
    case 3:
    *op0 = ~*op0;
    break;
  }
}

void flow_instr() {

}

void execute() {
  switch (instr_class) {
    case 0:
      data_instr();
      break;
    case 1:
      arithmetic_instr();
      break;
    case 2:
      logic_instr();
      break;
    case 3:
      flow_instr();
      break;
  }
}


int main() {

}

/*
  XXX00FFF - Data Movement
  XXX01FFF - Arithmetic
  XXX10FFF - Logic
  XXX11FFF - Control Flow

  Reg-Reg:  XXXXXXXX XXXXX XXXXX
  Reg-Imm:  XXXXXXXX XXXXX XXXXXXXXXXXXXXXX
  Reg-Mem:  XXXXXXXX XXXXX XXXXXXXXXXXXXXXX
  Mem-Reg:  XXXXXXXX XXXXXXXXXXXXXXXX XXXXX
  Reg:      XXXXXXXX XXXXX
  Imm:      XXXXXXXX XXXXXXXXXXXXXXXX
  Mem:      XXXXXXXX XXXXXXXXXXXXXXXX

*/
