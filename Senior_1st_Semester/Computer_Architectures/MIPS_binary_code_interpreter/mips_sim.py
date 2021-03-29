import sys


def main():
    f = open('/home/swe3005/2021s/proj1/'+sys.argv[1],'rb')
    hex_str = f.read().hex()

    def comple2(num, nbits):
        if (num & (1 << (nbits - 1))) != 0: 
            num = num - (1 << nbits)        
        return num   

    for i in range(0,len(hex_str),8):
        bi = bin(int(hex_str[i:i+8],16))[2:].zfill(32)

        if bi[:6] == '000000' and bi[-6:] == '100000' and bi[-11:-6] == '00000':
            # ADD
            rs = bi[6:11]
            rt = bi[11:16] 
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} add ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '100001' and bi[-11:-6]=='00000':
            # ADDU
            rs = bi[6:11]
            rt = bi[11:16] 
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} addu ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '100100'and bi[-11:-6]=='00000':
            # AND
            rs = bi[6:11]
            rt = bi[11:16] 
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} addu ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '011010' and bi[-16:-6] == '0'*10:
            # DIV
            rs = bi[6:11]
            rt = bi[11:16] 
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} div ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '011011' and bi[-16:-6] == '0'*10:
            # DIVU
            rs = bi[6:11]
            rt = bi[11:16] 
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} divu ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '001001' \
            and bi[11:16] == '00000' and bi[-11:-6] == '00000':
            # JALR
            rs = bi[6:11]
            rd = bi[16:21] 
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} jalr ${int(rd,2)}, ${int(rs,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '001000' \
            and bi[11:-6] == '000000000000000':
            # JR
            rs = bi[6:11]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} jr ${int(rs,2)}')
        
        elif bi[:6] == '000000' and bi[-6:] == '010000' \
            and bi[6:][:10] == '0'*10 and bi[21:26] == '00000':
            # MFHI
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} mfhi ${int(rd,2)}')
        
        elif bi[:6] == '000000' and bi[-6:] == '010010' \
            and bi[6:][:10] == '0'*10 and bi[21:26] == '00000':
            # MFLO
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} mflo ${int(rd,2)}')
        
        elif bi[:6] == '000000' and bi[-6:] == '010001' \
            and bi[-21:-6] == '0'*15:
            # MTHI
            rs = bi[6:11]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} mthi ${int(rs,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '010011' \
            and bi[-21:-6] == '0'*15:
            # MTLO
            rs = bi[6:11]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} mtlo ${int(rs,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '011000' \
            and bi[-16:-6] == '0'*10:
            # MULT
            rs = bi[6:11]
            rt = bi[11:16]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} mult ${int(rs,2)}, ${int(rt,2)}')    

        elif bi[:6] == '000000' and bi[-6:] == '011001' \
            and bi[-16:-6] == '0'*10:
            # MULTU
            rs = bi[6:11]
            rt = bi[11:16]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} multu ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '100111' \
            and bi[-11:-6] == '0'*5:
            # NOR
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} nor ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')
        
        elif bi[:6] == '000000' and bi[-6:] == '100101' \
            and bi[-11:-6] == '0'*5:
            # OR
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} or ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '000000' \
            and bi[6:11] == '0'*5:
            # SLL
            rt = bi[11:16]
            rd = bi[16:21]
            sa = bi[21:26]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sll ${int(rd,2)}, ${int(rt,2)}, {int(sa,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '000100' \
            and bi[-11:-6] == '0'*5:
            # SLLV
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sllv ${int(rd,2)}, ${int(rt,2)}, ${int(rs,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '101010' \
            and bi[-11:-6] == '0'*5:
            # SLT
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} slt ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '101011' \
            and bi[-11:-6] == '0'*5:
            # SLTU
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sltu ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '000011' \
            and bi[6:11] == '0'*5:
            # SRA
            rt = bi[11:16]
            rd = bi[16:21]
            sa = bi[21:26]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sra ${int(rd,2)}, ${int(rt,2)}, {comple2(int(sa,2),len(sa))}')

        elif bi[:6] == '000000' and bi[-6:] == '000111' \
            and bi[-11:-6] == '0'*5:
            # SRAV
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} srav ${int(rd,2)}, ${int(rt,2)}, ${int(rs,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '000011' \
            and bi[6:11] == '0'*5:
            # SRL
            rt = bi[11:16]
            rd = bi[16:21]
            sa = bi[21:26]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} srl ${int(rd,2)}, ${int(rt,2)}, {comple2(int(sa,2),len(sa))}')

        elif bi[:6] == '000000' and bi[-6:] == '000110' \
            and bi[-11:-6] == '0'*5:
            # SRLV
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} srlv ${int(rd,2)}, ${int(rt,2)}, ${int(rs,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '100010' \
            and bi[-11:-6] == '0'*5:
            # SUB
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sub ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '100011' \
            and bi[-11:-6] == '0'*5:
            # SUBU
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} subu ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

        elif bi[:6] == '000000' and bi[-6:] == '001100':
            # SYSCALL
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} syscall')

        elif bi[:6] == '000000' and bi[-6:] == '100110' \
            and bi[-11:-6] == '0'*5:
            # XOR
            rs = bi[6:11]
            rt = bi[11:16]
            rd = bi[16:21]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} xor ${int(rd,2)}, ${int(rs,2)}, ${int(rt,2)}')

    ################ I-TYPE ################
        elif bi[:6] == '001000':
            # ADDI
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} addi ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))}')

        elif bi[:6] == '001001':
            # ADDIU
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} addiu ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))}')
        
        elif bi[:6] == '001100':
            # ANDI
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} addiu ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))}')

        elif bi[:6] == '000100':
            # BEQ
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} beq ${int(rs,2)}, ${int(rt,2)}, {comple2(int(im,2),len(im))}')
        
        elif bi[:6] == '000101':
            # BNE
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} bne ${int(rs,2)}, ${int(rt,2)}, {comple2(int(im,2),len(im))}')

        elif bi[:6] == '100000':
            # LB
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} lb ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')

        elif bi[:6] == '100100':
            # LBU
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} lbu ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')

        elif bi[:6] == '100001':
            # LH
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} lh ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')

        elif bi[:6] == '100101':
            # LHU
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} lhu ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')

        elif bi[:6] == '001111' and bi[6:11] == '0'*5:
            # LUI
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} lui ${int(rt,2)}, {comple2(int(im,2),len(im))}')

        elif bi[:6] == '100011':
            # LW
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} lw ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')

        elif bi[:6] == '001101':
            # ORI
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} ori ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))})')

        elif bi[:6] == '101000':
            # SB
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sb ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')
        
        elif bi[:6] == '001010':
            # SLTI
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} slti ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))}')
        
        elif bi[:6] == '001011':
            # SLTIU
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sltiu ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))}')
        
        elif bi[:6] == '101001':
            # SH
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sh ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')

        elif bi[:6] == '101011':
            # SW
            base = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} sw ${int(rt,2)}, {comple2(int(im,2),len(im))}(${int(base,2)})')


        elif bi[:6] == '001110':
            # XORI
            rs = bi[6:11]
            rt = bi[11:16]
            im = bi[16:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} xori ${int(rt,2)}, ${int(rs,2)}, {comple2(int(im,2),len(im))}')

        elif bi[:6] == '000010':
            # J
            target = bi[6:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} j {int(target,2)}')
        
        elif bi[:6] == '000011':
            # JAL
            target = bi[6:]
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} jal {int(target,2)}')
        
        else:
            print(f'inst {int(i/8)}: {hex_str[i:i+8]} unknown instruction')
    f.close()   

if __name__ == '__main__':
    main()