from typing import List

class Solution:
    def fizzbuzz(self, n: int):
        if n % 3 != 0 and n % 5 != 0:
            return n
        s = ''
        if n % 3 == 0:
            s = 'fizz'
        
        if n % 5 == 0:
            s = s + 'buzz'
        return s
