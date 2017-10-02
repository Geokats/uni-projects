#include <stdio.h>
int main(
)	{int x; for(;;){switch(
x=getchar()) {case EOF: return
 0;   case   ';':   x='\n'; break;
	case '\n': x=
';'; break; case '"'
: x='\''; break; case '\'': x='\"';
break; case     ']': case
'}': x=')'; break; case ')': x  ='}';
		break;
case '[': case '{':x  =  '(';break;
case '(':x=  '{';}putchar(x
);}return 0;}