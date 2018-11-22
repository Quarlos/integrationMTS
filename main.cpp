//
//  main.cpp
//  integrationMTS
//  Numerical integration using Midpoint, Trapezoidal, and Simpson's rule
//  with prescribed tolerance; starting number of subintervals is 4; doubles
//  until it reaches the desired tolerance (given by the difference of two
//  consecutive evaluations)
//
//  INPUT: limits of integration and tolerance
//
//  Editable: the function to integrate defined below as f_int(x)
//
//  Reference: Dan Stefanica, A Primer for the Maths of Financial Eng., Section 2.5.1
//
//  Created by carlos on 15/11/2018.
//  Copyright © 2018 carlos. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

#include <iomanip> // to use setprecision() so that std output gives me more decimal places


// For different integrands EDIT HERE
double f_int(double x) {
    double f_x = sqrt(x*x*x*x*x)/(1+x*x);
    return f_x;
}


// Midpoint integration rule
double I_numericalM(double a, double b, int n){
    double h = (b-a)/n;
    double I_midpoint=0;
    for(unsigned long i=1; i < n+1; i++) {
        I_midpoint += f_int(a+h*(i-0.5));
    }
    return h*I_midpoint;
}

// Trapezoidal integration rule
double I_numericalT(double a, double b, int n){
    double h = (b-a)/n;
    double I_trap=f_int(a)/2+f_int(b)/2;
    for(unsigned long i=1; i < n; i++) {
            I_trap += f_int(a+i*h);
        }
    return h*I_trap;
}

// Simpson's integration rule
double I_numericalS(double a, double b, int n){
    double h = (b-a)/n;
    double I_simpson=f_int(a)/6+f_int(b)/6;
    for(unsigned long i=1; i < n; i++) {
           I_simpson += f_int(a+i*h)/3;
        }
    for(unsigned long i=1; i < n+1; i++) {
            I_simpson += 2*f_int(a+h*(i-0.5))/3;
         }
    return h*I_simpson;
}



int main() {
    double a, b;
    int n=4;
    double tol;
    double I_old, I_new;
    
    cout << "Limits of integration\n";
    cout << "Left limit a: ";
    cin >> a;
    cout << "Right limit b: ";
    cin >> b;
    cout << "Tolerance: ";
    cin >> tol;

    I_old = I_numericalM(a, b, n);
    I_new = I_numericalM(a, b, 2*n);
    
    while(abs(I_new-I_old) > tol){
        cout << "I_midpoint(" << n << ") = " << setprecision (8) << I_old << endl;
        I_old = I_new;
        n = 2*n;
        I_new = I_numericalM(a, b, 2*n);
    }
    
    cout << "I_midpoint(" << n << ") = " << setprecision (8) << I_old << endl;
    cout << "I_midpoint(" << 2*n << ") = " << setprecision (8) << I_new << endl;
    
    n = 4;
    I_old = I_numericalT(a, b, n);
    I_new = I_numericalT(a, b, 2*n);
    
    while(abs(I_new-I_old) > tol){
        cout << "I_trap(" << n << ") = " << setprecision (8) << I_old << endl;
        I_old = I_new;
        n = 2*n;
        I_new = I_numericalT(a, b, 2*n);
    }
    
    cout << "I_trap(" << n << ") = " << setprecision (8) << I_old << endl;
    cout << "I_trap(" << 2*n << ") = " << setprecision (8) << I_new << endl;
    
    
    n = 4;
    I_old = I_numericalS(a, b, n);
    I_new = I_numericalS(a, b, 2*n);
    
    while(abs(I_new-I_old) > tol){
        cout << "I_simpson(" << n << ") = " << setprecision (8) << I_old << endl;
        I_old = I_new;
        n = 2*n;
        I_new = I_numericalS(a, b, 2*n);
    }
    
    cout << "I_simpson(" << n << ") = " << setprecision (8) << I_old << endl;
    cout << "I_simpson(" << 2*n << ") = " << setprecision (8) << I_new << endl;

    
    return 0;
}
