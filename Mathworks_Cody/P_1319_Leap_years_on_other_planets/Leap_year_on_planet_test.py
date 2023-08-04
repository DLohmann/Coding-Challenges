import unittest
from math import floor
from math import pow
from Leap_year_on_planet import calculate_leap_years

class TestLeapYear(unittest.TestCase):

    def test_given_approximate_earth_year(self):
        solution = calculate_leap_years(365.2425)
        full_days = floor(365.2425)

        # Check all integers
        for leap_interval in solution:
            self.assertIsInstance(leap_interval, int, msg=f'All leap intervals must be integers, but found {leap_interval} is not of type int.')
        
        # Check all divisible:
        for i in range(len(solution) - 1):
            self.assertTrue(solution[i + 1] % solution[i] == 0,
                            msg=f'Each leap interval must be divisible by previous leap interval, but {solution[i + 1]} is not divisible by {solution[i]}.')

        # Check average number of days
        days_per_year = full_days + sum([pow(-1, i) / float(b) for i, b in enumerate(solution)])
        self.assertAlmostEqual(
            days_per_year,
            365.2425,
            places = 2,
            msg=f'Wrong average number of days per year. Expected 365.24 within 2 decimal places. Returned {days_per_year}.')
        
        # Check expected solution given by Mathworks
        self.assertListEqual(solution, [4, 132, 13068],  msg = f'Expected [4, 132, 13068]. Returned {solution}.')
        # print('calculate_leap_years(365.2425): ', solution)


    def test_earth_year(self):
        solution = calculate_leap_years(365.24217)
        full_days = floor(365.24217)

        # Check all integers
        for leap_interval in solution:
            self.assertIsInstance(leap_interval, int, msg=f'All leap intervals must be integers, but found {leap_interval} is not of type int.')
        
        # Check all divisible:
        for i in range(len(solution) - 1):
            self.assertTrue(solution[i + 1] % solution[i] == 0,
                            msg=f'Each leap interval must be divisible by previous leap interval, but {solution[i + 1]} is not divisible by {solution[i]}.')

        # Check average number of days
        days_per_year = full_days + sum([pow(-1, i) / float(b) for i, b in enumerate(solution)])
        self.assertAlmostEqual(
            days_per_year,
            365.24,
            places = 2,
            msg=f'Wrong average number of days per year. Expected 365.24 within 2 decimal places. Returned {days_per_year}.')
        # print('calculate_leap_years(365.24217): ', solution)

    # According to https://en.wikipedia.org/wiki/Timekeeping_on_Mars
    # Average length of Mars solar day is 88,775.244 seconds.
    # One Martian year is approximately equal to 18 × (37 sols) + 2.59897 sols.
    # Assuming that this means solar (and not sidereal) year, then there should be
    # around 668.59897 martian sols (solar days) in a martian solar year.
    def test_mars_year(self):
        solution = calculate_leap_years(668.59897)
        full_days = floor(668.59897)

        # Check all integers
        for leap_interval in solution:
            self.assertIsInstance(leap_interval, int, msg=f'All leap intervals must be integers, but found {leap_interval} is not of type int.')
        
        # Check all divisible:
        for i in range(len(solution) - 1):
            self.assertTrue(solution[i + 1] % solution[i] == 0,
                            msg=f'Each leap interval must be divisible by previous leap interval, but {solution[i + 1]} is not divisible by {solution[i]}.')

        # Check average number of days
        days_per_year = full_days + sum([pow(-1, i) / float(b) for i, b in enumerate(solution)])
        self.assertAlmostEqual(
            days_per_year,
            668.59897,
            places = 2,
            msg=f'Wrong average number of days per year. Expected 668.59897 within 2 decimal places. Returned {days_per_year}.')
        # print('calculate_leap_years(668.59897): ', solution)
    
if __name__ == '__main__':
    unittest.main()
