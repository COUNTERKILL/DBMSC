
print '<node id="99999" parentId="0"  devType="S" weight="0.0001"/>'
for i in range(0, 15):
	print '<node id="' + str(20000+i) + '" parentId="' +  str(99999) + '"  devType="L" weight="0.0007451"/>'
	parent = 10000 + i
	print '<node id="' + str(parent) + '" parentId="' + str(20000+i) + '"  devType="S" weight="0.0001"/>'
	for lId in range (0, 4):
		print '<node id="' +  str(20000+15 + 4 * i + lId) +'" parentId="' + str(parent) +'"  devType="L" weight="0.004657"/>'
		print '<node id="' + str(30000+4*i + lId) + '" parentId="'+ str(20000+15 + 4 * i + lId) + '"  devType="W" perfomance="378"/>'

	
	
