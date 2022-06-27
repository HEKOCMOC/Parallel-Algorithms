program simpson_rule
implicit none
integer:: i ,n;
real::a , b , dx , sum , f , x
real::start_time, end_time

n=10 ** 8 !число шагов
a=1 !левая граница интегрирования
b=20 !правая граница интегрирования
dx=(b-a)/n
sum=f(a)+f(b)

call CPU_TIME(start_time)
do i=1,n-1 ;
x=a+(i*dx)
If (i/2*2.ne.i) then
sum=sum+4*f(x)
else ;
sum=sum+2*f(x)
endif ;
enddo
call CPU_TIME(end_time)
print '("Computation time: " f6.3, "sec")', end_time - start_time

sum=sum*dx/3.0
print*, "for n =",n,"Integral =", sum
end

real function f(x)
implicit none
real::x
f=sin(x*x+2*x) !формула для расчета
end