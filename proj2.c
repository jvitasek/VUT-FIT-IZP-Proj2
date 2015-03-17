/**
 * @file    proj2.c
 * @author  Jakub Vitasek <me@jvitasek.cz>
 * @date    21.11.2013
 * @brief   1BIT Project 2: Iteration Calculations
 * 
 * The program calculates the interior angles of a common triangle. It also exclusively
 * calculates a square root or an inverse sine of a number. The program achieves that
 * without the need to use the built-in library <math.h>.
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
#define PI 3.14159265358979
double eps = 1e-14; // Precision accounted for in asin and sqrt calculations.
 
double my_sqrt(double x); // Returns the square root of a number.
double my_abs(double a); // Returns the absolute value of a number.
double my_asin(double x); // Returns the arcsin approximation of a number.
double my_asin_extreme(double x); // Returns the arcsin approximation for the extreme values.
double my_acos(double x); // Returns the arccos approximation of a number.
double my_pow(double m, int e); // Returns the result of a number m to the power of e.
double arg_type_and_output(int argc, char *argv[]); // Gets the user-side arguments.
void print_help(void); // Prints out the help message.
double triangle(double ax, double ay, double bx, double by, double cx, double cy); // Returns the three angles.
 
int main(int argc, char *argv[])
{
    if(argc > 8)
    {
        fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nYou've entered too many arguments."
                        "\nTo get the help message, type \"--help\" as the first argument (0 being ./proj2).\n\n");
        return EXIT_FAILURE;
    }
    else if(argc < 2)
    {
        fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nNothing to do."
                        "\nTo get the help message, type \"--help\" as the first argument (0 being ./proj2).\n\n");
        return EXIT_FAILURE;
    }
    arg_type_and_output(argc, argv);
    return 0;
}
 
/* Gets the user-side arguments. */
double arg_type_and_output(int argc, char *argv[])
{
    char *end;
    double converted = 0;   
    /* Printing help. */
    if((strcmp(argv[1], "--help") == 0) || ((argc == 3) && (strcmp(argv[2], "--help") == 0)) || ((argc == 4) && (strcmp(argv[3], "--help") == 0)))
        print_help();
    /* Printing the square root of the number X in '--sqrt X' */
    else if((argc == 3) 
    && (strcmp(argv[1], "--sqrt") == 0) && ((isdigit(*argv[2])) || (argv[2][0] == '-') 
    || (argv[2][0] == '.') || (strcmp(argv[2], "inf") == 0)))
    {
        if(argv[2][0] == '-')
        {
            printf("nan\n");
            return EXIT_FAILURE;
        }
        else
        {
            converted = strtod(argv[2], &end);
            if(*end != '\0')
            {
                fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nWrong type of input.\n\n");
                return EXIT_FAILURE;
            }
            else
            {
                printf("%.10e\n", my_sqrt(converted));
                return EXIT_SUCCESS;
            }
        }
    }
    /* Printing the arcsin of the number X in '--asin X' */
    else if((argc == 3) && (strcmp(argv[1], "--asin") == 0) && ((isdigit(*argv[2])) || (argv[2][0] == '-') || (argv[2][0] == '.')))
    {
        converted = strtod(argv[2], &end);
        if(*end != '\0')
        {
            fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nWrong type of input.\n\n");
            return EXIT_FAILURE;
        }
        else if (converted < -1.0 || converted > 1.0)
        {
            printf("nan\n");
            return EXIT_FAILURE;
        }
        else if(converted < -0.5 || converted > 0.5)
        {
            printf("%.10e\n", my_asin_extreme(converted));
            return EXIT_SUCCESS;
        }
        else
        {
            printf("%.10e\n", my_asin(converted));
            return EXIT_SUCCESS;
        }
    }
    /* Printing the values of the three angles in a triangle */
    else if((argc == 8) && (strcmp(argv[1], "--triangle") == 0)
    && (isdigit(*argv[2]) || (argv[2][0] == '-') || (argv[2][0] == '.')) && (isdigit(*argv[3]) || (argv[3][0] == '-') || (argv[3][0] == '.'))
    && (isdigit(*argv[4]) || (argv[4][0] == '-') || (argv[4][0] == '.')) && (isdigit(*argv[5]) || (argv[5][0] == '-') || (argv[5][0] == '.'))
    && (isdigit(*argv[6]) || (argv[6][0] == '-') || (argv[6][0] == '.')) && (isdigit(*argv[7]) || (argv[7][0] == '-') || (argv[7][0] == '.')))
        triangle(strtod(argv[2], NULL), strtod(argv[3], NULL), strtod(argv[4], NULL), strtod(argv[5], NULL), strtod(argv[6], NULL), strtod(argv[7], NULL));
 
    /* Printing the error message */
    else
    {
        fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nWrong combination of arguments. If you need help, type \"--help\".\n\n");
        return EXIT_FAILURE;
    }
    return 0;
}
 
/* Prints the help message. */
void print_help()
{
    printf("\n\033[32;1m HELP \033[0m\n"
         "\n\"Iteration Calculations\" - proj2.\n"
         "Author: Jakub Vitasek (c) 2013\n"
         "The program calculates interior angles of a common triangle.\n"
         "Program starts upon entering the following prompts:\n"
         "./proj2 --help\n"
         "./proj2 --sqrt X\n"
         "./proj2 --asin X\n"
         "./proj2 --triangle AX AY BX BY CX CY\n\n");
}
 
/* Returns the square root of a number. */
double my_sqrt(double x)
{
    if(x == 0)
        return 0;
    else
    {
        double eps = 1e-11;
        double next_term = x;
        double prev_term = 1;
        next_term = 0.5*(x / prev_term + prev_term);
        double difference = next_term - prev_term;
        while(my_abs(difference) >= (my_abs(next_term)*eps))
        { 
            prev_term = next_term;
            next_term = 0.5*(x / prev_term + prev_term);
            difference = next_term - prev_term;
        }
        return next_term;
    }
}
 
/* Returns the absolute value of a number. */
double my_abs(double a)
{
    if(a < 0)
        return -a;
    else
        return a;
}
 
/* Returns the result of a number m to the power of e. */
double my_pow(double m, int e)
{
    double temp;
    if(e == 0)
       return 1;
    temp = my_pow(m, e/2);       
    if (e%2 == 0)
        return temp*temp;
    else
    {
        if(e > 0)
            return m*temp*temp;
        else
            return (temp*temp)/m;
    }
}
 
/* Returns the three angles. */
double triangle(double ax, double ay, double bx, double by, double cx, double cy)
{
    double c = 0; // AB
    double b = 0; // CA
    double a = 0; // BC
    double alpha = 0; // angle opposing a
    double beta = 0; // angle opposing b
    double gamma = 0; // angle opposing c
     
    // BC = a = √[(cx - bx)^2 + (cy - by)^2]
    a = my_sqrt(my_pow(cx-bx, 2) + my_pow(cy-by, 2));
    // CA = b = √[(cx - ax)^2 + (cy - ay)^2]
    b = my_sqrt(my_pow(cx-ax, 2) + my_pow(cy-ay, 2));
    // AB = c =√[(bx - ax)^2 + (by - ay)^2]
    c = my_sqrt(my_pow(bx-ax, 2) + my_pow(by-ay, 2));
 
    if(((a + b) > c) && ((b + c) > a) && ((c + a) > b))
    {
        // γ = arccos(a^2+b^2-c^2/2ab)
        gamma = my_acos((my_pow(a, 2) + my_pow(b, 2) - my_pow(c, 2))/(2*a*b));
        // β = arccos(a^2+c^2-b^2/2ac)
        beta = my_acos((my_pow(a, 2) + my_pow(c, 2) - my_pow(b, 2))/(2*a*c));
        alpha = PI - gamma - beta;
        printf("%.10e\n%.10e\n%.10e\n", alpha, beta, gamma);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nNot a triangle.\n\n");
        return EXIT_FAILURE;
    }
}
 
/* Returns the arcsin approximation of a number */
double my_asin(double x)
{
    double sum = x;
    if(x < -1.0 || x > 1.0)
    {
        printf("nan\n");
        return EXIT_FAILURE;
    }
  
    double i = 1;
    double a = 2;
    double b = x;

    while(my_abs(b - a) > eps*my_abs(b))
    {
         a = b;
         b *= ((i/(i+1))*((x*x)/(i+2))*i);
         i += 2;
         sum += b;
         eps *= b;
    }
    return sum;
}
 
/* Returns the arcsin approximation of a number for the extreme values. */
double my_asin_extreme(double x)
{
    double sum = x;
    if(x < -0.5)
    {
        sum = -0.5*PI + my_asin(my_sqrt(1-my_pow(x,2)));
        return sum;
    }
    else if(x > 0.5)
    {
        sum = 0.5*PI - my_asin(my_sqrt(1-my_pow(x,2)));
        return sum;
    }
    return 0;
}
 
/* Returns the arccos approximation of a number. */
double my_acos(double x)
{
    double result = 0;
    if(x < -0.5 || x > 0.5)
        result = PI/2 - my_asin_extreme(x);
    else
        result = PI/2 - my_asin(x);
    return result;
}
