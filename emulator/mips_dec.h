/*
Binary decoder synthesized by SimIt-MIPS version 1.0

Input statistics 
Total entries  : 463
Unique labels  : 92
Shannon entropy     : 6.50779
Huffman tree height : 6.6044

Decoder characteristics 
Gamma          : 0.25
1 bit only     : 0
Average height : 2.52445
Maximum height : 6
Minimum height : 1
Table entries  : 300
Total nodes    : 79
*/

_STUB_DEC(stub_0_0)
_STUB_DEC(stub_0_1)
_STUB_DEC(stub_0_2)
_STUB_DEC(stub_0_3)
_STUB_DEC(stub_0_34)
_STUB_DEC(stub_0_35)
_STUB_DEC(stub_1_0)
_STUB_DEC(stub_3_8)
_STUB_DEC(stub_5_0)
_STUB_DEC(stub_5_1)
_STUB_DEC(stub_5_2)
_STUB_DEC(stub_5_3)
_STUB_DEC(stub_5_4)
_STUB_DEC(stub_5_5)
_STUB_DEC(stub_5_6)
_STUB_DEC(stub_5_7)

/*
Table begin: index=0 size=463
Mask=0xffffffff	DMask=0x00000000	CMask=0x00000000	Sig=0x38000000
Prob=91	Entropy=6.50779465	HTreeHeight=6.6043956
-------------------------------------------------------------------
mask=0xffe0003f	sig=0x46200005	prob=0.010989011	name=abs_d
mask=0xffe0003f	sig=0x46000005	prob=0.010989011	name=abs_s
mask=0xfc00003f	sig=0x00000020	prob=0.010989011	name=add
mask=0xffe0003f	sig=0x46200000	prob=0.010989011	name=add_d
mask=0xffe0003f	sig=0x46000000	prob=0.010989011	name=add_s
mask=0xfc000000	sig=0x20000000	prob=0.010989011	name=addi
mask=0xfc000000	sig=0x24000000	prob=0.010989011	name=addiu
mask=0xfc00003f	sig=0x00000021	prob=0.010989011	name=addu
mask=0xfc00003f	sig=0x00000024	prob=0.010989011	name=and
mask=0xfc000000	sig=0x30000000	prob=0.010989011	name=andi
mask=0xffe30000	sig=0x45000000	prob=0.010989011	name=bc1f
mask=0xffe30000	sig=0x45010000	prob=0.010989011	name=bc1t
mask=0xfc000000	sig=0x10000000	prob=0.010989011	name=beq
mask=0xfc1f0000	sig=0x04010000	prob=0.010989011	name=bgez
mask=0xfc1f0000	sig=0x04110000	prob=0.010989011	name=bgezal
mask=0xfc000000	sig=0x1c000000	prob=0.010989011	name=bgtz
mask=0xfc000000	sig=0x18000000	prob=0.010989011	name=blez
mask=0xfc1f0000	sig=0x04000000	prob=0.010989011	name=bltz
mask=0xfc1f0000	sig=0x04100000	prob=0.010989011	name=bltzal
mask=0xfc000000	sig=0x14000000	prob=0.010989011	name=bne
mask=0xfc00003f	sig=0x0000000d	prob=0.010989011	name=brk
mask=0xffe00030	sig=0x46200030	prob=0.010989011	name=c_cond_d
mask=0xffe00030	sig=0x46000030	prob=0.010989011	name=c_cond_s
mask=0xffe00000	sig=0x44400000	prob=0.010989011	name=cfc1
mask=0xffe00000	sig=0x44c00000	prob=0.010989011	name=ctc1
mask=0xffe0003f	sig=0x46000021	prob=0.010989011	name=cvt_d_s
mask=0xffe0003f	sig=0x46800021	prob=0.010989011	name=cvt_d_w
mask=0xffe0003f	sig=0x46200020	prob=0.010989011	name=cvt_s_d
mask=0xffe0003f	sig=0x46800020	prob=0.010989011	name=cvt_s_w
mask=0xffe0003f	sig=0x46200024	prob=0.010989011	name=cvt_w_d
mask=0xffe0003f	sig=0x46000024	prob=0.010989011	name=cvt_w_s
mask=0xfc00003f	sig=0x0000001a	prob=0.010989011	name=div
mask=0xffe0003f	sig=0x46200003	prob=0.010989011	name=div_d
mask=0xffe0003f	sig=0x46000003	prob=0.010989011	name=div_s
mask=0xfc00003f	sig=0x0000001b	prob=0.010989011	name=divu
mask=0xfc000000	sig=0x08000000	prob=0.010989011	name=j
mask=0xfc000000	sig=0x0c000000	prob=0.010989011	name=jal
mask=0xfc00003f	sig=0x00000009	prob=0.010989011	name=jalr
mask=0xfc00003f	sig=0x00000008	prob=0.010989011	name=jr
mask=0xfc000000	sig=0x80000000	prob=0.010989011	name=lb
mask=0xfc000000	sig=0x90000000	prob=0.010989011	name=lbu
mask=0xfc000000	sig=0x84000000	prob=0.010989011	name=lh
mask=0xfc000000	sig=0x94000000	prob=0.010989011	name=lhu
mask=0xfc000000	sig=0xc0000000	prob=0.010989011	name=ll
mask=0xfc000000	sig=0x3c000000	prob=0.010989011	name=lui
mask=0xfc000000	sig=0x8c000000	prob=0.010989011	name=lw
mask=0xfc000000	sig=0xc4000000	prob=0.010989011	name=lwc1
mask=0xfc000000	sig=0x88000000	prob=0.010989011	name=lwl
mask=0xfc000000	sig=0x98000000	prob=0.010989011	name=lwr
mask=0xffe00000	sig=0x44000000	prob=0.010989011	name=mfc1
mask=0xfc00003f	sig=0x00000010	prob=0.010989011	name=mfhi
mask=0xfc00003f	sig=0x00000012	prob=0.010989011	name=mflo
mask=0xffe0003f	sig=0x46200006	prob=0.010989011	name=mov_d
mask=0xffe0003f	sig=0x46000006	prob=0.010989011	name=mov_s
mask=0xffe00000	sig=0x44800000	prob=0.010989011	name=mtc1
mask=0xfc00003f	sig=0x00000011	prob=0.010989011	name=mthi
mask=0xfc00003f	sig=0x00000013	prob=0.010989011	name=mtlo
mask=0xffe0003f	sig=0x46200002	prob=0.010989011	name=mul_d
mask=0xffe0003f	sig=0x46000002	prob=0.010989011	name=mul_s
mask=0xfc00003f	sig=0x00000018	prob=0.010989011	name=mult
mask=0xfc00003f	sig=0x00000019	prob=0.010989011	name=multu
mask=0xffe0003f	sig=0x46200007	prob=0.010989011	name=neg_d
mask=0xffe0003f	sig=0x46000007	prob=0.010989011	name=neg_s
mask=0xfc00007f	sig=0x00000040	prob=0.000549450549	name=sll
mask=0xfc0000bf	sig=0x00000080	prob=0.000549450549	name=sll
mask=0xfc00013f	sig=0x00000100	prob=0.000549450549	name=sll
mask=0xfc00023f	sig=0x00000200	prob=0.000549450549	name=sll
mask=0xfc00043f	sig=0x00000400	prob=0.000549450549	name=sll
mask=0xfc00083f	sig=0x00000800	prob=0.000549450549	name=sll
mask=0xfc00103f	sig=0x00001000	prob=0.000549450549	name=sll
mask=0xfc00203f	sig=0x00002000	prob=0.000549450549	name=sll
mask=0xfc00403f	sig=0x00004000	prob=0.000549450549	name=sll
mask=0xfc00803f	sig=0x00008000	prob=0.000549450549	name=sll
mask=0xfc01003f	sig=0x00010000	prob=0.000549450549	name=sll
mask=0xfc02003f	sig=0x00020000	prob=0.000549450549	name=sll
mask=0xfc04003f	sig=0x00040000	prob=0.000549450549	name=sll
mask=0xfc08003f	sig=0x00080000	prob=0.000549450549	name=sll
mask=0xfc10003f	sig=0x00100000	prob=0.000549450549	name=sll
mask=0xfc20003f	sig=0x00200000	prob=0.000549450549	name=sll
mask=0xfc40003f	sig=0x00400000	prob=0.000549450549	name=sll
mask=0xfc80003f	sig=0x00800000	prob=0.000549450549	name=sll
mask=0xfd00003f	sig=0x01000000	prob=0.000549450549	name=sll
mask=0xfe00003f	sig=0x02000000	prob=0.000549450549	name=sll
mask=0xfc00003f	sig=0x00000027	prob=0.010989011	name=nor
mask=0xb8a8003b	sig=0x00a80001	prob=1.0989011e-012	name=null
mask=0xb928003b	sig=0x01280001	prob=1.0989011e-012	name=null
mask=0xb928002f	sig=0x01280005	prob=1.0989011e-012	name=null
mask=0xbb04003b	sig=0x03040001	prob=1.0989011e-012	name=null
mask=0xbb04002f	sig=0x03040005	prob=1.0989011e-012	name=null
mask=0xb924003b	sig=0x01240001	prob=1.0989011e-012	name=null
mask=0xb924002f	sig=0x01240005	prob=1.0989011e-012	name=null
mask=0xb988003b	sig=0x01880001	prob=1.0989011e-012	name=null
mask=0xb988002f	sig=0x01880005	prob=1.0989011e-012	name=null
mask=0xbb08003b	sig=0x03080001	prob=1.0989011e-012	name=null
mask=0xb8a8002f	sig=0x00a80005	prob=1.0989011e-012	name=null
mask=0xb984003b	sig=0x01840001	prob=1.0989011e-012	name=null
mask=0xb984002f	sig=0x01840005	prob=1.0989011e-012	name=null
mask=0xb8a4003b	sig=0x00a40001	prob=1.0989011e-012	name=null
mask=0xb8a4002f	sig=0x00a40005	prob=1.0989011e-012	name=null
mask=0xb8a2003b	sig=0x00a20001	prob=1.0989011e-012	name=null
mask=0xb8a2002f	sig=0x00a20005	prob=1.0989011e-012	name=null
mask=0xbc00003b	sig=0x00000001	prob=1.0989011e-012	name=null
mask=0xbc00002f	sig=0x00000005	prob=1.0989011e-012	name=null
mask=0xba28003b	sig=0x00280001	prob=1.0989011e-012	name=null
mask=0xba28002f	sig=0x00280005	prob=1.0989011e-012	name=null
mask=0xba24003b	sig=0x00240001	prob=1.0989011e-012	name=null
mask=0xba24002f	sig=0x00240005	prob=1.0989011e-012	name=null
mask=0xba22003b	sig=0x00220001	prob=1.0989011e-012	name=null
mask=0xb868002f	sig=0x00680005	prob=1.0989011e-012	name=null
mask=0xbe220000	sig=0x04220000	prob=1.0989011e-012	name=null
mask=0xfc080000	sig=0x04080000	prob=1.0989011e-012	name=null
mask=0xfc040000	sig=0x04040000	prob=1.0989011e-012	name=null
mask=0xfc020000	sig=0x04020000	prob=1.0989011e-012	name=null
mask=0xbd020000	sig=0x05020000	prob=1.0989011e-012	name=null
mask=0xc2000027	sig=0x42000004	prob=1.0989011e-012	name=null
mask=0xba48003b	sig=0x02480001	prob=1.0989011e-012	name=null
mask=0xba48002f	sig=0x02480005	prob=1.0989011e-012	name=null
mask=0xb948003b	sig=0x01480001	prob=1.0989011e-012	name=null
mask=0xb948002f	sig=0x01480005	prob=1.0989011e-012	name=null
mask=0xb868003b	sig=0x00680001	prob=1.0989011e-012	name=null
mask=0xbb08002f	sig=0x03080005	prob=1.0989011e-012	name=null
mask=0xba44003b	sig=0x02440001	prob=1.0989011e-012	name=null
mask=0xba44002f	sig=0x02440005	prob=1.0989011e-012	name=null
mask=0xb944003b	sig=0x01440001	prob=1.0989011e-012	name=null
mask=0xb944002f	sig=0x01440005	prob=1.0989011e-012	name=null
mask=0xb864003b	sig=0x00640001	prob=1.0989011e-012	name=null
mask=0xb864002f	sig=0x00640005	prob=1.0989011e-012	name=null
mask=0xba42003b	sig=0x02420001	prob=1.0989011e-012	name=null
mask=0xba42002f	sig=0x02420005	prob=1.0989011e-012	name=null
mask=0xb862003b	sig=0x00620001	prob=1.0989011e-012	name=null
mask=0xb862002f	sig=0x00620005	prob=1.0989011e-012	name=null
mask=0xf804003b	sig=0x00040001	prob=1.0989011e-012	name=null
mask=0xba88002a	sig=0x02880028	prob=1.0989011e-012	name=null
mask=0xb924002a	sig=0x01240028	prob=1.0989011e-012	name=null
mask=0xb988002a	sig=0x01880028	prob=1.0989011e-012	name=null
mask=0xba08003c	sig=0x0208002c	prob=1.0989011e-012	name=null
mask=0xb822001e	sig=0x0022000e	prob=1.0989011e-012	name=null
mask=0xb822003a	sig=0x00220028	prob=1.0989011e-012	name=null
mask=0xb822003c	sig=0x0022002c	prob=1.0989011e-012	name=null
mask=0xba02001e	sig=0x0202000e	prob=1.0989011e-012	name=null
mask=0xba02003a	sig=0x02020028	prob=1.0989011e-012	name=null
mask=0xba02003c	sig=0x0202002c	prob=1.0989011e-012	name=null
mask=0xba82002a	sig=0x02820028	prob=1.0989011e-012	name=null
mask=0xba84002a	sig=0x02840028	prob=1.0989011e-012	name=null
mask=0xbc220027	sig=0x04220004	prob=1.0989011e-012	name=null
mask=0xb902002a	sig=0x01020028	prob=1.0989011e-012	name=null
mask=0xf802002a	sig=0x00020028	prob=1.0989011e-012	name=null
mask=0xf804002a	sig=0x00040028	prob=1.0989011e-012	name=null
mask=0xf808002a	sig=0x00080028	prob=1.0989011e-012	name=null
mask=0xba22002a	sig=0x00220028	prob=1.0989011e-012	name=null
mask=0xb8a8002a	sig=0x00a80028	prob=1.0989011e-012	name=null
mask=0xba24002a	sig=0x00240028	prob=1.0989011e-012	name=null
mask=0xb984002a	sig=0x01840028	prob=1.0989011e-012	name=null
mask=0xba28002a	sig=0x00280028	prob=1.0989011e-012	name=null
mask=0xb8a4002a	sig=0x00a40028	prob=1.0989011e-012	name=null
mask=0xb8a2002a	sig=0x00a20028	prob=1.0989011e-012	name=null
mask=0xba48002a	sig=0x02480028	prob=1.0989011e-012	name=null
mask=0xf808003b	sig=0x00080001	prob=1.0989011e-012	name=null
mask=0xf808002f	sig=0x00080005	prob=1.0989011e-012	name=null
mask=0xbc00002a	sig=0x00000028	prob=1.0989011e-012	name=null
mask=0xf804002f	sig=0x00040005	prob=1.0989011e-012	name=null
mask=0xf802003b	sig=0x00020001	prob=1.0989011e-012	name=null
mask=0xf802002f	sig=0x00020005	prob=1.0989011e-012	name=null
mask=0xb902003b	sig=0x01020001	prob=1.0989011e-012	name=null
mask=0xb902002f	sig=0x01020005	prob=1.0989011e-012	name=null
mask=0xba88003b	sig=0x02880001	prob=1.0989011e-012	name=null
mask=0xba84003b	sig=0x02840001	prob=1.0989011e-012	name=null
mask=0xba82003b	sig=0x02820001	prob=1.0989011e-012	name=null
mask=0xba22002f	sig=0x00220005	prob=1.0989011e-012	name=null
mask=0xb948002a	sig=0x01480028	prob=1.0989011e-012	name=null
mask=0xb868002a	sig=0x00680028	prob=1.0989011e-012	name=null
mask=0xba44002a	sig=0x02440028	prob=1.0989011e-012	name=null
mask=0xb944002a	sig=0x01440028	prob=1.0989011e-012	name=null
mask=0xb864002a	sig=0x00640028	prob=1.0989011e-012	name=null
mask=0xba42002a	sig=0x02420028	prob=1.0989011e-012	name=null
mask=0xb862002a	sig=0x00620028	prob=1.0989011e-012	name=null
mask=0xbb08002a	sig=0x03080028	prob=1.0989011e-012	name=null
mask=0xb928002a	sig=0x01280028	prob=1.0989011e-012	name=null
mask=0xbb04002a	sig=0x03040028	prob=1.0989011e-012	name=null
mask=0xbea80035	sig=0x06080020	prob=1.0989011e-012	name=null
mask=0xb824002e	sig=0x0024000e	prob=1.0989011e-012	name=null
mask=0xbe020027	sig=0x06020004	prob=1.0989011e-012	name=null
mask=0xbe080027	sig=0x06080004	prob=1.0989011e-012	name=null
mask=0xbe040027	sig=0x06040004	prob=1.0989011e-012	name=null
mask=0xbc220032	sig=0x04220022	prob=1.0989011e-012	name=null
mask=0xbc280032	sig=0x04280022	prob=1.0989011e-012	name=null
mask=0xbc240032	sig=0x04240022	prob=1.0989011e-012	name=null
mask=0xbc280031	sig=0x04280021	prob=1.0989011e-012	name=null
mask=0xbc240031	sig=0x04240021	prob=1.0989011e-012	name=null
mask=0xbc220031	sig=0x04220021	prob=1.0989011e-012	name=null
mask=0xbea20035	sig=0x06020020	prob=1.0989011e-012	name=null
mask=0xb824003a	sig=0x0024000a	prob=1.0989011e-012	name=null
mask=0xbea40035	sig=0x06040020	prob=1.0989011e-012	name=null
mask=0xbe020035	sig=0x06020025	prob=1.0989011e-012	name=null
mask=0xbe020032	sig=0x06020022	prob=1.0989011e-012	name=null
mask=0xbe080035	sig=0x06080025	prob=1.0989011e-012	name=null
mask=0xbe040035	sig=0x06040025	prob=1.0989011e-012	name=null
mask=0xbe080032	sig=0x06080022	prob=1.0989011e-012	name=null
mask=0xbe040032	sig=0x06040022	prob=1.0989011e-012	name=null
mask=0xbe880020	sig=0x06880000	prob=1.0989011e-012	name=null
mask=0xbe880010	sig=0x06880010	prob=1.0989011e-012	name=null
mask=0xbe880008	sig=0x06880008	prob=1.0989011e-012	name=null
mask=0xbe880004	sig=0x06880004	prob=1.0989011e-012	name=null
mask=0xb902003a	sig=0x0102000a	prob=1.0989011e-012	name=null
mask=0xbc280027	sig=0x04280004	prob=1.0989011e-012	name=null
mask=0xbc240027	sig=0x04240004	prob=1.0989011e-012	name=null
mask=0xc0200027	sig=0x40200004	prob=1.0989011e-012	name=null
mask=0xb948003a	sig=0x0148000a	prob=1.0989011e-012	name=null
mask=0xb944003a	sig=0x0144000a	prob=1.0989011e-012	name=null
mask=0xb988003a	sig=0x0188000a	prob=1.0989011e-012	name=null
mask=0xb984003a	sig=0x0184000a	prob=1.0989011e-012	name=null
mask=0xbc00003a	sig=0x0000000a	prob=1.0989011e-012	name=null
mask=0xf808003a	sig=0x0008000a	prob=1.0989011e-012	name=null
mask=0xf804003a	sig=0x0004000a	prob=1.0989011e-012	name=null
mask=0xf802003a	sig=0x0002000a	prob=1.0989011e-012	name=null
mask=0xbe880002	sig=0x06880002	prob=1.0989011e-012	name=null
mask=0xba02003a	sig=0x0202000a	prob=1.0989011e-012	name=null
mask=0xba02002e	sig=0x0202000e	prob=1.0989011e-012	name=null
mask=0xb822003a	sig=0x0022000a	prob=1.0989011e-012	name=null
mask=0xb822002e	sig=0x0022000e	prob=1.0989011e-012	name=null
mask=0xba08003a	sig=0x0208000a	prob=1.0989011e-012	name=null
mask=0xba08002e	sig=0x0208000e	prob=1.0989011e-012	name=null
mask=0xba04003a	sig=0x0204000a	prob=1.0989011e-012	name=null
mask=0xba04002e	sig=0x0204000e	prob=1.0989011e-012	name=null
mask=0xb828003a	sig=0x0028000a	prob=1.0989011e-012	name=null
mask=0xb828002e	sig=0x0028000e	prob=1.0989011e-012	name=null
mask=0xbd880000	sig=0x05880000	prob=1.0989011e-012	name=null
mask=0xbc620000	sig=0x04620000	prob=1.0989011e-012	name=null
mask=0xbe080030	sig=0x06080010	prob=1.0989011e-012	name=null
mask=0xbe040030	sig=0x06040010	prob=1.0989011e-012	name=null
mask=0xbe080028	sig=0x06080008	prob=1.0989011e-012	name=null
mask=0xbe040028	sig=0x06040008	prob=1.0989011e-012	name=null
mask=0xbe080018	sig=0x06080008	prob=1.0989011e-012	name=null
mask=0xbe040018	sig=0x06040008	prob=1.0989011e-012	name=null
mask=0xbf080000	sig=0x07080000	prob=1.0989011e-012	name=null
mask=0xbd280000	sig=0x05280000	prob=1.0989011e-012	name=null
mask=0xbf040000	sig=0x07040000	prob=1.0989011e-012	name=null
mask=0xbd240000	sig=0x05240000	prob=1.0989011e-012	name=null
mask=0xbe420000	sig=0x06420000	prob=1.0989011e-012	name=null
mask=0xbca80000	sig=0x04a80000	prob=1.0989011e-012	name=null
mask=0xbd840000	sig=0x05840000	prob=1.0989011e-012	name=null
mask=0xbca40000	sig=0x04a40000	prob=1.0989011e-012	name=null
mask=0xbca20000	sig=0x04a20000	prob=1.0989011e-012	name=null
mask=0xbc280030	sig=0x04280010	prob=1.0989011e-012	name=null
mask=0xbc240030	sig=0x04240010	prob=1.0989011e-012	name=null
mask=0xbc280028	sig=0x04280008	prob=1.0989011e-012	name=null
mask=0xbc280018	sig=0x04280008	prob=1.0989011e-012	name=null
mask=0xbc240028	sig=0x04240008	prob=1.0989011e-012	name=null
mask=0xbc240018	sig=0x04240008	prob=1.0989011e-012	name=null
mask=0xbe280000	sig=0x04280000	prob=1.0989011e-012	name=null
mask=0xbc220030	sig=0x04220010	prob=1.0989011e-012	name=null
mask=0xbe840020	sig=0x06840000	prob=1.0989011e-012	name=null
mask=0xbe840010	sig=0x06840010	prob=1.0989011e-012	name=null
mask=0xbe840008	sig=0x06840008	prob=1.0989011e-012	name=null
mask=0xbe840004	sig=0x06840004	prob=1.0989011e-012	name=null
mask=0xbe840002	sig=0x06840002	prob=1.0989011e-012	name=null
mask=0xbe820020	sig=0x06820000	prob=1.0989011e-012	name=null
mask=0xbe820010	sig=0x06820010	prob=1.0989011e-012	name=null
mask=0xbe820008	sig=0x06820008	prob=1.0989011e-012	name=null
mask=0xbe820004	sig=0x06820004	prob=1.0989011e-012	name=null
mask=0xbe820002	sig=0x06820002	prob=1.0989011e-012	name=null
mask=0xbe020030	sig=0x06020010	prob=1.0989011e-012	name=null
mask=0xbe240000	sig=0x04240000	prob=1.0989011e-012	name=null
mask=0xbe020028	sig=0x06020008	prob=1.0989011e-012	name=null
mask=0xbc220028	sig=0x04220008	prob=1.0989011e-012	name=null
mask=0xbe020018	sig=0x06020008	prob=1.0989011e-012	name=null
mask=0xbc220018	sig=0x04220008	prob=1.0989011e-012	name=null
mask=0xbe480000	sig=0x06480000	prob=1.0989011e-012	name=null
mask=0xbd480000	sig=0x05480000	prob=1.0989011e-012	name=null
mask=0xbc680000	sig=0x04680000	prob=1.0989011e-012	name=null
mask=0xbe440000	sig=0x06440000	prob=1.0989011e-012	name=null
mask=0xbd440000	sig=0x05440000	prob=1.0989011e-012	name=null
mask=0xbc640000	sig=0x04640000	prob=1.0989011e-012	name=null
mask=0xba220014	sig=0x00220014	prob=1.0989011e-012	name=null
mask=0xb8a40014	sig=0x00a40014	prob=1.0989011e-012	name=null
mask=0xb8a20030	sig=0x00a20030	prob=1.0989011e-012	name=null
mask=0xb8a20014	sig=0x00a20014	prob=1.0989011e-012	name=null
mask=0xbc000030	sig=0x00000030	prob=1.0989011e-012	name=null
mask=0xbc000014	sig=0x00000014	prob=1.0989011e-012	name=null
mask=0xba280030	sig=0x00280030	prob=1.0989011e-012	name=null
mask=0xba280014	sig=0x00280014	prob=1.0989011e-012	name=null
mask=0xba240030	sig=0x00240030	prob=1.0989011e-012	name=null
mask=0xba240014	sig=0x00240014	prob=1.0989011e-012	name=null
mask=0xba220030	sig=0x00220030	prob=1.0989011e-012	name=null
mask=0xb8a40030	sig=0x00a40030	prob=1.0989011e-012	name=null
mask=0xf8080030	sig=0x00080030	prob=1.0989011e-012	name=null
mask=0xf8080014	sig=0x00080014	prob=1.0989011e-012	name=null
mask=0xf8040030	sig=0x00040030	prob=1.0989011e-012	name=null
mask=0xf8040014	sig=0x00040014	prob=1.0989011e-012	name=null
mask=0xf8020030	sig=0x00020030	prob=1.0989011e-012	name=null
mask=0xf8020014	sig=0x00020014	prob=1.0989011e-012	name=null
mask=0xb9020030	sig=0x01020030	prob=1.0989011e-012	name=null
mask=0xb9020014	sig=0x01020014	prob=1.0989011e-012	name=null
mask=0xba880030	sig=0x02880030	prob=1.0989011e-012	name=null
mask=0xbb040030	sig=0x03040030	prob=1.0989011e-012	name=null
mask=0xb8640014	sig=0x00640014	prob=1.0989011e-012	name=null
mask=0xba420030	sig=0x02420030	prob=1.0989011e-012	name=null
mask=0xba420014	sig=0x02420014	prob=1.0989011e-012	name=null
mask=0xb8620030	sig=0x00620030	prob=1.0989011e-012	name=null
mask=0xb8620014	sig=0x00620014	prob=1.0989011e-012	name=null
mask=0xbb080030	sig=0x03080030	prob=1.0989011e-012	name=null
mask=0xbb080014	sig=0x03080014	prob=1.0989011e-012	name=null
mask=0xb9280030	sig=0x01280030	prob=1.0989011e-012	name=null
mask=0xb9280014	sig=0x01280014	prob=1.0989011e-012	name=null
mask=0xba880014	sig=0x02880014	prob=1.0989011e-012	name=null
mask=0xbb040014	sig=0x03040014	prob=1.0989011e-012	name=null
mask=0xb9240030	sig=0x01240030	prob=1.0989011e-012	name=null
mask=0xb9240014	sig=0x01240014	prob=1.0989011e-012	name=null
mask=0xb9880030	sig=0x01880030	prob=1.0989011e-012	name=null
mask=0xb9880014	sig=0x01880014	prob=1.0989011e-012	name=null
mask=0xb8a80030	sig=0x00a80030	prob=1.0989011e-012	name=null
mask=0xb8a80014	sig=0x00a80014	prob=1.0989011e-012	name=null
mask=0xb9840030	sig=0x01840030	prob=1.0989011e-012	name=null
mask=0xb9840014	sig=0x01840014	prob=1.0989011e-012	name=null
mask=0xc1800000	sig=0x41800000	prob=1.0989011e-012	name=null
mask=0xc2800002	sig=0x42800002	prob=1.0989011e-012	name=null
mask=0xc2400000	sig=0x42400000	prob=1.0989011e-012	name=null
mask=0xc1400000	sig=0x41400000	prob=1.0989011e-012	name=null
mask=0xc0600000	sig=0x40600000	prob=1.0989011e-012	name=null
mask=0xc2000030	sig=0x42000010	prob=1.0989011e-012	name=null
mask=0xc2000028	sig=0x42000008	prob=1.0989011e-012	name=null
mask=0xc2000018	sig=0x42000008	prob=1.0989011e-012	name=null
mask=0xc3000000	sig=0x43000000	prob=1.0989011e-012	name=null
mask=0xc1200000	sig=0x41200000	prob=1.0989011e-012	name=null
mask=0xc1020000	sig=0x41020000	prob=1.0989011e-012	name=null
mask=0xc2800004	sig=0x42800004	prob=1.0989011e-012	name=null
mask=0xc0a00000	sig=0x40a00000	prob=1.0989011e-012	name=null
mask=0xc0200030	sig=0x40200010	prob=1.0989011e-012	name=null
mask=0xc0200028	sig=0x40200008	prob=1.0989011e-012	name=null
mask=0xc0200018	sig=0x40200008	prob=1.0989011e-012	name=null
mask=0xc4000000	sig=0x40000000	prob=1.0989011e-012	name=null
mask=0xc2200000	sig=0x40200000	prob=1.0989011e-012	name=null
mask=0xe0000000	sig=0x60000000	prob=1.0989011e-012	name=null
mask=0x48000000	sig=0x48000000	prob=1.0989011e-012	name=null
mask=0x50000000	sig=0x50000000	prob=1.0989011e-012	name=null
mask=0xb8240034	sig=0x00240014	prob=1.0989011e-012	name=null
mask=0xba840030	sig=0x02840030	prob=1.0989011e-012	name=null
mask=0xba840014	sig=0x02840014	prob=1.0989011e-012	name=null
mask=0xba820030	sig=0x02820030	prob=1.0989011e-012	name=null
mask=0xba820014	sig=0x02820014	prob=1.0989011e-012	name=null
mask=0xba020034	sig=0x02020014	prob=1.0989011e-012	name=null
mask=0xb8220034	sig=0x00220014	prob=1.0989011e-012	name=null
mask=0xba080034	sig=0x02080014	prob=1.0989011e-012	name=null
mask=0xba040034	sig=0x02040014	prob=1.0989011e-012	name=null
mask=0xb8280034	sig=0x00280014	prob=1.0989011e-012	name=null
mask=0xba08001e	sig=0x0208000e	prob=1.0989011e-012	name=null
mask=0xc2a00035	sig=0x42000020	prob=1.0989011e-012	name=null
mask=0x9c000000	sig=0x9c000000	prob=1.0989011e-012	name=null
mask=0xc2000035	sig=0x42000025	prob=1.0989011e-012	name=null
mask=0xc2000032	sig=0x42000022	prob=1.0989011e-012	name=null
mask=0xb8000000	sig=0xb0000000	prob=1.0989011e-012	name=null
mask=0xb4000000	sig=0xb4000000	prob=1.0989011e-012	name=null
mask=0xc2800020	sig=0x42800000	prob=1.0989011e-012	name=null
mask=0xc2800010	sig=0x42800010	prob=1.0989011e-012	name=null
mask=0xc2800008	sig=0x42800008	prob=1.0989011e-012	name=null
mask=0xbc00000e	sig=0x0000000e	prob=1.0989011e-012	name=null
mask=0xb862000e	sig=0x0062000e	prob=1.0989011e-012	name=null
mask=0xbb08000e	sig=0x0308000e	prob=1.0989011e-012	name=null
mask=0xb928000e	sig=0x0128000e	prob=1.0989011e-012	name=null
mask=0xbb04000e	sig=0x0304000e	prob=1.0989011e-012	name=null
mask=0xb924000e	sig=0x0124000e	prob=1.0989011e-012	name=null
mask=0xb988000e	sig=0x0188000e	prob=1.0989011e-012	name=null
mask=0xb8a8000e	sig=0x00a8000e	prob=1.0989011e-012	name=null
mask=0xb984000e	sig=0x0184000e	prob=1.0989011e-012	name=null
mask=0xb8a4000e	sig=0x00a4000e	prob=1.0989011e-012	name=null
mask=0xb8a2000e	sig=0x00a2000e	prob=1.0989011e-012	name=null
mask=0xba42000e	sig=0x0242000e	prob=1.0989011e-012	name=null
mask=0xba28000e	sig=0x0028000e	prob=1.0989011e-012	name=null
mask=0xba24000e	sig=0x0024000e	prob=1.0989011e-012	name=null
mask=0xba22000e	sig=0x0022000e	prob=1.0989011e-012	name=null
mask=0xf808000e	sig=0x0008000e	prob=1.0989011e-012	name=null
mask=0xf804000e	sig=0x0004000e	prob=1.0989011e-012	name=null
mask=0xf802000e	sig=0x0002000e	prob=1.0989011e-012	name=null
mask=0xb902000e	sig=0x0102000e	prob=1.0989011e-012	name=null
mask=0xba88000e	sig=0x0288000e	prob=1.0989011e-012	name=null
mask=0xba84000e	sig=0x0284000e	prob=1.0989011e-012	name=null
mask=0xb824001e	sig=0x0024000e	prob=1.0989011e-012	name=null
mask=0xba08003a	sig=0x02080028	prob=1.0989011e-012	name=null
mask=0xba04003c	sig=0x0204002c	prob=1.0989011e-012	name=null
mask=0xba04003a	sig=0x02040028	prob=1.0989011e-012	name=null
mask=0xba04001e	sig=0x0204000e	prob=1.0989011e-012	name=null
mask=0xb828003c	sig=0x0028002c	prob=1.0989011e-012	name=null
mask=0xb828003a	sig=0x00280028	prob=1.0989011e-012	name=null
mask=0xb828001e	sig=0x0028000e	prob=1.0989011e-012	name=null
mask=0xb824003c	sig=0x0024002c	prob=1.0989011e-012	name=null
mask=0xb824003a	sig=0x00240028	prob=1.0989011e-012	name=null
mask=0xb9440014	sig=0x01440014	prob=1.0989011e-012	name=null
mask=0xba88002f	sig=0x02880005	prob=1.0989011e-012	name=null
mask=0xba84002f	sig=0x02840005	prob=1.0989011e-012	name=null
mask=0xba82002f	sig=0x02820005	prob=1.0989011e-012	name=null
mask=0xba48000e	sig=0x0248000e	prob=1.0989011e-012	name=null
mask=0xb948000e	sig=0x0148000e	prob=1.0989011e-012	name=null
mask=0xb868000e	sig=0x0068000e	prob=1.0989011e-012	name=null
mask=0xba44000e	sig=0x0244000e	prob=1.0989011e-012	name=null
mask=0xb944000e	sig=0x0144000e	prob=1.0989011e-012	name=null
mask=0xb864000e	sig=0x0064000e	prob=1.0989011e-012	name=null
mask=0xba480030	sig=0x02480030	prob=1.0989011e-012	name=null
mask=0xba22002c	sig=0x0022002c	prob=1.0989011e-012	name=null
mask=0xf808002c	sig=0x0008002c	prob=1.0989011e-012	name=null
mask=0xf804002c	sig=0x0004002c	prob=1.0989011e-012	name=null
mask=0xf802002c	sig=0x0002002c	prob=1.0989011e-012	name=null
mask=0xb902002c	sig=0x0102002c	prob=1.0989011e-012	name=null
mask=0xba88002c	sig=0x0288002c	prob=1.0989011e-012	name=null
mask=0xba84002c	sig=0x0284002c	prob=1.0989011e-012	name=null
mask=0xba82002c	sig=0x0282002c	prob=1.0989011e-012	name=null
mask=0xc0200032	sig=0x40200022	prob=1.0989011e-012	name=null
mask=0xc0200031	sig=0x40200021	prob=1.0989011e-012	name=null
mask=0xba48002c	sig=0x0248002c	prob=1.0989011e-012	name=null
mask=0xba480014	sig=0x02480014	prob=1.0989011e-012	name=null
mask=0xb9480030	sig=0x01480030	prob=1.0989011e-012	name=null
mask=0xb9480014	sig=0x01480014	prob=1.0989011e-012	name=null
mask=0xb8680030	sig=0x00680030	prob=1.0989011e-012	name=null
mask=0xb8680014	sig=0x00680014	prob=1.0989011e-012	name=null
mask=0xba440030	sig=0x02440030	prob=1.0989011e-012	name=null
mask=0xba440014	sig=0x02440014	prob=1.0989011e-012	name=null
mask=0xb9440030	sig=0x01440030	prob=1.0989011e-012	name=null
mask=0xb8640030	sig=0x00640030	prob=1.0989011e-012	name=null
mask=0xb862002c	sig=0x0062002c	prob=1.0989011e-012	name=null
mask=0xba24002c	sig=0x0024002c	prob=1.0989011e-012	name=null
mask=0xba82000e	sig=0x0282000e	prob=1.0989011e-012	name=null
mask=0xb948002c	sig=0x0148002c	prob=1.0989011e-012	name=null
mask=0xb868002c	sig=0x0068002c	prob=1.0989011e-012	name=null
mask=0xba44002c	sig=0x0244002c	prob=1.0989011e-012	name=null
mask=0xb944002c	sig=0x0144002c	prob=1.0989011e-012	name=null
mask=0xb864002c	sig=0x0064002c	prob=1.0989011e-012	name=null
mask=0xba42002c	sig=0x0242002c	prob=1.0989011e-012	name=null
mask=0xbb08002c	sig=0x0308002c	prob=1.0989011e-012	name=null
mask=0xb928002c	sig=0x0128002c	prob=1.0989011e-012	name=null
mask=0xbb04002c	sig=0x0304002c	prob=1.0989011e-012	name=null
mask=0xb924002c	sig=0x0124002c	prob=1.0989011e-012	name=null
mask=0xb988002c	sig=0x0188002c	prob=1.0989011e-012	name=null
mask=0xb8a8002c	sig=0x00a8002c	prob=1.0989011e-012	name=null
mask=0xb984002c	sig=0x0184002c	prob=1.0989011e-012	name=null
mask=0xb8a4002c	sig=0x00a4002c	prob=1.0989011e-012	name=null
mask=0xb8a2002c	sig=0x00a2002c	prob=1.0989011e-012	name=null
mask=0xbc00002c	sig=0x0000002c	prob=1.0989011e-012	name=null
mask=0xba28002c	sig=0x0028002c	prob=1.0989011e-012	name=null
mask=0xfc00003f	sig=0x00000025	prob=0.010989011	name=or
mask=0xfc000000	sig=0x34000000	prob=0.010989011	name=ori
mask=0xfc000000	sig=0xa0000000	prob=0.010989011	name=sb
mask=0xfc000000	sig=0xe0000000	prob=0.010989011	name=sc
mask=0xfc000000	sig=0xa4000000	prob=0.010989011	name=sh
mask=0xffffffff	sig=0x00000000	prob=0.010989011	name=nop
mask=0xfc00003f	sig=0x00000004	prob=0.010989011	name=sllv
mask=0xfc00003f	sig=0x0000002a	prob=0.010989011	name=slt
mask=0xfc000000	sig=0x28000000	prob=0.010989011	name=slti
mask=0xfc000000	sig=0x2c000000	prob=0.010989011	name=sltiu
mask=0xfc00003f	sig=0x0000002b	prob=0.010989011	name=sltu
mask=0xfc00003f	sig=0x00000003	prob=0.010989011	name=sra
mask=0xfc00003f	sig=0x00000007	prob=0.010989011	name=srav
mask=0xfc00003f	sig=0x00000002	prob=0.010989011	name=srl
mask=0xfc00003f	sig=0x00000006	prob=0.010989011	name=srlv
mask=0xfc00003f	sig=0x00000022	prob=0.010989011	name=sub
mask=0xffe0003f	sig=0x46200001	prob=0.010989011	name=sub_d
mask=0xffe0003f	sig=0x46000001	prob=0.010989011	name=sub_s
mask=0xfc00003f	sig=0x00000023	prob=0.010989011	name=subu
mask=0xfc000000	sig=0xac000000	prob=0.010989011	name=sw
mask=0xfc000000	sig=0xe4000000	prob=0.010989011	name=swc1
mask=0xfc000000	sig=0xa8000000	prob=0.010989011	name=swl
mask=0xfc000000	sig=0xb8000000	prob=0.010989011	name=swr
mask=0xfc00003f	sig=0x0000000c	prob=0.010989011	name=syscall
mask=0xfc00003f	sig=0x00000026	prob=0.010989011	name=xor
mask=0xfc000000	sig=0x38000000	prob=0.010989011	name=xori
-------------------------------------------------------------------
Table Mask=0xfe000000*/

_TABLE_DEF_BEGIN(table_0, 128)
  _STUB_NAME(stub_0_0),
  _STUB_NAME(stub_0_1),
  _STUB_NAME(stub_0_2),
  _STUB_NAME(stub_0_3),
  _FUNC_NAME(j),
  _FUNC_NAME(j),
  _FUNC_NAME(jal),
  _FUNC_NAME(jal),
  _FUNC_NAME(beq),
  _FUNC_NAME(beq),
  _FUNC_NAME(bne),
  _FUNC_NAME(bne),
  _FUNC_NAME(blez),
  _FUNC_NAME(blez),
  _FUNC_NAME(bgtz),
  _FUNC_NAME(bgtz),
  _FUNC_NAME(addi),
  _FUNC_NAME(addi),
  _FUNC_NAME(addiu),
  _FUNC_NAME(addiu),
  _FUNC_NAME(slti),
  _FUNC_NAME(slti),
  _FUNC_NAME(sltiu),
  _FUNC_NAME(sltiu),
  _FUNC_NAME(andi),
  _FUNC_NAME(andi),
  _FUNC_NAME(ori),
  _FUNC_NAME(ori),
  _FUNC_NAME(xori),
  _FUNC_NAME(xori),
  _FUNC_NAME(lui),
  _FUNC_NAME(lui),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _STUB_NAME(stub_0_34),
  _STUB_NAME(stub_0_35),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(lb),
  _FUNC_NAME(lb),
  _FUNC_NAME(lh),
  _FUNC_NAME(lh),
  _FUNC_NAME(lwl),
  _FUNC_NAME(lwl),
  _FUNC_NAME(lw),
  _FUNC_NAME(lw),
  _FUNC_NAME(lbu),
  _FUNC_NAME(lbu),
  _FUNC_NAME(lhu),
  _FUNC_NAME(lhu),
  _FUNC_NAME(lwr),
  _FUNC_NAME(lwr),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(sb),
  _FUNC_NAME(sb),
  _FUNC_NAME(sh),
  _FUNC_NAME(sh),
  _FUNC_NAME(swl),
  _FUNC_NAME(swl),
  _FUNC_NAME(sw),
  _FUNC_NAME(sw),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(swr),
  _FUNC_NAME(swr),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(ll),
  _FUNC_NAME(ll),
  _FUNC_NAME(lwc1),
  _FUNC_NAME(lwc1),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(sc),
  _FUNC_NAME(sc),
  _FUNC_NAME(swc1),
  _FUNC_NAME(swc1),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
_TABLE_DEF_END

/*
Table begin: index=0 size=214
Mask=0x01ffffff	DMask=0xfe000000	CMask=0x00000000	Sig=0x00000026
Prob=0.16456044	Entropy=4.8400534	HTreeHeight=4.89816361
-------------------------------------------------------------------
mask=0xfe00003f	sig=0x00000020	prob=0.0333889816	name=add
mask=0xfe00003f	sig=0x00000021	prob=0.0333889816	name=addu
mask=0xfe00003f	sig=0x00000024	prob=0.0333889816	name=and
mask=0xfe00003f	sig=0x0000000d	prob=0.0333889816	name=brk
mask=0xfe00003f	sig=0x0000001a	prob=0.0333889816	name=div
mask=0xfe00003f	sig=0x0000001b	prob=0.0333889816	name=divu
mask=0xfe00003f	sig=0x00000009	prob=0.0333889816	name=jalr
mask=0xfe00003f	sig=0x00000008	prob=0.0333889816	name=jr
mask=0xfe00003f	sig=0x00000010	prob=0.0333889816	name=mfhi
mask=0xfe00003f	sig=0x00000012	prob=0.0333889816	name=mflo
mask=0xfe00003f	sig=0x00000011	prob=0.0333889816	name=mthi
mask=0xfe00003f	sig=0x00000013	prob=0.0333889816	name=mtlo
mask=0xfe00003f	sig=0x00000018	prob=0.0333889816	name=mult
mask=0xfe00003f	sig=0x00000019	prob=0.0333889816	name=multu
mask=0xffffffff	sig=0x00000000	prob=0.0667779633	name=nop
mask=0xfe00003f	sig=0x00000027	prob=0.0333889816	name=nor
mask=0xfea8000e	sig=0x00a8000e	prob=8.34724541e-013	name=null
mask=0xfe640014	sig=0x00640014	prob=8.34724541e-013	name=null
mask=0xfe620030	sig=0x00620030	prob=8.34724541e-013	name=null
mask=0xfe620014	sig=0x00620014	prob=8.34724541e-013	name=null
mask=0xff280030	sig=0x01280030	prob=8.34724541e-013	name=null
mask=0xff280014	sig=0x01280014	prob=8.34724541e-013	name=null
mask=0xff240030	sig=0x01240030	prob=8.34724541e-013	name=null
mask=0xff240014	sig=0x01240014	prob=8.34724541e-013	name=null
mask=0xff880030	sig=0x01880030	prob=8.34724541e-013	name=null
mask=0xff880014	sig=0x01880014	prob=8.34724541e-013	name=null
mask=0xfea80030	sig=0x00a80030	prob=8.34724541e-013	name=null
mask=0xfea80014	sig=0x00a80014	prob=8.34724541e-013	name=null
mask=0xff840030	sig=0x01840030	prob=8.34724541e-013	name=null
mask=0xff840014	sig=0x01840014	prob=8.34724541e-013	name=null
mask=0xfe240034	sig=0x00240014	prob=8.34724541e-013	name=null
mask=0xfe220034	sig=0x00220014	prob=8.34724541e-013	name=null
mask=0xfe280034	sig=0x00280014	prob=8.34724541e-013	name=null
mask=0xfe00000e	sig=0x0000000e	prob=1.66944908e-012	name=null
mask=0xfe62000e	sig=0x0062000e	prob=8.34724541e-013	name=null
mask=0xff28000e	sig=0x0128000e	prob=8.34724541e-013	name=null
mask=0xff24000e	sig=0x0124000e	prob=8.34724541e-013	name=null
mask=0xff88000e	sig=0x0188000e	prob=8.34724541e-013	name=null
mask=0xfe22002e	sig=0x0022000e	prob=8.34724541e-013	name=null
mask=0xfe240030	sig=0x00240030	prob=1.66944908e-012	name=null
mask=0xfe02003a	sig=0x0002000a	prob=1.66944908e-012	name=null
mask=0xfe28003a	sig=0x0028000a	prob=8.34724541e-013	name=null
mask=0xfe28002e	sig=0x0028000e	prob=8.34724541e-013	name=null
mask=0xfe220014	sig=0x00220014	prob=1.66944908e-012	name=null
mask=0xfea40014	sig=0x00a40014	prob=8.34724541e-013	name=null
mask=0xfea20030	sig=0x00a20030	prob=8.34724541e-013	name=null
mask=0xfea20014	sig=0x00a20014	prob=8.34724541e-013	name=null
mask=0xfe000030	sig=0x00000030	prob=1.66944908e-012	name=null
mask=0xfe000014	sig=0x00000014	prob=1.66944908e-012	name=null
mask=0xfe280030	sig=0x00280030	prob=1.66944908e-012	name=null
mask=0xfe280014	sig=0x00280014	prob=1.66944908e-012	name=null
mask=0xff020014	sig=0x01020014	prob=8.34724541e-013	name=null
mask=0xfe240014	sig=0x00240014	prob=1.66944908e-012	name=null
mask=0xfe220030	sig=0x00220030	prob=1.66944908e-012	name=null
mask=0xfea40030	sig=0x00a40030	prob=8.34724541e-013	name=null
mask=0xfe080030	sig=0x00080030	prob=1.66944908e-012	name=null
mask=0xfe080014	sig=0x00080014	prob=1.66944908e-012	name=null
mask=0xfe040030	sig=0x00040030	prob=1.66944908e-012	name=null
mask=0xfe040014	sig=0x00040014	prob=1.66944908e-012	name=null
mask=0xfe020030	sig=0x00020030	prob=1.66944908e-012	name=null
mask=0xfe020014	sig=0x00020014	prob=1.66944908e-012	name=null
mask=0xff020030	sig=0x01020030	prob=8.34724541e-013	name=null
mask=0xfe68002c	sig=0x0068002c	prob=8.34724541e-013	name=null
mask=0xfe02002c	sig=0x0002002c	prob=1.66944908e-012	name=null
mask=0xff02002c	sig=0x0102002c	prob=8.34724541e-013	name=null
mask=0xff480030	sig=0x01480030	prob=8.34724541e-013	name=null
mask=0xff480014	sig=0x01480014	prob=8.34724541e-013	name=null
mask=0xfe680030	sig=0x00680030	prob=8.34724541e-013	name=null
mask=0xfe680014	sig=0x00680014	prob=8.34724541e-013	name=null
mask=0xff440030	sig=0x01440030	prob=8.34724541e-013	name=null
mask=0xfe640030	sig=0x00640030	prob=8.34724541e-013	name=null
mask=0xfe62002c	sig=0x0062002c	prob=8.34724541e-013	name=null
mask=0xfe24002c	sig=0x0024002c	prob=1.66944908e-012	name=null
mask=0xff48002c	sig=0x0148002c	prob=8.34724541e-013	name=null
mask=0xfe04002c	sig=0x0004002c	prob=1.66944908e-012	name=null
mask=0xff44002c	sig=0x0144002c	prob=8.34724541e-013	name=null
mask=0xfe64002c	sig=0x0064002c	prob=8.34724541e-013	name=null
mask=0xff28002c	sig=0x0128002c	prob=8.34724541e-013	name=null
mask=0xff24002c	sig=0x0124002c	prob=8.34724541e-013	name=null
mask=0xff88002c	sig=0x0188002c	prob=8.34724541e-013	name=null
mask=0xfea8002c	sig=0x00a8002c	prob=8.34724541e-013	name=null
mask=0xff84002c	sig=0x0184002c	prob=8.34724541e-013	name=null
mask=0xfea4002c	sig=0x00a4002c	prob=8.34724541e-013	name=null
mask=0xfea2002c	sig=0x00a2002c	prob=8.34724541e-013	name=null
mask=0xfe00002c	sig=0x0000002c	prob=1.66944908e-012	name=null
mask=0xfe28002c	sig=0x0028002c	prob=1.66944908e-012	name=null
mask=0xfe28003a	sig=0x00280028	prob=8.34724541e-013	name=null
mask=0xfea4000e	sig=0x00a4000e	prob=8.34724541e-013	name=null
mask=0xfea2000e	sig=0x00a2000e	prob=8.34724541e-013	name=null
mask=0xfe28000e	sig=0x0028000e	prob=1.66944908e-012	name=null
mask=0xfe24000e	sig=0x0024000e	prob=1.66944908e-012	name=null
mask=0xfe22000e	sig=0x0022000e	prob=1.66944908e-012	name=null
mask=0xfe08000e	sig=0x0008000e	prob=1.66944908e-012	name=null
mask=0xfe04000e	sig=0x0004000e	prob=1.66944908e-012	name=null
mask=0xfe02000e	sig=0x0002000e	prob=1.66944908e-012	name=null
mask=0xff02000e	sig=0x0102000e	prob=8.34724541e-013	name=null
mask=0xfe24001e	sig=0x0024000e	prob=8.34724541e-013	name=null
mask=0xfe28003c	sig=0x0028002c	prob=8.34724541e-013	name=null
mask=0xff84000e	sig=0x0184000e	prob=8.34724541e-013	name=null
mask=0xfe28001e	sig=0x0028000e	prob=8.34724541e-013	name=null
mask=0xfe24003c	sig=0x0024002c	prob=8.34724541e-013	name=null
mask=0xfe24003a	sig=0x00240028	prob=8.34724541e-013	name=null
mask=0xff440014	sig=0x01440014	prob=8.34724541e-013	name=null
mask=0xff48000e	sig=0x0148000e	prob=8.34724541e-013	name=null
mask=0xfe68000e	sig=0x0068000e	prob=8.34724541e-013	name=null
mask=0xff44000e	sig=0x0144000e	prob=8.34724541e-013	name=null
mask=0xfe64000e	sig=0x0064000e	prob=8.34724541e-013	name=null
mask=0xfe22002c	sig=0x0022002c	prob=1.66944908e-012	name=null
mask=0xfe08002c	sig=0x0008002c	prob=1.66944908e-012	name=null
mask=0xfe64003b	sig=0x00640001	prob=8.34724541e-013	name=null
mask=0xfe24003b	sig=0x00240001	prob=1.66944908e-012	name=null
mask=0xfe24002f	sig=0x00240005	prob=1.66944908e-012	name=null
mask=0xfe22003b	sig=0x00220001	prob=1.66944908e-012	name=null
mask=0xfe68002f	sig=0x00680005	prob=8.34724541e-013	name=null
mask=0xff48003b	sig=0x01480001	prob=8.34724541e-013	name=null
mask=0xff48002f	sig=0x01480005	prob=8.34724541e-013	name=null
mask=0xfe68003b	sig=0x00680001	prob=8.34724541e-013	name=null
mask=0xff44003b	sig=0x01440001	prob=8.34724541e-013	name=null
mask=0xff44002f	sig=0x01440005	prob=8.34724541e-013	name=null
mask=0xfe28002f	sig=0x00280005	prob=1.66944908e-012	name=null
mask=0xfe64002f	sig=0x00640005	prob=8.34724541e-013	name=null
mask=0xfe62003b	sig=0x00620001	prob=8.34724541e-013	name=null
mask=0xfe62002f	sig=0x00620005	prob=8.34724541e-013	name=null
mask=0xfe04003b	sig=0x00040001	prob=1.66944908e-012	name=null
mask=0xff24002a	sig=0x01240028	prob=8.34724541e-013	name=null
mask=0xff88002a	sig=0x01880028	prob=8.34724541e-013	name=null
mask=0xfe22001e	sig=0x0022000e	prob=8.34724541e-013	name=null
mask=0xfe22003a	sig=0x00220028	prob=8.34724541e-013	name=null
mask=0xff84003b	sig=0x01840001	prob=8.34724541e-013	name=null
mask=0xfea8003b	sig=0x00a80001	prob=8.34724541e-013	name=null
mask=0xff28003b	sig=0x01280001	prob=8.34724541e-013	name=null
mask=0xff28002f	sig=0x01280005	prob=8.34724541e-013	name=null
mask=0xff24003b	sig=0x01240001	prob=8.34724541e-013	name=null
mask=0xff24002f	sig=0x01240005	prob=8.34724541e-013	name=null
mask=0xff88003b	sig=0x01880001	prob=8.34724541e-013	name=null
mask=0xff88002f	sig=0x01880005	prob=8.34724541e-013	name=null
mask=0xfea8002f	sig=0x00a80005	prob=8.34724541e-013	name=null
mask=0xfe04003a	sig=0x0004000a	prob=1.66944908e-012	name=null
mask=0xff84002f	sig=0x01840005	prob=8.34724541e-013	name=null
mask=0xfea4003b	sig=0x00a40001	prob=8.34724541e-013	name=null
mask=0xfea4002f	sig=0x00a40005	prob=8.34724541e-013	name=null
mask=0xfea2003b	sig=0x00a20001	prob=8.34724541e-013	name=null
mask=0xfea2002f	sig=0x00a20005	prob=8.34724541e-013	name=null
mask=0xfe00003b	sig=0x00000001	prob=1.66944908e-012	name=null
mask=0xfe00002f	sig=0x00000005	prob=1.66944908e-012	name=null
mask=0xfe28003b	sig=0x00280001	prob=1.66944908e-012	name=null
mask=0xfe24003a	sig=0x0024000a	prob=8.34724541e-013	name=null
mask=0xff02002f	sig=0x01020005	prob=8.34724541e-013	name=null
mask=0xfe22002f	sig=0x00220005	prob=1.66944908e-012	name=null
mask=0xff48002a	sig=0x01480028	prob=8.34724541e-013	name=null
mask=0xfe68002a	sig=0x00680028	prob=8.34724541e-013	name=null
mask=0xff44002a	sig=0x01440028	prob=8.34724541e-013	name=null
mask=0xfe64002a	sig=0x00640028	prob=8.34724541e-013	name=null
mask=0xfe62002a	sig=0x00620028	prob=8.34724541e-013	name=null
mask=0xff28002a	sig=0x01280028	prob=8.34724541e-013	name=null
mask=0xfe24002e	sig=0x0024000e	prob=8.34724541e-013	name=null
mask=0xff02002a	sig=0x01020028	prob=8.34724541e-013	name=null
mask=0xff02003a	sig=0x0102000a	prob=8.34724541e-013	name=null
mask=0xff48003a	sig=0x0148000a	prob=8.34724541e-013	name=null
mask=0xff44003a	sig=0x0144000a	prob=8.34724541e-013	name=null
mask=0xff88003a	sig=0x0188000a	prob=8.34724541e-013	name=null
mask=0xff84003a	sig=0x0184000a	prob=8.34724541e-013	name=null
mask=0xfe00003a	sig=0x0000000a	prob=1.66944908e-012	name=null
mask=0xfe08003a	sig=0x0008000a	prob=1.66944908e-012	name=null
mask=0xfe22003a	sig=0x0022000a	prob=8.34724541e-013	name=null
mask=0xfe02002f	sig=0x00020005	prob=1.66944908e-012	name=null
mask=0xff02003b	sig=0x01020001	prob=8.34724541e-013	name=null
mask=0xfe22003c	sig=0x0022002c	prob=8.34724541e-013	name=null
mask=0xfe02002a	sig=0x00020028	prob=1.66944908e-012	name=null
mask=0xfe04002a	sig=0x00040028	prob=1.66944908e-012	name=null
mask=0xfe08002a	sig=0x00080028	prob=1.66944908e-012	name=null
mask=0xfe22002a	sig=0x00220028	prob=1.66944908e-012	name=null
mask=0xfea8002a	sig=0x00a80028	prob=8.34724541e-013	name=null
mask=0xfe24002a	sig=0x00240028	prob=1.66944908e-012	name=null
mask=0xff84002a	sig=0x01840028	prob=8.34724541e-013	name=null
mask=0xfea4002a	sig=0x00a40028	prob=8.34724541e-013	name=null
mask=0xfea2002a	sig=0x00a20028	prob=8.34724541e-013	name=null
mask=0xfe08003b	sig=0x00080001	prob=1.66944908e-012	name=null
mask=0xfe08002f	sig=0x00080005	prob=1.66944908e-012	name=null
mask=0xfe00002a	sig=0x00000028	prob=1.66944908e-012	name=null
mask=0xfe04002f	sig=0x00040005	prob=1.66944908e-012	name=null
mask=0xfe02003b	sig=0x00020001	prob=1.66944908e-012	name=null
mask=0xfe28002a	sig=0x00280028	prob=1.66944908e-012	name=null
mask=0xfe00003f	sig=0x00000025	prob=0.0333889816	name=or
mask=0xfe00007f	sig=0x00000040	prob=0.00166944908	name=sll
mask=0xfe0000bf	sig=0x00000080	prob=0.00166944908	name=sll
mask=0xfe00013f	sig=0x00000100	prob=0.00166944908	name=sll
mask=0xfe00023f	sig=0x00000200	prob=0.00166944908	name=sll
mask=0xfe00043f	sig=0x00000400	prob=0.00166944908	name=sll
mask=0xfe04003f	sig=0x00040000	prob=0.00166944908	name=sll
mask=0xfe00083f	sig=0x00000800	prob=0.00166944908	name=sll
mask=0xfe00103f	sig=0x00001000	prob=0.00166944908	name=sll
mask=0xfe00203f	sig=0x00002000	prob=0.00166944908	name=sll
mask=0xfe00803f	sig=0x00008000	prob=0.00166944908	name=sll
mask=0xfe01003f	sig=0x00010000	prob=0.00166944908	name=sll
mask=0xfe02003f	sig=0x00020000	prob=0.00166944908	name=sll
mask=0xfe08003f	sig=0x00080000	prob=0.00166944908	name=sll
mask=0xfe10003f	sig=0x00100000	prob=0.00166944908	name=sll
mask=0xfe20003f	sig=0x00200000	prob=0.00166944908	name=sll
mask=0xfe40003f	sig=0x00400000	prob=0.00166944908	name=sll
mask=0xfe80003f	sig=0x00800000	prob=0.00166944908	name=sll
mask=0xff00003f	sig=0x01000000	prob=0.00166944908	name=sll
mask=0xfe00403f	sig=0x00004000	prob=0.00166944908	name=sll
mask=0xfe00003f	sig=0x00000004	prob=0.0333889816	name=sllv
mask=0xfe00003f	sig=0x0000002a	prob=0.0333889816	name=slt
mask=0xfe00003f	sig=0x0000002b	prob=0.0333889816	name=sltu
mask=0xfe00003f	sig=0x00000003	prob=0.0333889816	name=sra
mask=0xfe00003f	sig=0x00000007	prob=0.0333889816	name=srav
mask=0xfe00003f	sig=0x00000002	prob=0.0333889816	name=srl
mask=0xfe00003f	sig=0x00000006	prob=0.0333889816	name=srlv
mask=0xfe00003f	sig=0x00000022	prob=0.0333889816	name=sub
mask=0xfe00003f	sig=0x00000023	prob=0.0333889816	name=subu
mask=0xfe00003f	sig=0x0000000c	prob=0.0333889816	name=syscall
mask=0xfe00003f	sig=0x00000026	prob=0.0333889816	name=xor
-------------------------------------------------------------------
Table Mask=0x0000003f*/

_TABLE_DEF_BEGIN(table_1, 64)
  _STUB_NAME(stub_1_0),
  _FUNC_NAME(null),
  _FUNC_NAME(srl),
  _FUNC_NAME(sra),
  _FUNC_NAME(sllv),
  _FUNC_NAME(null),
  _FUNC_NAME(srlv),
  _FUNC_NAME(srav),
  _FUNC_NAME(jr),
  _FUNC_NAME(jalr),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(syscall),
  _FUNC_NAME(brk),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(mfhi),
  _FUNC_NAME(mthi),
  _FUNC_NAME(mflo),
  _FUNC_NAME(mtlo),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(mult),
  _FUNC_NAME(multu),
  _FUNC_NAME(div),
  _FUNC_NAME(divu),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(add),
  _FUNC_NAME(addu),
  _FUNC_NAME(sub),
  _FUNC_NAME(subu),
  _FUNC_NAME(and),
  _FUNC_NAME(or),
  _FUNC_NAME(xor),
  _FUNC_NAME(nor),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(slt),
  _FUNC_NAME(sltu),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
_TABLE_DEF_END

/*
Table begin: index=1 size=267
Mask=0x01ffffff	DMask=0xfe000000	CMask=0x00000000	Sig=0x02000026
Prob=0.154120879	Entropy=4.80729398	HTreeHeight=4.8912656
-------------------------------------------------------------------
mask=0xfe00003f	sig=0x02000020	prob=0.0356506239	name=add
mask=0xfe00003f	sig=0x02000021	prob=0.0356506239	name=addu
mask=0xfe00003f	sig=0x02000024	prob=0.0356506239	name=and
mask=0xfe00003f	sig=0x0200000d	prob=0.0356506239	name=brk
mask=0xfe00003f	sig=0x0200001a	prob=0.0356506239	name=div
mask=0xfe00003f	sig=0x0200001b	prob=0.0356506239	name=divu
mask=0xfe00003f	sig=0x02000009	prob=0.0356506239	name=jalr
mask=0xfe00003f	sig=0x02000008	prob=0.0356506239	name=jr
mask=0xfe00003f	sig=0x02000010	prob=0.0356506239	name=mfhi
mask=0xfe00003f	sig=0x02000012	prob=0.0356506239	name=mflo
mask=0xfe00003f	sig=0x02000011	prob=0.0356506239	name=mthi
mask=0xfe00003f	sig=0x02000013	prob=0.0356506239	name=mtlo
mask=0xfe00003f	sig=0x02000018	prob=0.0356506239	name=mult
mask=0xfe00003f	sig=0x02000019	prob=0.0356506239	name=multu
mask=0xfe00003f	sig=0x02000027	prob=0.0356506239	name=nor
mask=0xfe280034	sig=0x02280014	prob=8.91265597e-013	name=null
mask=0xfe040034	sig=0x02040014	prob=1.78253119e-012	name=null
mask=0xfe080034	sig=0x02080014	prob=1.78253119e-012	name=null
mask=0xfe220034	sig=0x02220014	prob=8.91265597e-013	name=null
mask=0xfe020034	sig=0x02020014	prob=1.78253119e-012	name=null
mask=0xfe820014	sig=0x02820014	prob=1.78253119e-012	name=null
mask=0xfe820030	sig=0x02820030	prob=1.78253119e-012	name=null
mask=0xfe840014	sig=0x02840014	prob=1.78253119e-012	name=null
mask=0xfe840030	sig=0x02840030	prob=1.78253119e-012	name=null
mask=0xfe240034	sig=0x02240014	prob=8.91265597e-013	name=null
mask=0xff840014	sig=0x03840014	prob=8.91265597e-013	name=null
mask=0xff840030	sig=0x03840030	prob=8.91265597e-013	name=null
mask=0xfea80014	sig=0x02a80014	prob=8.91265597e-013	name=null
mask=0xfea80030	sig=0x02a80030	prob=8.91265597e-013	name=null
mask=0xfe04000e	sig=0x0204000e	prob=1.78253119e-012	name=null
mask=0xfe08001e	sig=0x0208000e	prob=1.78253119e-012	name=null
mask=0xfe00000e	sig=0x0200000e	prob=1.78253119e-012	name=null
mask=0xfe62000e	sig=0x0262000e	prob=8.91265597e-013	name=null
mask=0xff08000e	sig=0x0308000e	prob=1.78253119e-012	name=null
mask=0xff28000e	sig=0x0328000e	prob=8.91265597e-013	name=null
mask=0xff04000e	sig=0x0304000e	prob=1.78253119e-012	name=null
mask=0xff24000e	sig=0x0324000e	prob=8.91265597e-013	name=null
mask=0xff88000e	sig=0x0388000e	prob=8.91265597e-013	name=null
mask=0xfea8000e	sig=0x02a8000e	prob=8.91265597e-013	name=null
mask=0xff84000e	sig=0x0384000e	prob=8.91265597e-013	name=null
mask=0xfea4000e	sig=0x02a4000e	prob=8.91265597e-013	name=null
mask=0xfea2000e	sig=0x02a2000e	prob=8.91265597e-013	name=null
mask=0xfe42000e	sig=0x0242000e	prob=1.78253119e-012	name=null
mask=0xfe08000e	sig=0x0208000e	prob=1.78253119e-012	name=null
mask=0xfea20030	sig=0x02a20030	prob=8.91265597e-013	name=null
mask=0xff040030	sig=0x03040030	prob=1.78253119e-012	name=null
mask=0xfe28003a	sig=0x0228000a	prob=8.91265597e-013	name=null
mask=0xfea20014	sig=0x02a20014	prob=8.91265597e-013	name=null
mask=0xfe000030	sig=0x02000030	prob=1.78253119e-012	name=null
mask=0xfe000014	sig=0x02000014	prob=1.78253119e-012	name=null
mask=0xfea40030	sig=0x02a40030	prob=8.91265597e-013	name=null
mask=0xfe080030	sig=0x02080030	prob=1.78253119e-012	name=null
mask=0xfe080014	sig=0x02080014	prob=1.78253119e-012	name=null
mask=0xfe040030	sig=0x02040030	prob=1.78253119e-012	name=null
mask=0xfe040014	sig=0x02040014	prob=1.78253119e-012	name=null
mask=0xfe020030	sig=0x02020030	prob=1.78253119e-012	name=null
mask=0xfe020014	sig=0x02020014	prob=1.78253119e-012	name=null
mask=0xff020030	sig=0x03020030	prob=8.91265597e-013	name=null
mask=0xff020014	sig=0x03020014	prob=8.91265597e-013	name=null
mask=0xfe880030	sig=0x02880030	prob=1.78253119e-012	name=null
mask=0xff880014	sig=0x03880014	prob=8.91265597e-013	name=null
mask=0xfe640014	sig=0x02640014	prob=8.91265597e-013	name=null
mask=0xfe420030	sig=0x02420030	prob=1.78253119e-012	name=null
mask=0xfe420014	sig=0x02420014	prob=1.78253119e-012	name=null
mask=0xfe620030	sig=0x02620030	prob=8.91265597e-013	name=null
mask=0xfe620014	sig=0x02620014	prob=8.91265597e-013	name=null
mask=0xff080030	sig=0x03080030	prob=1.78253119e-012	name=null
mask=0xff080014	sig=0x03080014	prob=1.78253119e-012	name=null
mask=0xff280030	sig=0x03280030	prob=8.91265597e-013	name=null
mask=0xff280014	sig=0x03280014	prob=8.91265597e-013	name=null
mask=0xfe880014	sig=0x02880014	prob=1.78253119e-012	name=null
mask=0xff040014	sig=0x03040014	prob=1.78253119e-012	name=null
mask=0xff240030	sig=0x03240030	prob=8.91265597e-013	name=null
mask=0xff240014	sig=0x03240014	prob=8.91265597e-013	name=null
mask=0xff880030	sig=0x03880030	prob=8.91265597e-013	name=null
mask=0xfe68002c	sig=0x0268002c	prob=8.91265597e-013	name=null
mask=0xfe82002c	sig=0x0282002c	prob=1.78253119e-012	name=null
mask=0xfe48002c	sig=0x0248002c	prob=1.78253119e-012	name=null
mask=0xfe480014	sig=0x02480014	prob=1.78253119e-012	name=null
mask=0xff480030	sig=0x03480030	prob=8.91265597e-013	name=null
mask=0xff480014	sig=0x03480014	prob=8.91265597e-013	name=null
mask=0xfe680030	sig=0x02680030	prob=8.91265597e-013	name=null
mask=0xfe680014	sig=0x02680014	prob=8.91265597e-013	name=null
mask=0xfe440030	sig=0x02440030	prob=1.78253119e-012	name=null
mask=0xfe440014	sig=0x02440014	prob=1.78253119e-012	name=null
mask=0xff440030	sig=0x03440030	prob=8.91265597e-013	name=null
mask=0xfe640030	sig=0x02640030	prob=8.91265597e-013	name=null
mask=0xfe62002c	sig=0x0262002c	prob=8.91265597e-013	name=null
mask=0xfe82000e	sig=0x0282000e	prob=1.78253119e-012	name=null
mask=0xff48002c	sig=0x0348002c	prob=8.91265597e-013	name=null
mask=0xfe84002c	sig=0x0284002c	prob=1.78253119e-012	name=null
mask=0xfe44002c	sig=0x0244002c	prob=1.78253119e-012	name=null
mask=0xff44002c	sig=0x0344002c	prob=8.91265597e-013	name=null
mask=0xfe64002c	sig=0x0264002c	prob=8.91265597e-013	name=null
mask=0xfe42002c	sig=0x0242002c	prob=1.78253119e-012	name=null
mask=0xff08002c	sig=0x0308002c	prob=1.78253119e-012	name=null
mask=0xff28002c	sig=0x0328002c	prob=8.91265597e-013	name=null
mask=0xff04002c	sig=0x0304002c	prob=1.78253119e-012	name=null
mask=0xff24002c	sig=0x0324002c	prob=8.91265597e-013	name=null
mask=0xff88002c	sig=0x0388002c	prob=8.91265597e-013	name=null
mask=0xfea8002c	sig=0x02a8002c	prob=8.91265597e-013	name=null
mask=0xff84002c	sig=0x0384002c	prob=8.91265597e-013	name=null
mask=0xfea4002c	sig=0x02a4002c	prob=8.91265597e-013	name=null
mask=0xfea2002c	sig=0x02a2002c	prob=8.91265597e-013	name=null
mask=0xfe00002c	sig=0x0200002c	prob=1.78253119e-012	name=null
mask=0xfe88002f	sig=0x02880005	prob=1.78253119e-012	name=null
mask=0xff02000e	sig=0x0302000e	prob=8.91265597e-013	name=null
mask=0xfe88000e	sig=0x0288000e	prob=1.78253119e-012	name=null
mask=0xfe84000e	sig=0x0284000e	prob=1.78253119e-012	name=null
mask=0xfe24001e	sig=0x0224000e	prob=8.91265597e-013	name=null
mask=0xfe08003a	sig=0x02080028	prob=1.78253119e-012	name=null
mask=0xfe04003c	sig=0x0204002c	prob=1.78253119e-012	name=null
mask=0xfe04003a	sig=0x02040028	prob=1.78253119e-012	name=null
mask=0xfe04001e	sig=0x0204000e	prob=1.78253119e-012	name=null
mask=0xfe28003c	sig=0x0228002c	prob=8.91265597e-013	name=null
mask=0xfe28003a	sig=0x02280028	prob=8.91265597e-013	name=null
mask=0xfe28001e	sig=0x0228000e	prob=8.91265597e-013	name=null
mask=0xfe24003c	sig=0x0224002c	prob=8.91265597e-013	name=null
mask=0xfe24003a	sig=0x02240028	prob=8.91265597e-013	name=null
mask=0xff440014	sig=0x03440014	prob=8.91265597e-013	name=null
mask=0xfe02000e	sig=0x0202000e	prob=1.78253119e-012	name=null
mask=0xfe84002f	sig=0x02840005	prob=1.78253119e-012	name=null
mask=0xfe82002f	sig=0x02820005	prob=1.78253119e-012	name=null
mask=0xfe48000e	sig=0x0248000e	prob=1.78253119e-012	name=null
mask=0xff48000e	sig=0x0348000e	prob=8.91265597e-013	name=null
mask=0xfe68000e	sig=0x0268000e	prob=8.91265597e-013	name=null
mask=0xfe44000e	sig=0x0244000e	prob=1.78253119e-012	name=null
mask=0xff44000e	sig=0x0344000e	prob=8.91265597e-013	name=null
mask=0xfe64000e	sig=0x0264000e	prob=8.91265597e-013	name=null
mask=0xfe480030	sig=0x02480030	prob=1.78253119e-012	name=null
mask=0xfe08002c	sig=0x0208002c	prob=1.78253119e-012	name=null
mask=0xfe04002c	sig=0x0204002c	prob=1.78253119e-012	name=null
mask=0xfe02002c	sig=0x0202002c	prob=1.78253119e-012	name=null
mask=0xff02002c	sig=0x0302002c	prob=8.91265597e-013	name=null
mask=0xfe88002c	sig=0x0288002c	prob=1.78253119e-012	name=null
mask=0xfe88002a	sig=0x02880028	prob=1.78253119e-012	name=null
mask=0xff08002f	sig=0x03080005	prob=1.78253119e-012	name=null
mask=0xfe44003b	sig=0x02440001	prob=1.78253119e-012	name=null
mask=0xfe44002f	sig=0x02440005	prob=1.78253119e-012	name=null
mask=0xff44003b	sig=0x03440001	prob=8.91265597e-013	name=null
mask=0xff44002f	sig=0x03440005	prob=8.91265597e-013	name=null
mask=0xfe64003b	sig=0x02640001	prob=8.91265597e-013	name=null
mask=0xfe64002f	sig=0x02640005	prob=8.91265597e-013	name=null
mask=0xfe42003b	sig=0x02420001	prob=1.78253119e-012	name=null
mask=0xfe42002f	sig=0x02420005	prob=1.78253119e-012	name=null
mask=0xfe62003b	sig=0x02620001	prob=8.91265597e-013	name=null
mask=0xfe62002f	sig=0x02620005	prob=8.91265597e-013	name=null
mask=0xfe04003b	sig=0x02040001	prob=1.78253119e-012	name=null
mask=0xfe68003b	sig=0x02680001	prob=8.91265597e-013	name=null
mask=0xff24002a	sig=0x03240028	prob=8.91265597e-013	name=null
mask=0xff88002a	sig=0x03880028	prob=8.91265597e-013	name=null
mask=0xfe08003c	sig=0x0208002c	prob=1.78253119e-012	name=null
mask=0xfe22001e	sig=0x0222000e	prob=8.91265597e-013	name=null
mask=0xfe22003a	sig=0x02220028	prob=8.91265597e-013	name=null
mask=0xfe22003c	sig=0x0222002c	prob=8.91265597e-013	name=null
mask=0xfe02001e	sig=0x0202000e	prob=1.78253119e-012	name=null
mask=0xfe02003a	sig=0x02020028	prob=1.78253119e-012	name=null
mask=0xfe02003c	sig=0x0202002c	prob=1.78253119e-012	name=null
mask=0xfe82002a	sig=0x02820028	prob=1.78253119e-012	name=null
mask=0xfe84002a	sig=0x02840028	prob=1.78253119e-012	name=null
mask=0xff84002f	sig=0x03840005	prob=8.91265597e-013	name=null
mask=0xfea8003b	sig=0x02a80001	prob=8.91265597e-013	name=null
mask=0xff28003b	sig=0x03280001	prob=8.91265597e-013	name=null
mask=0xff28002f	sig=0x03280005	prob=8.91265597e-013	name=null
mask=0xff04003b	sig=0x03040001	prob=1.78253119e-012	name=null
mask=0xff04002f	sig=0x03040005	prob=1.78253119e-012	name=null
mask=0xff24003b	sig=0x03240001	prob=8.91265597e-013	name=null
mask=0xff24002f	sig=0x03240005	prob=8.91265597e-013	name=null
mask=0xff88003b	sig=0x03880001	prob=8.91265597e-013	name=null
mask=0xff88002f	sig=0x03880005	prob=8.91265597e-013	name=null
mask=0xff08003b	sig=0x03080001	prob=1.78253119e-012	name=null
mask=0xfea8002f	sig=0x02a80005	prob=8.91265597e-013	name=null
mask=0xff84003b	sig=0x03840001	prob=8.91265597e-013	name=null
mask=0xfe28002e	sig=0x0228000e	prob=8.91265597e-013	name=null
mask=0xfea4003b	sig=0x02a40001	prob=8.91265597e-013	name=null
mask=0xfea4002f	sig=0x02a40005	prob=8.91265597e-013	name=null
mask=0xfea2003b	sig=0x02a20001	prob=8.91265597e-013	name=null
mask=0xfea2002f	sig=0x02a20005	prob=8.91265597e-013	name=null
mask=0xfe00003b	sig=0x02000001	prob=1.78253119e-012	name=null
mask=0xfe00002f	sig=0x02000005	prob=1.78253119e-012	name=null
mask=0xfe68002f	sig=0x02680005	prob=8.91265597e-013	name=null
mask=0xfe48003b	sig=0x02480001	prob=1.78253119e-012	name=null
mask=0xfe48002f	sig=0x02480005	prob=1.78253119e-012	name=null
mask=0xff48003b	sig=0x03480001	prob=8.91265597e-013	name=null
mask=0xff48002f	sig=0x03480005	prob=8.91265597e-013	name=null
mask=0xfe08003a	sig=0x0208000a	prob=1.78253119e-012	name=null
mask=0xfe62002a	sig=0x02620028	prob=8.91265597e-013	name=null
mask=0xff08002a	sig=0x03080028	prob=1.78253119e-012	name=null
mask=0xff28002a	sig=0x03280028	prob=8.91265597e-013	name=null
mask=0xff04002a	sig=0x03040028	prob=1.78253119e-012	name=null
mask=0xfe24002e	sig=0x0224000e	prob=8.91265597e-013	name=null
mask=0xfe24003a	sig=0x0224000a	prob=8.91265597e-013	name=null
mask=0xff02003a	sig=0x0302000a	prob=8.91265597e-013	name=null
mask=0xff48003a	sig=0x0348000a	prob=8.91265597e-013	name=null
mask=0xff44003a	sig=0x0344000a	prob=8.91265597e-013	name=null
mask=0xff88003a	sig=0x0388000a	prob=8.91265597e-013	name=null
mask=0xff84003a	sig=0x0384000a	prob=8.91265597e-013	name=null
mask=0xfe00003a	sig=0x0200000a	prob=1.78253119e-012	name=null
mask=0xfe02002a	sig=0x02020028	prob=1.78253119e-012	name=null
mask=0xfe04003a	sig=0x0204000a	prob=1.78253119e-012	name=null
mask=0xfe02003a	sig=0x0202000a	prob=1.78253119e-012	name=null
mask=0xfe02003a	sig=0x0202000a	prob=1.78253119e-012	name=null
mask=0xfe02002e	sig=0x0202000e	prob=1.78253119e-012	name=null
mask=0xfe22003a	sig=0x0222000a	prob=8.91265597e-013	name=null
mask=0xfe22002e	sig=0x0222000e	prob=8.91265597e-013	name=null
mask=0xfe08003a	sig=0x0208000a	prob=1.78253119e-012	name=null
mask=0xfe08002e	sig=0x0208000e	prob=1.78253119e-012	name=null
mask=0xfe04003a	sig=0x0204000a	prob=1.78253119e-012	name=null
mask=0xfe04002e	sig=0x0204000e	prob=1.78253119e-012	name=null
mask=0xfea40014	sig=0x02a40014	prob=8.91265597e-013	name=null
mask=0xfe64002a	sig=0x02640028	prob=8.91265597e-013	name=null
mask=0xfe42002a	sig=0x02420028	prob=1.78253119e-012	name=null
mask=0xff02002a	sig=0x03020028	prob=8.91265597e-013	name=null
mask=0xfe04002a	sig=0x02040028	prob=1.78253119e-012	name=null
mask=0xfe08002a	sig=0x02080028	prob=1.78253119e-012	name=null
mask=0xfea8002a	sig=0x02a80028	prob=8.91265597e-013	name=null
mask=0xff84002a	sig=0x03840028	prob=8.91265597e-013	name=null
mask=0xfea4002a	sig=0x02a40028	prob=8.91265597e-013	name=null
mask=0xfea2002a	sig=0x02a20028	prob=8.91265597e-013	name=null
mask=0xfe48002a	sig=0x02480028	prob=1.78253119e-012	name=null
mask=0xfe08003b	sig=0x02080001	prob=1.78253119e-012	name=null
mask=0xfe08002f	sig=0x02080005	prob=1.78253119e-012	name=null
mask=0xfe00002a	sig=0x02000028	prob=1.78253119e-012	name=null
mask=0xfe02003b	sig=0x02020001	prob=1.78253119e-012	name=null
mask=0xff44002a	sig=0x03440028	prob=8.91265597e-013	name=null
mask=0xfe44002a	sig=0x02440028	prob=1.78253119e-012	name=null
mask=0xfe68002a	sig=0x02680028	prob=8.91265597e-013	name=null
mask=0xff48002a	sig=0x03480028	prob=8.91265597e-013	name=null
mask=0xfe82003b	sig=0x02820001	prob=1.78253119e-012	name=null
mask=0xfe88003b	sig=0x02880001	prob=1.78253119e-012	name=null
mask=0xff02002f	sig=0x03020005	prob=8.91265597e-013	name=null
mask=0xff02003b	sig=0x03020001	prob=8.91265597e-013	name=null
mask=0xfe02002f	sig=0x02020005	prob=1.78253119e-012	name=null
mask=0xfe04002f	sig=0x02040005	prob=1.78253119e-012	name=null
mask=0xfe84003b	sig=0x02840001	prob=1.78253119e-012	name=null
mask=0xfe00003f	sig=0x02000025	prob=0.0356506239	name=or
mask=0xfe00403f	sig=0x02004000	prob=0.00178253119	name=sll
mask=0xfe00203f	sig=0x02002000	prob=0.00178253119	name=sll
mask=0xfe00103f	sig=0x02001000	prob=0.00178253119	name=sll
mask=0xfe00083f	sig=0x02000800	prob=0.00178253119	name=sll
mask=0xfe00043f	sig=0x02000400	prob=0.00178253119	name=sll
mask=0xfe00023f	sig=0x02000200	prob=0.00178253119	name=sll
mask=0xfe00013f	sig=0x02000100	prob=0.00178253119	name=sll
mask=0xfe40003f	sig=0x02400000	prob=0.00178253119	name=sll
mask=0xfe0000bf	sig=0x02000080	prob=0.00178253119	name=sll
mask=0xfe00007f	sig=0x02000040	prob=0.00178253119	name=sll
mask=0xfe01003f	sig=0x02010000	prob=0.00178253119	name=sll
mask=0xfe02003f	sig=0x02020000	prob=0.00178253119	name=sll
mask=0xfe04003f	sig=0x02040000	prob=0.00178253119	name=sll
mask=0xfe08003f	sig=0x02080000	prob=0.00178253119	name=sll
mask=0xfe10003f	sig=0x02100000	prob=0.00178253119	name=sll
mask=0xfe20003f	sig=0x02200000	prob=0.00178253119	name=sll
mask=0xfe80003f	sig=0x02800000	prob=0.00178253119	name=sll
mask=0xff00003f	sig=0x03000000	prob=0.00178253119	name=sll
mask=0xfe00003f	sig=0x02000000	prob=0.00356506239	name=sll
mask=0xfe00803f	sig=0x02008000	prob=0.00178253119	name=sll
mask=0xfe00003f	sig=0x02000004	prob=0.0356506239	name=sllv
mask=0xfe00003f	sig=0x0200002a	prob=0.0356506239	name=slt
mask=0xfe00003f	sig=0x0200002b	prob=0.0356506239	name=sltu
mask=0xfe00003f	sig=0x02000003	prob=0.0356506239	name=sra
mask=0xfe00003f	sig=0x02000007	prob=0.0356506239	name=srav
mask=0xfe00003f	sig=0x02000002	prob=0.0356506239	name=srl
mask=0xfe00003f	sig=0x02000006	prob=0.0356506239	name=srlv
mask=0xfe00003f	sig=0x02000022	prob=0.0356506239	name=sub
mask=0xfe00003f	sig=0x02000023	prob=0.0356506239	name=subu
mask=0xfe00003f	sig=0x0200000c	prob=0.0356506239	name=syscall
mask=0xfe00003f	sig=0x02000026	prob=0.0356506239	name=xor
-------------------------------------------------------------------
Table Mask=0x0000003f*/

_TABLE_DEF_BEGIN(table_2, 64)
  _FUNC_NAME(sll),
  _FUNC_NAME(null),
  _FUNC_NAME(srl),
  _FUNC_NAME(sra),
  _FUNC_NAME(sllv),
  _FUNC_NAME(null),
  _FUNC_NAME(srlv),
  _FUNC_NAME(srav),
  _FUNC_NAME(jr),
  _FUNC_NAME(jalr),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(syscall),
  _FUNC_NAME(brk),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(mfhi),
  _FUNC_NAME(mthi),
  _FUNC_NAME(mflo),
  _FUNC_NAME(mtlo),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(mult),
  _FUNC_NAME(multu),
  _FUNC_NAME(div),
  _FUNC_NAME(divu),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(add),
  _FUNC_NAME(addu),
  _FUNC_NAME(sub),
  _FUNC_NAME(subu),
  _FUNC_NAME(and),
  _FUNC_NAME(or),
  _FUNC_NAME(xor),
  _FUNC_NAME(nor),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(slt),
  _FUNC_NAME(sltu),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
_TABLE_DEF_END

/*
Table begin: index=34 size=188
Mask=0x01ef003f	DMask=0xfe000000	CMask=0x00000000	Sig=0x4548000a
Prob=0.0659340659	Entropy=2.58496252	HTreeHeight=2.83333333
-------------------------------------------------------------------
mask=0xffe30000	sig=0x45000000	prob=0.166666667	name=bc1f
mask=0xffe30000	sig=0x45010000	prob=0.166666667	name=bc1t
mask=0xffe00000	sig=0x44400000	prob=0.166666667	name=cfc1
mask=0xffe00000	sig=0x44c00000	prob=0.166666667	name=ctc1
mask=0xffe00000	sig=0x44000000	prob=0.166666667	name=mfc1
mask=0xffe00000	sig=0x44800000	prob=0.166666667	name=mtc1
mask=0xfe600000	sig=0x44600000	prob=5.20833333e-013	name=null
mask=0xff240030	sig=0x45240030	prob=2.08333333e-012	name=null
mask=0xff400000	sig=0x45400000	prob=5.20833333e-013	name=null
mask=0xff800000	sig=0x45800000	prob=5.20833333e-013	name=null
mask=0xff840014	sig=0x45840014	prob=2.08333333e-012	name=null
mask=0xff840030	sig=0x45840030	prob=2.08333333e-012	name=null
mask=0xfea80014	sig=0x44a80014	prob=2.08333333e-012	name=null
mask=0xfea80030	sig=0x44a80030	prob=2.08333333e-012	name=null
mask=0xff880014	sig=0x45880014	prob=2.08333333e-012	name=null
mask=0xff880030	sig=0x45880030	prob=2.08333333e-012	name=null
mask=0xff240014	sig=0x45240014	prob=2.08333333e-012	name=null
mask=0xfe62000e	sig=0x4462000e	prob=2.08333333e-012	name=null
mask=0xff200000	sig=0x45200000	prob=5.20833333e-013	name=null
mask=0xff020000	sig=0x45020000	prob=5.20833333e-013	name=null
mask=0xfea00000	sig=0x44a00000	prob=5.20833333e-013	name=null
mask=0xfe200030	sig=0x44200010	prob=5.20833333e-013	name=null
mask=0xfe200028	sig=0x44200008	prob=5.20833333e-013	name=null
mask=0xfe200018	sig=0x44200008	prob=5.20833333e-013	name=null
mask=0xfe200000	sig=0x44200000	prob=1.04166667e-012	name=null
mask=0xfe240034	sig=0x44240014	prob=2.08333333e-012	name=null
mask=0xfe220034	sig=0x44220014	prob=2.08333333e-012	name=null
mask=0xfe280034	sig=0x44280014	prob=2.08333333e-012	name=null
mask=0xfe220028	sig=0x44220008	prob=4.16666666e-012	name=null
mask=0xfe280014	sig=0x44280014	prob=4.16666666e-012	name=null
mask=0xfe28002c	sig=0x4428002c	prob=4.16666666e-012	name=null
mask=0xfe220018	sig=0x44220008	prob=4.16666666e-012	name=null
mask=0xff480000	sig=0x45480000	prob=4.16666666e-012	name=null
mask=0xfe680000	sig=0x44680000	prob=4.16666666e-012	name=null
mask=0xff440000	sig=0x45440000	prob=4.16666666e-012	name=null
mask=0xfe640000	sig=0x44640000	prob=4.16666666e-012	name=null
mask=0xfe220014	sig=0x44220014	prob=4.16666666e-012	name=null
mask=0xfea40014	sig=0x44a40014	prob=2.08333333e-012	name=null
mask=0xfea20030	sig=0x44a20030	prob=2.08333333e-012	name=null
mask=0xfea20014	sig=0x44a20014	prob=2.08333333e-012	name=null
mask=0xfe280030	sig=0x44280030	prob=4.16666666e-012	name=null
mask=0xff280014	sig=0x45280014	prob=2.08333333e-012	name=null
mask=0xfe240030	sig=0x44240030	prob=4.16666666e-012	name=null
mask=0xfe240014	sig=0x44240014	prob=4.16666666e-012	name=null
mask=0xfe220030	sig=0x44220030	prob=4.16666666e-012	name=null
mask=0xfea40030	sig=0x44a40030	prob=2.08333333e-012	name=null
mask=0xff020030	sig=0x45020030	prob=2.08333333e-012	name=null
mask=0xff020014	sig=0x45020014	prob=2.08333333e-012	name=null
mask=0xfe640014	sig=0x44640014	prob=2.08333333e-012	name=null
mask=0xfe620030	sig=0x44620030	prob=2.08333333e-012	name=null
mask=0xfe620014	sig=0x44620014	prob=2.08333333e-012	name=null
mask=0xff280030	sig=0x45280030	prob=2.08333333e-012	name=null
mask=0xff48002c	sig=0x4548002c	prob=2.08333333e-012	name=null
mask=0xff02002c	sig=0x4502002c	prob=2.08333333e-012	name=null
mask=0xfe200032	sig=0x44200022	prob=5.20833333e-013	name=null
mask=0xfe200031	sig=0x44200021	prob=5.20833333e-013	name=null
mask=0xff480030	sig=0x45480030	prob=2.08333333e-012	name=null
mask=0xff480014	sig=0x45480014	prob=2.08333333e-012	name=null
mask=0xfe680030	sig=0x44680030	prob=2.08333333e-012	name=null
mask=0xfe680014	sig=0x44680014	prob=2.08333333e-012	name=null
mask=0xff440030	sig=0x45440030	prob=2.08333333e-012	name=null
mask=0xfe640030	sig=0x44640030	prob=2.08333333e-012	name=null
mask=0xfe62002c	sig=0x4462002c	prob=2.08333333e-012	name=null
mask=0xfe24002c	sig=0x4424002c	prob=4.16666666e-012	name=null
mask=0xfe22002c	sig=0x4422002c	prob=4.16666666e-012	name=null
mask=0xfe68002c	sig=0x4468002c	prob=2.08333333e-012	name=null
mask=0xff44002c	sig=0x4544002c	prob=2.08333333e-012	name=null
mask=0xfe64002c	sig=0x4464002c	prob=2.08333333e-012	name=null
mask=0xff28002c	sig=0x4528002c	prob=2.08333333e-012	name=null
mask=0xff24002c	sig=0x4524002c	prob=2.08333333e-012	name=null
mask=0xff88002c	sig=0x4588002c	prob=2.08333333e-012	name=null
mask=0xfea8002c	sig=0x44a8002c	prob=2.08333333e-012	name=null
mask=0xff84002c	sig=0x4584002c	prob=2.08333333e-012	name=null
mask=0xfea4002c	sig=0x44a4002c	prob=2.08333333e-012	name=null
mask=0xfea2002c	sig=0x44a2002c	prob=2.08333333e-012	name=null
mask=0xfe24001e	sig=0x4424000e	prob=2.08333333e-012	name=null
mask=0xff24000e	sig=0x4524000e	prob=2.08333333e-012	name=null
mask=0xff88000e	sig=0x4588000e	prob=2.08333333e-012	name=null
mask=0xfea8000e	sig=0x44a8000e	prob=2.08333333e-012	name=null
mask=0xff84000e	sig=0x4584000e	prob=2.08333333e-012	name=null
mask=0xfea4000e	sig=0x44a4000e	prob=2.08333333e-012	name=null
mask=0xfea2000e	sig=0x44a2000e	prob=2.08333333e-012	name=null
mask=0xfe28000e	sig=0x4428000e	prob=4.16666666e-012	name=null
mask=0xfe24000e	sig=0x4424000e	prob=4.16666666e-012	name=null
mask=0xfe22000e	sig=0x4422000e	prob=4.16666666e-012	name=null
mask=0xff02000e	sig=0x4502000e	prob=2.08333333e-012	name=null
mask=0xff28000e	sig=0x4528000e	prob=2.08333333e-012	name=null
mask=0xfe28003c	sig=0x4428002c	prob=2.08333333e-012	name=null
mask=0xfe28003a	sig=0x44280028	prob=2.08333333e-012	name=null
mask=0xfe28001e	sig=0x4428000e	prob=2.08333333e-012	name=null
mask=0xfe24003c	sig=0x4424002c	prob=2.08333333e-012	name=null
mask=0xfe24003a	sig=0x44240028	prob=2.08333333e-012	name=null
mask=0xff440014	sig=0x45440014	prob=2.08333333e-012	name=null
mask=0xff48000e	sig=0x4548000e	prob=2.08333333e-012	name=null
mask=0xfe68000e	sig=0x4468000e	prob=2.08333333e-012	name=null
mask=0xff44000e	sig=0x4544000e	prob=2.08333333e-012	name=null
mask=0xfe64000e	sig=0x4464000e	prob=2.08333333e-012	name=null
mask=0xfe22003a	sig=0x44220028	prob=2.08333333e-012	name=null
mask=0xff48002f	sig=0x45480005	prob=2.08333333e-012	name=null
mask=0xfe68003b	sig=0x44680001	prob=2.08333333e-012	name=null
mask=0xff44003b	sig=0x45440001	prob=2.08333333e-012	name=null
mask=0xff44002f	sig=0x45440005	prob=2.08333333e-012	name=null
mask=0xfe64003b	sig=0x44640001	prob=2.08333333e-012	name=null
mask=0xfe64002f	sig=0x44640005	prob=2.08333333e-012	name=null
mask=0xfe62003b	sig=0x44620001	prob=2.08333333e-012	name=null
mask=0xfe62002f	sig=0x44620005	prob=2.08333333e-012	name=null
mask=0xff24002a	sig=0x45240028	prob=2.08333333e-012	name=null
mask=0xff88002a	sig=0x45880028	prob=2.08333333e-012	name=null
mask=0xfe22001e	sig=0x4422000e	prob=2.08333333e-012	name=null
mask=0xff48003b	sig=0x45480001	prob=2.08333333e-012	name=null
mask=0xfe22003c	sig=0x4422002c	prob=2.08333333e-012	name=null
mask=0xfe220027	sig=0x44220004	prob=4.16666666e-012	name=null
mask=0xff02002a	sig=0x45020028	prob=2.08333333e-012	name=null
mask=0xfe22002a	sig=0x44220028	prob=4.16666666e-012	name=null
mask=0xfea8002a	sig=0x44a80028	prob=2.08333333e-012	name=null
mask=0xfe24002a	sig=0x44240028	prob=4.16666666e-012	name=null
mask=0xff84002a	sig=0x45840028	prob=2.08333333e-012	name=null
mask=0xfe28002a	sig=0x44280028	prob=4.16666666e-012	name=null
mask=0xfea4002a	sig=0x44a40028	prob=2.08333333e-012	name=null
mask=0xfea2002a	sig=0x44a20028	prob=2.08333333e-012	name=null
mask=0xfea4002f	sig=0x44a40005	prob=2.08333333e-012	name=null
mask=0xfea8003b	sig=0x44a80001	prob=2.08333333e-012	name=null
mask=0xff28003b	sig=0x45280001	prob=2.08333333e-012	name=null
mask=0xff28002f	sig=0x45280005	prob=2.08333333e-012	name=null
mask=0xff24003b	sig=0x45240001	prob=2.08333333e-012	name=null
mask=0xff24002f	sig=0x45240005	prob=2.08333333e-012	name=null
mask=0xff88003b	sig=0x45880001	prob=2.08333333e-012	name=null
mask=0xff88002f	sig=0x45880005	prob=2.08333333e-012	name=null
mask=0xfea8002f	sig=0x44a80005	prob=2.08333333e-012	name=null
mask=0xff84003b	sig=0x45840001	prob=2.08333333e-012	name=null
mask=0xff84002f	sig=0x45840005	prob=2.08333333e-012	name=null
mask=0xfea4003b	sig=0x44a40001	prob=2.08333333e-012	name=null
mask=0xff02003b	sig=0x45020001	prob=2.08333333e-012	name=null
mask=0xfea2003b	sig=0x44a20001	prob=2.08333333e-012	name=null
mask=0xfea2002f	sig=0x44a20005	prob=2.08333333e-012	name=null
mask=0xfe28003b	sig=0x44280001	prob=4.16666666e-012	name=null
mask=0xfe28002f	sig=0x44280005	prob=4.16666666e-012	name=null
mask=0xfe24003b	sig=0x44240001	prob=4.16666666e-012	name=null
mask=0xfe24002f	sig=0x44240005	prob=4.16666666e-012	name=null
mask=0xfe22003b	sig=0x44220001	prob=4.16666666e-012	name=null
mask=0xfe68002f	sig=0x44680005	prob=2.08333333e-012	name=null
mask=0xfe220000	sig=0x44220000	prob=8.33333333e-012	name=null
mask=0xff020000	sig=0x45020000	prob=4.16666666e-012	name=null
mask=0xff840000	sig=0x45840000	prob=4.16666666e-012	name=null
mask=0xff88003a	sig=0x4588000a	prob=2.08333333e-012	name=null
mask=0xff84003a	sig=0x4584000a	prob=2.08333333e-012	name=null
mask=0xfe22003a	sig=0x4422000a	prob=2.08333333e-012	name=null
mask=0xfe22002e	sig=0x4422000e	prob=2.08333333e-012	name=null
mask=0xfe28003a	sig=0x4428000a	prob=2.08333333e-012	name=null
mask=0xfe28002e	sig=0x4428000e	prob=2.08333333e-012	name=null
mask=0xff880000	sig=0x45880000	prob=4.16666666e-012	name=null
mask=0xfe620000	sig=0x44620000	prob=4.16666666e-012	name=null
mask=0xff280000	sig=0x45280000	prob=4.16666666e-012	name=null
mask=0xff240000	sig=0x45240000	prob=4.16666666e-012	name=null
mask=0xfea80000	sig=0x44a80000	prob=4.16666666e-012	name=null
mask=0xff44003a	sig=0x4544000a	prob=2.08333333e-012	name=null
mask=0xfea40000	sig=0x44a40000	prob=4.16666666e-012	name=null
mask=0xfea20000	sig=0x44a20000	prob=4.16666666e-012	name=null
mask=0xfe280030	sig=0x44280010	prob=4.16666666e-012	name=null
mask=0xfe240030	sig=0x44240010	prob=4.16666666e-012	name=null
mask=0xfe280028	sig=0x44280008	prob=4.16666666e-012	name=null
mask=0xfe280018	sig=0x44280008	prob=4.16666666e-012	name=null
mask=0xfe240028	sig=0x44240008	prob=4.16666666e-012	name=null
mask=0xfe240018	sig=0x44240008	prob=4.16666666e-012	name=null
mask=0xfe280000	sig=0x44280000	prob=8.33333333e-012	name=null
mask=0xfe220030	sig=0x44220010	prob=4.16666666e-012	name=null
mask=0xfe280032	sig=0x44280022	prob=4.16666666e-012	name=null
mask=0xff02002f	sig=0x45020005	prob=2.08333333e-012	name=null
mask=0xfe22002f	sig=0x44220005	prob=4.16666666e-012	name=null
mask=0xff48002a	sig=0x45480028	prob=2.08333333e-012	name=null
mask=0xfe68002a	sig=0x44680028	prob=2.08333333e-012	name=null
mask=0xff44002a	sig=0x45440028	prob=2.08333333e-012	name=null
mask=0xfe64002a	sig=0x44640028	prob=2.08333333e-012	name=null
mask=0xfe62002a	sig=0x44620028	prob=2.08333333e-012	name=null
mask=0xff28002a	sig=0x45280028	prob=2.08333333e-012	name=null
mask=0xfe24002e	sig=0x4424000e	prob=2.08333333e-012	name=null
mask=0xfe220032	sig=0x44220022	prob=4.16666666e-012	name=null
mask=0xfe240000	sig=0x44240000	prob=8.33333333e-012	name=null
mask=0xfe240032	sig=0x44240022	prob=4.16666666e-012	name=null
mask=0xfe280031	sig=0x44280021	prob=4.16666666e-012	name=null
mask=0xfe240031	sig=0x44240021	prob=4.16666666e-012	name=null
mask=0xfe220031	sig=0x44220021	prob=4.16666666e-012	name=null
mask=0xfe24003a	sig=0x4424000a	prob=2.08333333e-012	name=null
mask=0xff02003a	sig=0x4502000a	prob=2.08333333e-012	name=null
mask=0xfe280027	sig=0x44280004	prob=4.16666666e-012	name=null
mask=0xfe240027	sig=0x44240004	prob=4.16666666e-012	name=null
mask=0xfe200027	sig=0x44200004	prob=5.20833333e-013	name=null
mask=0xff48003a	sig=0x4548000a	prob=2.08333333e-012	name=null
-------------------------------------------------------------------
Table Mask=0x01e00000*/

_TABLE_DEF_BEGIN(table_3, 16)
  _FUNC_NAME(mfc1),
  _FUNC_NAME(null),
  _FUNC_NAME(cfc1),
  _FUNC_NAME(null),
  _FUNC_NAME(mtc1),
  _FUNC_NAME(null),
  _FUNC_NAME(ctc1),
  _FUNC_NAME(null),
  _STUB_NAME(stub_3_8),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
_TABLE_DEF_END

/*
Table begin: index=8 size=12
Mask=0x0003003f	DMask=0xffe00000	CMask=0x00020000	Sig=0x4502000a
Prob=0.333333333	Entropy=1	HTreeHeight=1.5
-------------------------------------------------------------------
mask=0xffe30000	sig=0x45000000	prob=0.5	name=bc1f
mask=0xffe30000	sig=0x45010000	prob=0.5	name=bc1t
mask=0xffe20000	sig=0x45020000	prob=1.953125e-013	name=null
mask=0xffe20030	sig=0x45020030	prob=7.8125e-013	name=null
mask=0xffe20014	sig=0x45020014	prob=7.8125e-013	name=null
mask=0xffe2002c	sig=0x4502002c	prob=7.8125e-013	name=null
mask=0xffe2000e	sig=0x4502000e	prob=7.8125e-013	name=null
mask=0xffe2002a	sig=0x45020028	prob=7.8125e-013	name=null
mask=0xffe2003b	sig=0x45020001	prob=7.8125e-013	name=null
mask=0xffe20000	sig=0x45020000	prob=1.5625e-012	name=null
mask=0xffe2002f	sig=0x45020005	prob=7.8125e-013	name=null
mask=0xffe2003a	sig=0x4502000a	prob=7.8125e-013	name=null
-------------------------------------------------------------------
Table Mask=0x00030000*/

_TABLE_DEF_BEGIN(table_4, 4)
  _FUNC_NAME(bc1f),
  _FUNC_NAME(bc1t),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
_TABLE_DEF_END

/*
Table begin: index=35 size=308
Mask=0x01ee003f	DMask=0xfe000000	CMask=0x00000000	Sig=0x46000001
Prob=0.241758242	Entropy=4.45943163	HTreeHeight=4.59090909
-------------------------------------------------------------------
mask=0xffe0003f	sig=0x46200005	prob=0.0454545454	name=abs_d
mask=0xffe0003f	sig=0x46000005	prob=0.0454545454	name=abs_s
mask=0xffe0003f	sig=0x46200000	prob=0.0454545454	name=add_d
mask=0xffe0003f	sig=0x46000000	prob=0.0454545454	name=add_s
mask=0xffe00030	sig=0x46200030	prob=0.0454545454	name=c_cond_d
mask=0xffe00030	sig=0x46000030	prob=0.0454545454	name=c_cond_s
mask=0xffe0003f	sig=0x46000021	prob=0.0454545454	name=cvt_d_s
mask=0xffe0003f	sig=0x46800021	prob=0.0454545454	name=cvt_d_w
mask=0xffe0003f	sig=0x46200020	prob=0.0454545454	name=cvt_s_d
mask=0xffe0003f	sig=0x46800020	prob=0.0454545454	name=cvt_s_w
mask=0xffe0003f	sig=0x46200024	prob=0.0454545454	name=cvt_w_d
mask=0xffe0003f	sig=0x46000024	prob=0.0454545454	name=cvt_w_s
mask=0xffe0003f	sig=0x46200003	prob=0.0454545454	name=div_d
mask=0xffe0003f	sig=0x46000003	prob=0.0454545454	name=div_s
mask=0xffe0003f	sig=0x46200006	prob=0.0454545454	name=mov_d
mask=0xffe0003f	sig=0x46000006	prob=0.0454545454	name=mov_s
mask=0xffe0003f	sig=0x46200002	prob=0.0454545454	name=mul_d
mask=0xffe0003f	sig=0x46000002	prob=0.0454545454	name=mul_s
mask=0xffe0003f	sig=0x46200007	prob=0.0454545454	name=neg_d
mask=0xffe0003f	sig=0x46000007	prob=0.0454545454	name=neg_s
mask=0xfe800004	sig=0x46800004	prob=2.84090909e-013	name=null
mask=0xff020000	sig=0x47020000	prob=1.42045455e-013	name=null
mask=0xff200000	sig=0x47200000	prob=1.42045455e-013	name=null
mask=0xff000000	sig=0x47000000	prob=2.84090909e-013	name=null
mask=0xfe000018	sig=0x46000008	prob=2.84090909e-013	name=null
mask=0xfe000028	sig=0x46000008	prob=2.84090909e-013	name=null
mask=0xfe000030	sig=0x46000010	prob=2.84090909e-013	name=null
mask=0xfe600000	sig=0x46600000	prob=1.42045455e-013	name=null
mask=0xff400000	sig=0x47400000	prob=1.42045455e-013	name=null
mask=0xfe400000	sig=0x46400000	prob=2.84090909e-013	name=null
mask=0xfe800002	sig=0x46800002	prob=2.84090909e-013	name=null
mask=0xff800000	sig=0x47800000	prob=1.42045455e-013	name=null
mask=0xff840014	sig=0x47840014	prob=5.68181818e-013	name=null
mask=0xff840030	sig=0x47840030	prob=5.68181818e-013	name=null
mask=0xfea80014	sig=0x46a80014	prob=5.68181818e-013	name=null
mask=0xfea80030	sig=0x46a80030	prob=5.68181818e-013	name=null
mask=0xff880014	sig=0x47880014	prob=5.68181818e-013	name=null
mask=0xff880030	sig=0x47880030	prob=5.68181818e-013	name=null
mask=0xfe000035	sig=0x46000025	prob=2.84090909e-013	name=null
mask=0xfe820008	sig=0x46820008	prob=2.27272727e-012	name=null
mask=0xfea00035	sig=0x46000020	prob=2.84090909e-013	name=null
mask=0xfe08001e	sig=0x4608000e	prob=1.13636364e-012	name=null
mask=0xfe280034	sig=0x46280014	prob=5.68181818e-013	name=null
mask=0xfe040034	sig=0x46040014	prob=1.13636364e-012	name=null
mask=0xfe080034	sig=0x46080014	prob=1.13636364e-012	name=null
mask=0xfe220034	sig=0x46220014	prob=5.68181818e-013	name=null
mask=0xfe020034	sig=0x46020014	prob=1.13636364e-012	name=null
mask=0xfea00000	sig=0x46a00000	prob=1.42045455e-013	name=null
mask=0xfe820014	sig=0x46820014	prob=1.13636364e-012	name=null
mask=0xfe820030	sig=0x46820030	prob=1.13636364e-012	name=null
mask=0xfe840014	sig=0x46840014	prob=1.13636364e-012	name=null
mask=0xfe840030	sig=0x46840030	prob=1.13636364e-012	name=null
mask=0xfe240034	sig=0x46240014	prob=5.68181818e-013	name=null
mask=0xfe200018	sig=0x46200008	prob=1.42045455e-013	name=null
mask=0xfe200028	sig=0x46200008	prob=1.42045455e-013	name=null
mask=0xfe200030	sig=0x46200010	prob=1.42045455e-013	name=null
mask=0xfe480000	sig=0x46480000	prob=2.27272727e-012	name=null
mask=0xfea20014	sig=0x46a20014	prob=5.68181818e-013	name=null
mask=0xfea20030	sig=0x46a20030	prob=5.68181818e-013	name=null
mask=0xfea40014	sig=0x46a40014	prob=5.68181818e-013	name=null
mask=0xfe640000	sig=0x46640000	prob=1.13636364e-012	name=null
mask=0xff440000	sig=0x47440000	prob=1.13636364e-012	name=null
mask=0xfe440000	sig=0x46440000	prob=2.27272727e-012	name=null
mask=0xfe680000	sig=0x46680000	prob=1.13636364e-012	name=null
mask=0xff480000	sig=0x47480000	prob=1.13636364e-012	name=null
mask=0xfea40030	sig=0x46a40030	prob=5.68181818e-013	name=null
mask=0xfe220018	sig=0x46220008	prob=1.13636364e-012	name=null
mask=0xfe020018	sig=0x46020008	prob=2.27272727e-012	name=null
mask=0xfe220028	sig=0x46220008	prob=1.13636364e-012	name=null
mask=0xfe020028	sig=0x46020008	prob=2.27272727e-012	name=null
mask=0xfe020030	sig=0x46020010	prob=2.27272727e-012	name=null
mask=0xfe820002	sig=0x46820002	prob=2.27272727e-012	name=null
mask=0xfe820004	sig=0x46820004	prob=2.27272727e-012	name=null
mask=0xfe240028	sig=0x46240008	prob=1.13636364e-012	name=null
mask=0xfe620030	sig=0x46620030	prob=5.68181818e-013	name=null
mask=0xff240030	sig=0x47240030	prob=5.68181818e-013	name=null
mask=0xff040014	sig=0x47040014	prob=1.13636364e-012	name=null
mask=0xfe880014	sig=0x46880014	prob=1.13636364e-012	name=null
mask=0xff280014	sig=0x47280014	prob=5.68181818e-013	name=null
mask=0xff280030	sig=0x47280030	prob=5.68181818e-013	name=null
mask=0xff080014	sig=0x47080014	prob=1.13636364e-012	name=null
mask=0xff080030	sig=0x47080030	prob=1.13636364e-012	name=null
mask=0xfe620014	sig=0x46620014	prob=5.68181818e-013	name=null
mask=0xff240014	sig=0x47240014	prob=5.68181818e-013	name=null
mask=0xfe420014	sig=0x46420014	prob=1.13636364e-012	name=null
mask=0xfe420030	sig=0x46420030	prob=1.13636364e-012	name=null
mask=0xfe640014	sig=0x46640014	prob=5.68181818e-013	name=null
mask=0xff040030	sig=0x47040030	prob=1.13636364e-012	name=null
mask=0xfe880030	sig=0x46880030	prob=1.13636364e-012	name=null
mask=0xff020014	sig=0x47020014	prob=5.68181818e-013	name=null
mask=0xff020030	sig=0x47020030	prob=5.68181818e-013	name=null
mask=0xfe48002c	sig=0x4648002c	prob=1.13636364e-012	name=null
mask=0xff440030	sig=0x47440030	prob=5.68181818e-013	name=null
mask=0xfe440014	sig=0x46440014	prob=1.13636364e-012	name=null
mask=0xfe440030	sig=0x46440030	prob=1.13636364e-012	name=null
mask=0xfe680014	sig=0x46680014	prob=5.68181818e-013	name=null
mask=0xfe680030	sig=0x46680030	prob=5.68181818e-013	name=null
mask=0xff480014	sig=0x47480014	prob=5.68181818e-013	name=null
mask=0xff480030	sig=0x47480030	prob=5.68181818e-013	name=null
mask=0xfe480014	sig=0x46480014	prob=1.13636364e-012	name=null
mask=0xfe640030	sig=0x46640030	prob=5.68181818e-013	name=null
mask=0xfe200031	sig=0x46200021	prob=1.42045455e-013	name=null
mask=0xfe200032	sig=0x46200022	prob=1.42045455e-013	name=null
mask=0xfe82002c	sig=0x4682002c	prob=1.13636364e-012	name=null
mask=0xfe84002c	sig=0x4684002c	prob=1.13636364e-012	name=null
mask=0xfe88002c	sig=0x4688002c	prob=1.13636364e-012	name=null
mask=0xff02002c	sig=0x4702002c	prob=5.68181818e-013	name=null
mask=0xfe480030	sig=0x46480030	prob=1.13636364e-012	name=null
mask=0xfe64000e	sig=0x4664000e	prob=5.68181818e-013	name=null
mask=0xff08002c	sig=0x4708002c	prob=1.13636364e-012	name=null
mask=0xfea2002c	sig=0x46a2002c	prob=5.68181818e-013	name=null
mask=0xfea4002c	sig=0x46a4002c	prob=5.68181818e-013	name=null
mask=0xff84002c	sig=0x4784002c	prob=5.68181818e-013	name=null
mask=0xfea8002c	sig=0x46a8002c	prob=5.68181818e-013	name=null
mask=0xff88002c	sig=0x4788002c	prob=5.68181818e-013	name=null
mask=0xff24002c	sig=0x4724002c	prob=5.68181818e-013	name=null
mask=0xff04002c	sig=0x4704002c	prob=1.13636364e-012	name=null
mask=0xff28002c	sig=0x4728002c	prob=5.68181818e-013	name=null
mask=0xff44000e	sig=0x4744000e	prob=5.68181818e-013	name=null
mask=0xfe42002c	sig=0x4642002c	prob=1.13636364e-012	name=null
mask=0xfe64002c	sig=0x4664002c	prob=5.68181818e-013	name=null
mask=0xff44002c	sig=0x4744002c	prob=5.68181818e-013	name=null
mask=0xfe44002c	sig=0x4644002c	prob=1.13636364e-012	name=null
mask=0xfe68002c	sig=0x4668002c	prob=5.68181818e-013	name=null
mask=0xff48002c	sig=0x4748002c	prob=5.68181818e-013	name=null
mask=0xfe82000e	sig=0x4682000e	prob=1.13636364e-012	name=null
mask=0xfe62002c	sig=0x4662002c	prob=5.68181818e-013	name=null
mask=0xff88000e	sig=0x4788000e	prob=5.68181818e-013	name=null
mask=0xfe84000e	sig=0x4684000e	prob=1.13636364e-012	name=null
mask=0xfe88000e	sig=0x4688000e	prob=1.13636364e-012	name=null
mask=0xff02000e	sig=0x4702000e	prob=5.68181818e-013	name=null
mask=0xfe42000e	sig=0x4642000e	prob=1.13636364e-012	name=null
mask=0xfea2000e	sig=0x46a2000e	prob=5.68181818e-013	name=null
mask=0xfea4000e	sig=0x46a4000e	prob=5.68181818e-013	name=null
mask=0xff84000e	sig=0x4784000e	prob=5.68181818e-013	name=null
mask=0xfea8000e	sig=0x46a8000e	prob=5.68181818e-013	name=null
mask=0xfe24001e	sig=0x4624000e	prob=5.68181818e-013	name=null
mask=0xff24000e	sig=0x4724000e	prob=5.68181818e-013	name=null
mask=0xff04000e	sig=0x4704000e	prob=1.13636364e-012	name=null
mask=0xff28000e	sig=0x4728000e	prob=5.68181818e-013	name=null
mask=0xff08000e	sig=0x4708000e	prob=1.13636364e-012	name=null
mask=0xfe62000e	sig=0x4662000e	prob=5.68181818e-013	name=null
mask=0xfe800008	sig=0x46800008	prob=2.84090909e-013	name=null
mask=0xfe800010	sig=0x46800010	prob=2.84090909e-013	name=null
mask=0xfe800020	sig=0x46800000	prob=2.84090909e-013	name=null
mask=0xfe24003a	sig=0x46240028	prob=5.68181818e-013	name=null
mask=0xfe44000e	sig=0x4644000e	prob=1.13636364e-012	name=null
mask=0xfe68000e	sig=0x4668000e	prob=5.68181818e-013	name=null
mask=0xff48000e	sig=0x4748000e	prob=5.68181818e-013	name=null
mask=0xfe48000e	sig=0x4648000e	prob=1.13636364e-012	name=null
mask=0xfe82002f	sig=0x46820005	prob=1.13636364e-012	name=null
mask=0xfe84002f	sig=0x46840005	prob=1.13636364e-012	name=null
mask=0xfe88002f	sig=0x46880005	prob=1.13636364e-012	name=null
mask=0xff440014	sig=0x47440014	prob=5.68181818e-013	name=null
mask=0xfe000032	sig=0x46000022	prob=2.84090909e-013	name=null
mask=0xfe24003c	sig=0x4624002c	prob=5.68181818e-013	name=null
mask=0xfe28001e	sig=0x4628000e	prob=5.68181818e-013	name=null
mask=0xfe28003a	sig=0x46280028	prob=5.68181818e-013	name=null
mask=0xfe28003c	sig=0x4628002c	prob=5.68181818e-013	name=null
mask=0xfe04001e	sig=0x4604000e	prob=1.13636364e-012	name=null
mask=0xfe04003a	sig=0x46040028	prob=1.13636364e-012	name=null
mask=0xfe04003c	sig=0x4604002c	prob=1.13636364e-012	name=null
mask=0xfe08003a	sig=0x46080028	prob=1.13636364e-012	name=null
mask=0xfe02003a	sig=0x46020028	prob=1.13636364e-012	name=null
mask=0xfea4002a	sig=0x46a40028	prob=5.68181818e-013	name=null
mask=0xff84002a	sig=0x47840028	prob=5.68181818e-013	name=null
mask=0xfea8002a	sig=0x46a80028	prob=5.68181818e-013	name=null
mask=0xff02002a	sig=0x47020028	prob=5.68181818e-013	name=null
mask=0xfe220027	sig=0x46220004	prob=1.13636364e-012	name=null
mask=0xfe84002a	sig=0x46840028	prob=1.13636364e-012	name=null
mask=0xfe82002a	sig=0x46820028	prob=1.13636364e-012	name=null
mask=0xfe02003c	sig=0x4602002c	prob=1.13636364e-012	name=null
mask=0xfea2002a	sig=0x46a20028	prob=5.68181818e-013	name=null
mask=0xfe02001e	sig=0x4602000e	prob=1.13636364e-012	name=null
mask=0xfe22003c	sig=0x4622002c	prob=5.68181818e-013	name=null
mask=0xfe22003a	sig=0x46220028	prob=5.68181818e-013	name=null
mask=0xfe22001e	sig=0x4622000e	prob=5.68181818e-013	name=null
mask=0xfe08003c	sig=0x4608002c	prob=1.13636364e-012	name=null
mask=0xff88002a	sig=0x47880028	prob=5.68181818e-013	name=null
mask=0xff24002a	sig=0x47240028	prob=5.68181818e-013	name=null
mask=0xfe88002a	sig=0x46880028	prob=1.13636364e-012	name=null
mask=0xfe44002a	sig=0x46440028	prob=1.13636364e-012	name=null
mask=0xfea80035	sig=0x46080020	prob=2.27272727e-012	name=null
mask=0xff04002a	sig=0x47040028	prob=1.13636364e-012	name=null
mask=0xff28002a	sig=0x47280028	prob=5.68181818e-013	name=null
mask=0xff08002a	sig=0x47080028	prob=1.13636364e-012	name=null
mask=0xfe62002a	sig=0x46620028	prob=5.68181818e-013	name=null
mask=0xfe42002a	sig=0x46420028	prob=1.13636364e-012	name=null
mask=0xfe64002a	sig=0x46640028	prob=5.68181818e-013	name=null
mask=0xff44002a	sig=0x47440028	prob=5.68181818e-013	name=null
mask=0xfe62002f	sig=0x46620005	prob=5.68181818e-013	name=null
mask=0xfe68002a	sig=0x46680028	prob=5.68181818e-013	name=null
mask=0xff48002a	sig=0x47480028	prob=5.68181818e-013	name=null
mask=0xfe82003b	sig=0x46820001	prob=1.13636364e-012	name=null
mask=0xfe84003b	sig=0x46840001	prob=1.13636364e-012	name=null
mask=0xfe88003b	sig=0x46880001	prob=1.13636364e-012	name=null
mask=0xff02002f	sig=0x47020005	prob=5.68181818e-013	name=null
mask=0xff02003b	sig=0x47020001	prob=5.68181818e-013	name=null
mask=0xfe48002a	sig=0x46480028	prob=1.13636364e-012	name=null
mask=0xff88002f	sig=0x47880005	prob=5.68181818e-013	name=null
mask=0xfea2002f	sig=0x46a20005	prob=5.68181818e-013	name=null
mask=0xfea2003b	sig=0x46a20001	prob=5.68181818e-013	name=null
mask=0xfea4002f	sig=0x46a40005	prob=5.68181818e-013	name=null
mask=0xfea4003b	sig=0x46a40001	prob=5.68181818e-013	name=null
mask=0xff84002f	sig=0x47840005	prob=5.68181818e-013	name=null
mask=0xff84003b	sig=0x47840001	prob=5.68181818e-013	name=null
mask=0xfea8002f	sig=0x46a80005	prob=5.68181818e-013	name=null
mask=0xff08003b	sig=0x47080001	prob=1.13636364e-012	name=null
mask=0xfe68002f	sig=0x46680005	prob=5.68181818e-013	name=null
mask=0xff88003b	sig=0x47880001	prob=5.68181818e-013	name=null
mask=0xff24002f	sig=0x47240005	prob=5.68181818e-013	name=null
mask=0xff24003b	sig=0x47240001	prob=5.68181818e-013	name=null
mask=0xff04002f	sig=0x47040005	prob=1.13636364e-012	name=null
mask=0xff04003b	sig=0x47040001	prob=1.13636364e-012	name=null
mask=0xff28002f	sig=0x47280005	prob=5.68181818e-013	name=null
mask=0xff28003b	sig=0x47280001	prob=5.68181818e-013	name=null
mask=0xfea8003b	sig=0x46a80001	prob=5.68181818e-013	name=null
mask=0xfe44003b	sig=0x46440001	prob=1.13636364e-012	name=null
mask=0xfe62003b	sig=0x46620001	prob=5.68181818e-013	name=null
mask=0xfe42002f	sig=0x46420005	prob=1.13636364e-012	name=null
mask=0xfe42003b	sig=0x46420001	prob=1.13636364e-012	name=null
mask=0xfe64002f	sig=0x46640005	prob=5.68181818e-013	name=null
mask=0xfe64003b	sig=0x46640001	prob=5.68181818e-013	name=null
mask=0xff44002f	sig=0x47440005	prob=5.68181818e-013	name=null
mask=0xff44003b	sig=0x47440001	prob=5.68181818e-013	name=null
mask=0xfe44002f	sig=0x46440005	prob=1.13636364e-012	name=null
mask=0xfe820020	sig=0x46820000	prob=2.27272727e-012	name=null
mask=0xff08002f	sig=0x47080005	prob=1.13636364e-012	name=null
mask=0xfe68003b	sig=0x46680001	prob=5.68181818e-013	name=null
mask=0xff48002f	sig=0x47480005	prob=5.68181818e-013	name=null
mask=0xff48003b	sig=0x47480001	prob=5.68181818e-013	name=null
mask=0xfe48002f	sig=0x46480005	prob=1.13636364e-012	name=null
mask=0xfe48003b	sig=0x46480001	prob=1.13636364e-012	name=null
mask=0xfe000027	sig=0x46000004	prob=2.84090909e-013	name=null
mask=0xff020000	sig=0x47020000	prob=1.13636364e-012	name=null
mask=0xfe080030	sig=0x46080010	prob=2.27272727e-012	name=null
mask=0xff040000	sig=0x47040000	prob=2.27272727e-012	name=null
mask=0xff280000	sig=0x47280000	prob=1.13636364e-012	name=null
mask=0xff080000	sig=0x47080000	prob=2.27272727e-012	name=null
mask=0xfe040018	sig=0x46040008	prob=2.27272727e-012	name=null
mask=0xfe080018	sig=0x46080008	prob=2.27272727e-012	name=null
mask=0xfe040028	sig=0x46040008	prob=2.27272727e-012	name=null
mask=0xfe080028	sig=0x46080008	prob=2.27272727e-012	name=null
mask=0xfe040030	sig=0x46040010	prob=2.27272727e-012	name=null
mask=0xff240000	sig=0x47240000	prob=1.13636364e-012	name=null
mask=0xfe620000	sig=0x46620000	prob=1.13636364e-012	name=null
mask=0xff880000	sig=0x47880000	prob=1.13636364e-012	name=null
mask=0xfe28002e	sig=0x4628000e	prob=5.68181818e-013	name=null
mask=0xfe28003a	sig=0x4628000a	prob=5.68181818e-013	name=null
mask=0xfe04002e	sig=0x4604000e	prob=1.13636364e-012	name=null
mask=0xfe04003a	sig=0x4604000a	prob=1.13636364e-012	name=null
mask=0xfe08002e	sig=0x4608000e	prob=1.13636364e-012	name=null
mask=0xfe08003a	sig=0x4608000a	prob=1.13636364e-012	name=null
mask=0xfe280018	sig=0x46280008	prob=1.13636364e-012	name=null
mask=0xfe820010	sig=0x46820010	prob=2.27272727e-012	name=null
mask=0xfe840002	sig=0x46840002	prob=2.27272727e-012	name=null
mask=0xfe840004	sig=0x46840004	prob=2.27272727e-012	name=null
mask=0xfe840008	sig=0x46840008	prob=2.27272727e-012	name=null
mask=0xfe840010	sig=0x46840010	prob=2.27272727e-012	name=null
mask=0xfe840020	sig=0x46840000	prob=2.27272727e-012	name=null
mask=0xfe220030	sig=0x46220010	prob=1.13636364e-012	name=null
mask=0xfe240018	sig=0x46240008	prob=1.13636364e-012	name=null
mask=0xfe020027	sig=0x46020004	prob=2.27272727e-012	name=null
mask=0xfe280028	sig=0x46280008	prob=1.13636364e-012	name=null
mask=0xfe240030	sig=0x46240010	prob=1.13636364e-012	name=null
mask=0xfe280030	sig=0x46280010	prob=1.13636364e-012	name=null
mask=0xfea20000	sig=0x46a20000	prob=1.13636364e-012	name=null
mask=0xfea40000	sig=0x46a40000	prob=1.13636364e-012	name=null
mask=0xff840000	sig=0x47840000	prob=1.13636364e-012	name=null
mask=0xfea80000	sig=0x46a80000	prob=1.13636364e-012	name=null
mask=0xfe420000	sig=0x46420000	prob=2.27272727e-012	name=null
mask=0xfe220031	sig=0x46220021	prob=1.13636364e-012	name=null
mask=0xfe080032	sig=0x46080022	prob=2.27272727e-012	name=null
mask=0xfe040035	sig=0x46040025	prob=2.27272727e-012	name=null
mask=0xfe080035	sig=0x46080025	prob=2.27272727e-012	name=null
mask=0xfe020032	sig=0x46020022	prob=2.27272727e-012	name=null
mask=0xfe020035	sig=0x46020025	prob=2.27272727e-012	name=null
mask=0xfea40035	sig=0x46040020	prob=2.27272727e-012	name=null
mask=0xfe24003a	sig=0x4624000a	prob=5.68181818e-013	name=null
mask=0xfea20035	sig=0x46020020	prob=2.27272727e-012	name=null
mask=0xfe22003a	sig=0x4622000a	prob=5.68181818e-013	name=null
mask=0xfe240031	sig=0x46240021	prob=1.13636364e-012	name=null
mask=0xfe280031	sig=0x46280021	prob=1.13636364e-012	name=null
mask=0xfe240032	sig=0x46240022	prob=1.13636364e-012	name=null
mask=0xfe280032	sig=0x46280022	prob=1.13636364e-012	name=null
mask=0xfe220032	sig=0x46220022	prob=1.13636364e-012	name=null
mask=0xfe040027	sig=0x46040004	prob=2.27272727e-012	name=null
mask=0xfe080027	sig=0x46080004	prob=2.27272727e-012	name=null
mask=0xfe24002e	sig=0x4624000e	prob=5.68181818e-013	name=null
mask=0xfe880020	sig=0x46880000	prob=2.27272727e-012	name=null
mask=0xfe22002e	sig=0x4622000e	prob=5.68181818e-013	name=null
mask=0xfe02002e	sig=0x4602000e	prob=1.13636364e-012	name=null
mask=0xfe02003a	sig=0x4602000a	prob=1.13636364e-012	name=null
mask=0xfe880002	sig=0x46880002	prob=2.27272727e-012	name=null
mask=0xff84003a	sig=0x4784000a	prob=5.68181818e-013	name=null
mask=0xff88003a	sig=0x4788000a	prob=5.68181818e-013	name=null
mask=0xff44003a	sig=0x4744000a	prob=5.68181818e-013	name=null
mask=0xff48003a	sig=0x4748000a	prob=5.68181818e-013	name=null
mask=0xfe200027	sig=0x46200004	prob=1.42045455e-013	name=null
mask=0xfe240027	sig=0x46240004	prob=1.13636364e-012	name=null
mask=0xfe280027	sig=0x46280004	prob=1.13636364e-012	name=null
mask=0xff02003a	sig=0x4702000a	prob=5.68181818e-013	name=null
mask=0xfe880004	sig=0x46880004	prob=2.27272727e-012	name=null
mask=0xfe880008	sig=0x46880008	prob=2.27272727e-012	name=null
mask=0xfe880010	sig=0x46880010	prob=2.27272727e-012	name=null
mask=0xfe040032	sig=0x46040022	prob=2.27272727e-012	name=null
mask=0xffe0003f	sig=0x46200001	prob=0.0454545454	name=sub_d
mask=0xffe0003f	sig=0x46000001	prob=0.0454545454	name=sub_s
-------------------------------------------------------------------
Table Mask=0x00000007*/

_TABLE_DEF_BEGIN(table_5, 8)
  _STUB_NAME(stub_5_0),
  _STUB_NAME(stub_5_1),
  _STUB_NAME(stub_5_2),
  _STUB_NAME(stub_5_3),
  _STUB_NAME(stub_5_4),
  _STUB_NAME(stub_5_5),
  _STUB_NAME(stub_5_6),
  _STUB_NAME(stub_5_7),
_TABLE_DEF_END

/*
Table begin: index=0 size=21
Mask=0x000e0038	DMask=0xffe00007	CMask=0x00000000	Sig=0x46000010
Prob=0.529411765	Entropy=0.503258336	HTreeHeight=1.11111111
-------------------------------------------------------------------
mask=0xffe0003f	sig=0x46000000	prob=0.888888889	name=add_s
mask=0xffe00037	sig=0x46000030	prob=0.111111111	name=c_cond_s
mask=0xffe4001f	sig=0x46040008	prob=3.47222222e-013	name=null
mask=0xffe40037	sig=0x46040020	prob=5.55555556e-012	name=null
mask=0xffe20037	sig=0x46020020	prob=5.55555556e-012	name=null
mask=0xffe8001f	sig=0x46080008	prob=3.47222222e-013	name=null
mask=0xffe4002f	sig=0x46040008	prob=3.47222222e-013	name=null
mask=0xffe8002f	sig=0x46080008	prob=3.47222222e-013	name=null
mask=0xffe40037	sig=0x46040010	prob=3.47222222e-013	name=null
mask=0xffe80037	sig=0x46080010	prob=3.47222222e-013	name=null
mask=0xffe80037	sig=0x46080020	prob=5.55555556e-012	name=null
mask=0xffe4003f	sig=0x46040028	prob=3.47222222e-013	name=null
mask=0xffe8003f	sig=0x46080028	prob=3.47222222e-013	name=null
mask=0xffe2001f	sig=0x46020008	prob=3.47222222e-013	name=null
mask=0xffe2002f	sig=0x46020008	prob=3.47222222e-013	name=null
mask=0xffe20037	sig=0x46020010	prob=3.47222222e-013	name=null
mask=0xffe2003f	sig=0x46020028	prob=3.47222222e-013	name=null
mask=0xffe00037	sig=0x46000020	prob=6.94444444e-013	name=null
mask=0xffe0001f	sig=0x46000008	prob=4.34027778e-014	name=null
mask=0xffe0002f	sig=0x46000008	prob=4.34027778e-014	name=null
mask=0xffe00037	sig=0x46000010	prob=4.34027778e-014	name=null
-------------------------------------------------------------------
Table Mask=0x00000038*/

_TABLE_DEF_BEGIN(table_6, 8)
  _FUNC_NAME(add_s),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(c_cond_s),
  _FUNC_NAME(c_cond_s),
_TABLE_DEF_END

/*
Table begin: index=0 size=40
Mask=0x000e0038	DMask=0xffe00007	CMask=0x00000000	Sig=0x46200001
Prob=0.529411765	Entropy=0.503258335	HTreeHeight=1.11111111
-------------------------------------------------------------------
mask=0xffe00037	sig=0x46200031	prob=0.111111111	name=c_cond_d
mask=0xffe2003f	sig=0x46220029	prob=3.47222222e-013	name=null
mask=0xffe20037	sig=0x46220011	prob=3.47222222e-013	name=null
mask=0xffe20037	sig=0x46220011	prob=3.47222222e-013	name=null
mask=0xffe4001f	sig=0x46240009	prob=3.47222222e-013	name=null
mask=0xffe8002f	sig=0x46280009	prob=3.47222222e-013	name=null
mask=0xffe40037	sig=0x46240011	prob=3.47222222e-013	name=null
mask=0xffe80037	sig=0x46280011	prob=3.47222222e-013	name=null
mask=0xffe4003f	sig=0x46240009	prob=1.73611111e-013	name=null
mask=0xffe4003f	sig=0x46240029	prob=1.73611111e-013	name=null
mask=0xffe8003f	sig=0x46280009	prob=1.73611111e-013	name=null
mask=0xffe8003f	sig=0x46280029	prob=1.73611111e-013	name=null
mask=0xffe4002f	sig=0x46240009	prob=3.47222222e-013	name=null
mask=0xffe8002f	sig=0x46280009	prob=3.47222222e-013	name=null
mask=0xffe8001f	sig=0x46280009	prob=3.47222222e-013	name=null
mask=0xffe20037	sig=0x46220021	prob=6.94444444e-013	name=null
mask=0xffe40037	sig=0x46240021	prob=6.94444444e-013	name=null
mask=0xffe80037	sig=0x46280021	prob=6.94444444e-013	name=null
mask=0xffe40037	sig=0x46240011	prob=3.47222222e-013	name=null
mask=0xffe80037	sig=0x46280011	prob=3.47222222e-013	name=null
mask=0xffe4003f	sig=0x46240029	prob=3.47222222e-013	name=null
mask=0xffe0003f	sig=0x46200009	prob=2.17013889e-014	name=null
mask=0xffe0003f	sig=0x46200029	prob=2.17013889e-014	name=null
mask=0xffe0002f	sig=0x46200009	prob=4.34027778e-014	name=null
mask=0xffe00037	sig=0x46200011	prob=4.34027778e-014	name=null
mask=0xffe0001f	sig=0x46200009	prob=4.34027778e-014	name=null
mask=0xffe0002f	sig=0x46200009	prob=4.34027778e-014	name=null
mask=0xffe00037	sig=0x46200011	prob=4.34027778e-014	name=null
mask=0xffe2002f	sig=0x46220009	prob=3.47222222e-013	name=null
mask=0xffe2001f	sig=0x46220009	prob=3.47222222e-013	name=null
mask=0xffe2003f	sig=0x46220009	prob=1.73611111e-013	name=null
mask=0xffe2003f	sig=0x46220029	prob=1.73611111e-013	name=null
mask=0xffe2002f	sig=0x46220009	prob=3.47222222e-013	name=null
mask=0xffe2003f	sig=0x46220029	prob=3.47222222e-013	name=null
mask=0xffe4002f	sig=0x46240009	prob=3.47222222e-013	name=null
mask=0xffe00037	sig=0x46200021	prob=8.68055556e-014	name=null
mask=0xffe8003f	sig=0x46280029	prob=3.47222222e-013	name=null
mask=0xffe4003f	sig=0x46240029	prob=3.47222222e-013	name=null
mask=0xffe8003f	sig=0x46280029	prob=3.47222222e-013	name=null
mask=0xffe0003f	sig=0x46200001	prob=0.888888889	name=sub_d
-------------------------------------------------------------------
Table Mask=0x00000038*/

_TABLE_DEF_BEGIN(table_7, 8)
  _FUNC_NAME(sub_d),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(null),
  _FUNC_NAME(c_cond_d),
  _FUNC_NAME(c_cond_d),
_TABLE_DEF_END


_STUB_ENTRY(stub_0_0)
{
 _TABLE_JUMP(table_1, 0x0000003f, 0);
}

_STUB_ENTRY(stub_0_1)
{
 _TABLE_JUMP(table_2, 0x0000003f, 0);
}

_STUB_ENTRY(stub_0_2)
{
 if _PATTERN_TRUE(0x00010000, 0x00000000) {
   if _PATTERN_TRUE(0x00100000, 0x00000000) {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bltz);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bltzal);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00100000, 0x00000000) {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bgez);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bgezal);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_0_3)
{
 if _PATTERN_TRUE(0x00010000, 0x00000000) {
   if _PATTERN_TRUE(0x00100000, 0x00000000) {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bltz);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bltzal);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00100000, 0x00000000) {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bgez);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x000e0000, 0x00000000) {
       _FUNC_CALL(bgezal);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_0_34)
{
 _TABLE_JUMP(table_3, 0x0000000f, 21);
}

_STUB_ENTRY(stub_0_35)
{
 _TABLE_JUMP(table_5, 0x00000007, 0);
}

_STUB_ENTRY(stub_1_0)
{
 if _PATTERN_TRUE(0x01ffffc0, 0x00000000) {
   _FUNC_CALL(nop);
 } else {
   _FUNC_CALL(sll);
 }
}

_STUB_ENTRY(stub_3_8)
{
 _TABLE_JUMP(table_4, 0x00000003, 16);
}

_STUB_ENTRY(stub_5_0)
{
 if _PATTERN_TRUE(0x00600000, 0x00200000) {
   if _PATTERN_TRUE(0x01800038, 0x00000020) {
     _FUNC_CALL(cvt_s_d);
   } else {
     if _PATTERN_TRUE(0x00000010, 0x00000000) {
       if _PATTERN_TRUE(0x01800008, 0x00000000) {
         _FUNC_CALL(add_d);
       } else {
         _FUNC_CALL(null);
       }
     } else {
       if _PATTERN_TRUE(0x01800020, 0x00000020) {
         _FUNC_CALL(c_cond_d);
       } else {
         _FUNC_CALL(null);
       }
     }
   }
 } else {
   if _PATTERN_TRUE(0x01c00000, 0x00000000) {
     _TABLE_JUMP(table_6, 0x00000007, 3);
   } else {
     if _PATTERN_TRUE(0x01400038, 0x00000020) {
       _FUNC_CALL(cvt_s_w);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_1)
{
 if _PATTERN_TRUE(0x00200020, 0x00000020) {
   if _PATTERN_TRUE(0x01c00018, 0x00000000) {
     _FUNC_CALL(cvt_d_s);
   } else {
     if _PATTERN_TRUE(0x00000018, 0x00000000) {
       if _PATTERN_TRUE(0x01400000, 0x00000000) {
         _FUNC_CALL(cvt_d_w);
       } else {
         _FUNC_CALL(null);
       }
     } else {
       if _PATTERN_TRUE(0x01c00010, 0x00000010) {
         _FUNC_CALL(c_cond_s);
       } else {
         _FUNC_CALL(null);
       }
     }
   }
 } else {
   if _PATTERN_TRUE(0x01e00000, 0x00200000) {
     _TABLE_JUMP(table_7, 0x00000007, 3);
   } else {
     if _PATTERN_TRUE(0x01e00018, 0x00000000) {
       _FUNC_CALL(sub_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_2)
{
 if _PATTERN_TRUE(0x00200000, 0x00000000) {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(mul_s);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(mul_d);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_d);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_3)
{
 if _PATTERN_TRUE(0x00200000, 0x00000000) {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(div_s);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(div_d);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_d);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_4)
{
 if _PATTERN_TRUE(0x00200000, 0x00000000) {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000020) {
       _FUNC_CALL(cvt_w_s);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x01000010, 0x00000010) {
     if _PATTERN_TRUE(0x00c00020, 0x00000020) {
       _FUNC_CALL(c_cond_d);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00028, 0x00000020) {
       _FUNC_CALL(cvt_w_d);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_5)
{
 if _PATTERN_TRUE(0x00200000, 0x00000000) {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(abs_s);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00000030, 0x00000030) {
     if _PATTERN_TRUE(0x01c00000, 0x00000000) {
       _FUNC_CALL(c_cond_d);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00038, 0x00000000) {
       _FUNC_CALL(abs_d);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_6)
{
 if _PATTERN_TRUE(0x00200000, 0x00000000) {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(mov_s);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(mov_d);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_d);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}

_STUB_ENTRY(stub_5_7)
{
 if _PATTERN_TRUE(0x00200000, 0x00000000) {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(neg_s);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_s);
     } else {
       _FUNC_CALL(null);
     }
   }
 } else {
   if _PATTERN_TRUE(0x00000010, 0x00000000) {
     if _PATTERN_TRUE(0x01c00028, 0x00000000) {
       _FUNC_CALL(neg_d);
     } else {
       _FUNC_CALL(null);
     }
   } else {
     if _PATTERN_TRUE(0x01c00020, 0x00000020) {
       _FUNC_CALL(c_cond_d);
     } else {
       _FUNC_CALL(null);
     }
   }
 }
}


_MAIN_DECODE_ENTRY
{
 _TABLE_JUMP(table_0, 0x0000007f, 25);
}
/* End of decoder */
