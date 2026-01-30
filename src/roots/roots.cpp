#include <iostream>
#include "roots.hpp"

double Epsilon = 0.0000001;

bool bisection(std::function<double(double)> f,double a, double b,double *root)
{
    double Output = 0;
    int IterationCount = 1000;


    if (f(0) == 0)
    {
        *root = 0;
        return true;
    }

    for (int i = 0; i < IterationCount; i++)
    {
        double Midpoint = (a + b)/2;

        // If the midpoint equals Zero
        if (abs(f(Midpoint)) <= Epsilon)
        {
            Output = Midpoint;
            break;
        }

        // Midpoint does not equal zero, choose whether to replace the Left or Right guess.
        if (f(a) * f(Midpoint) < 0)
        {
            b = Midpoint;
        }
        else
        {
            a = Midpoint;
        }
    }

    if (abs(f(Output)) <= Epsilon)
    {
        *root = Output;
        return true;
    }
    else
    {
        return false;
    }
    
}


bool regula_falsi(std::function<double(double)> f,double a, double b,double *root)
{
    int IterationCount = 10000000;

    if (f(a) * f(b) > 0) 
    {
        return false;
    }

    double Midpoint;

    for (int i = 0; i < IterationCount; i++)
    {
        Midpoint = a - ((f(a) * (b-a) )/( f(b) - f(a)));

        // If the midpoint equals Zero
        if (abs(f(Midpoint)) <= Epsilon || (b-a) < Epsilon)
        {
            *root = Midpoint;
            return true;
        }

        // Midpoint does not equal zero, choose whether to replace the Left or Right guess.
        if (f(a) * f(Midpoint) < 0)
        {
            b = Midpoint;
        }
        else
        {
            a = Midpoint;
        }
    }

    return false;
}

bool newton_raphson(std::function<double(double)> f,std::function<double(double)> g,double a, double b, double c,double *root)
{
    int IterationCount = 1000;

    //Initial guess
    if (abs(f(c)) <= Epsilon)
    {
        *root = c;
        return true;
    }

    double PreviousGuess = c;
    double NextGuess;

    //Initial guess failed, now do the iterative process
    for (int i = 0; i < IterationCount; i++)
    {
        NextGuess = PreviousGuess - (f(PreviousGuess)/g(PreviousGuess));

        if (abs(f(NextGuess)) <= Epsilon)
        {
            *root = NextGuess;
            return true;
        }

        PreviousGuess = NextGuess;
    }

    return false;
}

/* Tries to find a zero crossing in f() in the interval [a,b] with
 * the secant method, given a starting guess c.
 * Returns true if a root is found. The crossing is stored in root.
 * Returns false if a crossing could not be found, which can happen
 * if iteration leaves the interval, or derivative is zero.
 */
bool secant(std::function<double(double)> f,double a, double b, double c,double *root)
{
    int IterationCount = 10;

    //Initial guess
    if (abs(f(c)) <= Epsilon)
    {
        *root = c;
        return true;
    }

    double PreviousPreviousGuess = c + 1;
    double PreviousGuess = c;
    double NextGuess;

    //Initial guess failed, now do the iterative process
    for (int i = 0; i < IterationCount; i++)
    {
        NextGuess = PreviousGuess - f(PreviousGuess)*( (PreviousGuess - PreviousPreviousGuess)/(f(PreviousGuess) - f(PreviousPreviousGuess)) );

        if (abs(f(NextGuess)) <= Epsilon)
        {
            *root = NextGuess;
            return true;
        }

        PreviousPreviousGuess = PreviousGuess;
        PreviousGuess = NextGuess;
    }

    return false;
}