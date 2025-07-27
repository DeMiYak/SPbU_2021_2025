#ifndef MATH2_H_INCLUDED
#define MATH2_H_INCLUDED

/** @brief sign x
 *  @param x - a number
 *  @return -1 (x<0), 0 (x=0), +1 (x>0), NaN (x-NaN)
 */
double sign (double x);

double sqrt (double x, double eps);

#endif // MATH2_H_INCLUDED
