# solution for factorial, both inputs
# looks identical to the third judge solution in ipsc, which is given without
# explanation. explanation exists here:
# http://math.stackexchange.com/questions/130352/last-non-zero-digit-of-a-factorial
# python because bigint (and because i have java)

from sys import stdin

a=[1,1,2,6,4,2,2,4,2,8]

def D(n):
	if n<10:return a[n]
	elif n%20/10==1:return 4*D(n/5)*D(n%10)%10
	else:return 6*D(n/5)*D(n%10)%10

while 1:
	s=stdin.readline().split()
	if len(s)==0:break
	n=int(s[0])
	print D(n)
