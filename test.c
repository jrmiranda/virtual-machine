#include <stdio.h>

int regs[10] = {0};
int *op0, *op1, *op2;

int imm = 100;

void show(int *arr) {
  int i;
  printf("\n");
  for (i = 0; i < 10; i++) {
    printf("[%d] => %d", i, arr[i]);
    printf("\n");
  }
  printf("\n");
}

void reg_reg() {
  op0 = (regs+0);
  op1 = (regs+1);
  op2 = (regs+2);
}

void reg_imm() {
  op0 = (regs+0);
  op1 = (regs+1);
  op2 = &imm;
}

int main() {
  reg_reg();

  *op0 = *op1 + *op2;

  show(regs);

  // int a = 0b00000000111111000000000000000000;
  //
  // int b = (a & 0xE0000000) >> 29; //Type
  // int c = (a & 0x18000000) >> 27; //Class
  // int d = (a & 0x07000000) >> 25; //Op
  //
  // int e = (a & 0x00F80000) >> 19; //Reg0
  // int f = (a & 0x0007C000) >> 14; //Reg1
  // int g = (a & 0x00FFFF00) >> 8; //Imm0
  // int h = (a & 0x0007FFF8) >> 3; //Imm1

}
