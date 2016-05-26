#!/usr/bin/python
print '<?xml version="1.0" encoding="utf-8"?>'
print '<!DOCTYPE node SYSTEM "DCHinput.dtd">'
print '<!--Database Multiprocessor Markup Language (DMML)-->'
print '<DCH-Tree name="NODES">'
print '<node id="99999" parentId="0"  devType="S" weight="1342"/>'
for i in range(0, 15):
	print '<node id="' + str(20000+i) + '" parentId="' +  str(99999) + '"  devType="L" weight="1342"/>'
	parent = 10000 + i
	print '<node id="' + str(parent) + '" parentId="' + str(20000+i) + '"  devType="S" weight="2147"/>'
	for lId in range (0, 10):
		print '<node id="' +  str(20000+15 + 10 * i + lId) +'" parentId="' + str(parent) +'"  devType="L" weight="2147"/>'
		print '<node id="' + str(30000+120*i + lId) + '" parentId="'+ str(20000+15 + 10 * i + lId) + '"  devType="W" perfomance="378"/>'

	
	
print '</DCH-Tree>'
