import turtle
import math

def star(turtle):
    for i in range(5):
        turtle.forward(10)
        turtle.left(144)

def gap(d1,a1,d2,a2):
    x1,y1=toCart(d1,a1)
    x2,y2=toCart(d2,a2)
    return math.sqrt((y2-y1)**2+(x2-x1)**2)

def moveTurtle(t,d1,a1,d2,a2):
    t.penup()
   # t.home()
    inl=10 #----------------------------------------------------> for inlarging
    a1=math.radians(a1)
    a2=math.radians(a2)
    t.goto(math.cos(a1)*d1*inl,math.sin(a1)*d1*inl)
    t.pendown()
    t.goto(math.cos(a2)*d2*inl,math.sin(a2)*d2*inl)

def toCart(radius,angle):
    angle=angle*math.pi/180
    x=radius*math.cos(angle)
    y=radius*math.sin(angle)
    return x,y

def toPolar(x,y):
    radius=math.sqrt(x*x+y*y)
    if x==0 :
        angle= math.pi/2;
        return radius,angle
    angle=math.atan(y/x)
    angle=angle*180/math.pi
    return radius,angle

def targetPos(r,a):
    x,y=toCart(r,a)
    x=x+1
    y=x-10 #-------------------------------------------------target equation
    r,a=toPolar(x,y)
    return r,a

def givetargetpos():
    x=int(input("X : "))
    y=int(input("Y : "))
    r,a=toPolar(x,y)
    return r,a

def chaserPos(d1,a1,d2,a2):
    d= 1.5 #-------------------------------------------------> speed of chaser
    x1,y1=toCart(d1,a1)
    x2,y2=toCart(d2,a2)

    m=(y2-y1)/(x2-x1)

    solx1= x1+(math.sqrt((d**2)/(1+m**2)))
    solx2= x1-(math.sqrt((d**2)/(1+m**2)))

    soly1= m*(solx1-x1)+y1
    soly2= m*(solx2-x1)+y1

    if math.sqrt((solx1 - x2) ** 2 + (soly1 - y2) ** 2) < math.sqrt((solx2 - x2) ** 2 + (soly2 - y2) ** 2):
        X=solx1
        Y=soly1
    else:
        X=solx2
        Y=soly2
    distance,angle =toPolar(X,Y)
    return distance,angle


def predict(d1,a1,t1,d2,a2,t2):
    x1,y1=toCart(d1,a1)
    x2,y2=toCart(d2,a2)

    m=(y2-y1)/(x2-x1)
    v=math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))/(t2-t1)
    d=v #here goes velocity

    A=1+m**2
    B=-2*x2-m*m*2*x1+2*m*(y1-y2)
    C=x2*x2+m*m*x1*x1+(y1-y2)*(y1-y2)-2*m*x1*(y1-y2)-d*d

    solx1=(-B+math.sqrt(B*B-4*A*C))/(2*A)
    solx2=(-B-math.sqrt(B*B-4*A*C))/(2*A)

    soly1=m*(solx1-x1)+y1
    soly2=m*(solx2-x1)+y1

    if math.sqrt((solx1 - x1) ** 2 + (soly1 - y1) ** 2) > math.sqrt((solx2 - x1) ** 2 + (soly2 - y1) ** 2):
        X=solx1
        Y=soly1
    else:
        X=solx2
        Y=soly2
    distance,angle =toPolar(X,Y)
    return distance,angle

dt1=10; at1=-90; t1=0 #-------------------------------------------> target initian possition
dt2,at2=targetPos(dt1,at1); t2=1
dc1=0; ac1=0
dc2=0; ac2=0
target=turtle.Turtle()
chaser=turtle.Turtle()

target.color("red")
chaser.color("green")
target.speed(0.15)
chaser.speed(0.15)

while(gap(dt1,at1,dc1,ac1)>0.1):

    distance,angle=predict(dt1,at1,t1,dt2,at2,t2)
    print("P : ",toCart(distance,angle))
    print("target : ",toCart(dt2,at2))
    dc2,ac2= chaserPos(dc1,ac1,distance,angle)
    print("Chaser : ",toCart(dc2,ac2))
    moveTurtle(target,dt1,at1,dt2,at2)
    star(target)
    if(gap(distance,angle,dc2,ac2)>0.25):
        moveTurtle(chaser,dc1,ac1,dc2,ac2)
        star(chaser)
        dc1,ac1= dc2,ac2
    dt1,at1= dt2,at2
    dt2,at2=targetPos(dt2,at2)
    #dt2,at2=givetargetpos()


turtle.Screen().exitonclick()


