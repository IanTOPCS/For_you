ld0:
	mov p1, #0xc0
	jnb p2.0, ldF
	jmp ld1

ld1:
	mov p1, #0xf9
	jnb p2.0, ld0
	jmp ld2

ld2:
	mov p1, #0xa4
	jnb p2.0, ld1
	jmp ld3

ld3:
	mov p1, #0xb0
	jnb p2.0, ld2
	jmp ld4

ld4:
	mov p1, #0x99
	jnb p2.0, ld3
	jmp ld5

ld5:
	mov p1, #0x92
	jnb p2.0, ld4
	jmp ld6

ld6:
	mov p1, #0xa0
	jnb p2.0, ld5
	jmp ld7

ld7:
	mov p1, #0xd8
	jnb p2.0, ld6
	jmp ld8

ld8:
	mov p1, #0x80
	jnb p2.0, ld7
	jmp ld9

ld9:
	mov p1, #0x90
	jnb p2.0, ld8
	jmp lda

lda:
	mov p1, #0x88
	jnb p2.0, ld9
	jmp ldb

ldb:
	mov p1, #0x83
	jnb p2.0, lda
	jmp ldc

ldc:
	mov p1, #0xc6
	jnb p2.0, ldb
	jmp ldd

ldd:
	mov p1, #0xa1
	jnb p2.0, ldc
	jmp lde

lde:
  mov p1, #0x86
  jnb p2.0, ldd
  jmp ldf

ldf:
	mov p1, #0x8e
	jnb p2.0, ldd
	jmp ld0