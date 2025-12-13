Interesting, so the assembler defines far more of the pseudo-instructions than I previously thought


Let's just assemble the ten most important instructions and deal with the rest later:

1. addi 
2. add
3. and
4. or
5. sll
6. srl
7. beq
8. bne
9. blt
10. bge
11. lui
12. auipc


ISA defined:
1. lui
2. auipc
3. addi
4. slti
5. xori
6. ori
7. andi
8. slli
9. srli
10. srai
11. add
12. sub
13. sll
14. slt
15. sltu
16. xor
17. srl
18. sra
19. or
20. and
21. fence
22. fence.i
23. csrrw
24. csrrs
25. csrrc
26. csrrwi
27. csrrsi
28. csrrci
29. ecall
30. ebreak
31. uret
32. sret
33. mret
34. wfi
35. sfence.vma
36. lb
37. lh
38. lw
39. lbu
40. lhu
41. sb
42. sw
43. jal
44. jalr
45. beq
46. bne
47. blt
48. bge
49. bltu
50. bgeu





1. lui
2. auipc rd, imm20 loads rd = pc + imm20, for pc-relative addressing. auipc is used in pseudo-instructions LA, CALL, or even just getting the current pc by running auipc t0, 0.
3. addi 
4. xori
5. 


Assembler defined:
1. li
2. la
3. call
