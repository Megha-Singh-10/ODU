dj=input('dj');
phij=input('phij');
%tj=input('tj');

if(phij==90)
t(j).x=0;
phij= phij*(pi/180);
else
phij= phij*(pi/180);
t(j).x=dj*cos(phij);
endif
t(j).y=dj*sin(phij);

j++;
