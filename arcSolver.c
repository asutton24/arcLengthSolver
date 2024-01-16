#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832
typedef double (*functionPointer)(double, double);

double constant = 1;

double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(y2-y1,2)+pow(x2-x1,2));
}

double arcLength(functionPointer func, double low, double high, int steps, double power){
    double ans = 0;
    double stepSize = (high-low)/steps;
    for (int i = 0; i < steps; i++){
        ans += distance(low+i*stepSize, func(low+i*stepSize, power), low+(i+1)*stepSize, func(low+(i+1)*stepSize, power));
    }
    return ans;
}

double integrate(functionPointer func, double low, double high, int steps, double power){
    double ans = 0;
    double stepSize = (high-low)/steps;
    for (int i = 0; i < steps; i++){
        ans += func(low + stepSize * i, power);
    }
    return ans * stepSize;
}

double derivative(functionPointer func, double point, double power){
    double h = 1e-06;
    return (func(point+h, power)-func(point, power))/(h); 
}

double f(double x, double y){
    return pow((sin(PI * x)),y);
}

double g(double x, double y){
    return f(x, y)/constant;
}

double h(double x, double y){
    return sin(PI);
}
int main(){
    functionPointer g_ptr = &g;
    functionPointer f_ptr = &f;
    printf("Start\n");
    printf("%f, %.17f\n", g(0, .01), sin(PI));
    for (int i = 1; i<=1000000;i++){
        if (i% 1000 == 0){
            constant = integrate(f_ptr, 0, 1, 1000000, 1.0/i);
            printf("n=%d: Arc Length: %.17f Area: %f\n", i, arcLength(g_ptr, 0, 1, 1000000, 1.0/i), integrate(g_ptr, 0, 1, 1000000, 1.0/i));
        }
    }
    return 0;
}