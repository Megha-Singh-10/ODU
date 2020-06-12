d1=input('d1');
phi=input('phi');
%t1=input('t1');

dt=1;

if(phi==90)
t(1).x=0;
phi= phi*(pi/180);
else
phi= phi*(pi/180);
t(1).x=d1*cos(phi);
endif
t(1).y=d1*sin(phi);

d2=input('d2');
thetan=input('theta');
%t2=input('t2');

if(thetan==90)
t(2).x=0;
thetan=thetan*(pi/180);
else
thetan=thetan*(pi/180);
t(2).x=d2*cos(thetan);
endif
t(2).y=d2*sin(thetan);



j=3;
i=2;
vc=input('vc');
dc=vc*dt;
c(1).x=0;
c(1).y=0;
