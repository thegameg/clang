// RUN: %clang_cc1 %s -triple=j2-unknown-linux-gnu -S -O1 -o - | FileCheck %s

int foo(int a, int b)
// CHECK-LABEL: foo:
{
// CHECK:       mov.l r14, @-r15
  return a + b;
// CHECK-NEXT:  add [[REG1:r[45]+]], [[REG2:r[45]+]]
// CHECK-NEXT:  mov [[REG2]], r0
// CHECK-NEXT:  mov.l @r15+, r14
// CHECK-NEXT:  rts
// CHECK-NEXT:  nop
}

int sum(int a, int b);

int double_sum(int a, int b)
{
  return sum(a, b) + sum(3, b);
// CHECK-LABEL: double_sum:
// CHECK-NEXT: mov.l pr, @-r15
// CHECK-NEXT: mov.l r14, @-r15
// CHECK-NEXT: mov.l @([[CPI1:CPI[0-9]+_[0-9]+]], pc), [[REG0:r[0-9]+]]
// CHECK-NEXT: jsr [[REG0]]
// CHECK-NEXT: nop
// CHECK-NEXT: mov r0, [[REG1:r[0-9]+]]
// CHECK-NEXT: mov #3, r4
// CHECK-NEXT: jsr [[REG0]]
// CHECK-NEXT: nop
// CHECK-NEXT: add [[REG1]], r0
// CHECK-NEXT: mov.l @r15+, r14
// CHECK-NEXT: mov.l @r15+, pr
// CHECK-NEXT: rts
// CHECK-NEXT: nop

// Constant pool island.
// CHECK-NEXT: .p2align 2
// CHECK-NEXT: [[CPI1]]:
// CHECK-NEXT: .long sum
}
