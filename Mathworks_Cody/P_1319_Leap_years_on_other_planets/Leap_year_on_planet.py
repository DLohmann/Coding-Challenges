from math import floor
from math import isclose
from math import modf
from math import inf
from math import nextafter

def calculate_leap_years(x: float, places = 4):
    if (x < 0):
        raise ValueError('x must be positive. Received ' + str(x))
    fraction, full_days = modf(x)
    leaps = []
    approximation = 0.0
    last_leap = 1.0
    sign = 1.0
    while(not isclose(floor(approximation   * (10**places)),   # Compares only 1st places digits after decimal point
                      floor(fraction * (10**places)),
                      abs_tol = nextafter(1.0, -inf))): # nextafter ensures tolerance is < 1 and not including = 1
        # print(f'sign = {sign}, approximation = {approximation}, last_leap = {last_leap}, leaps = {leaps}')

        # Determines how much to leap by (value of leap)
        upper_limit = 1.0 / (sign * (fraction - approximation))

        # Find leap such that leap is largest integer multiple of leap(i-1) such that leap <= upper_limit
        leap = last_leap * floor(upper_limit / last_leap)
        
        approximation += sign / leap
        leaps.append(int(leap))
        last_leap = leap
        sign = -sign
    return leaps

