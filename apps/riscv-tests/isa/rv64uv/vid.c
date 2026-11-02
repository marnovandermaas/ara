// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1() {
  VSET(16, e8, m1);
  __asm__ volatile("vid.v v1");
  VCMP_U8(1, v1, 0, 1, 2, 3, 4, 5, 6, 7);
  VSET(10, e8, m1);

  VLOAD_8(v1, 0b00001110, 0b00000111, 0b00010000, 0b01001011, 0b00110100,
          0b01111101, 0b11001100, 0b00011000, 0b01000111, 0b00010100);
  VSET(77, e8, m1);
  asm volatile("vid.v v2");
  VCMP_U8(2, v2, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
          18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
          35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
          52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
          69, 70, 71, 72, 73, 74, 75, 76);
}

void TEST_CASE2() {
  VSET(16, e8, m1);
  VLOAD_8(v0, 85, 0, 0, 0, 0, 0, 0, 0);
  VCLEAR(v1);
  __asm__ volatile("vid.v v1, v0.t");
  VCMP_U8(3, v1, 0, 0, 2, 0, 4, 0, 6, 0);
}

// Multiple VID instructions in a row.
void TEST_CASE3() {
  VSET(16, e8, m1);
  VCLEAR(v1);
  VCLEAR(v2);
  __asm__ volatile("vid.v v1");
  __asm__ volatile("vid.v v2");
  __asm__ volatile("vid.v v3");
  __asm__ volatile("vid.v v4");
  __asm__ volatile("vid.v v5");
  __asm__ volatile("vid.v v6");
  __asm__ volatile("vid.v v7");
  __asm__ volatile("vid.v v8");
  __asm__ volatile("vadd.vv v1, v1, v8");
  __asm__ volatile("vadd.vv v2, v2, v1");
  __asm__ volatile("vxor.vv v3, v3, v3");
  VCMP_U8(4, v1, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  VCMP_U8(5, v2, 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45);
  VCMP_U8(6, v3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  enable_fp();
  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  EXIT_CHECK();
}
