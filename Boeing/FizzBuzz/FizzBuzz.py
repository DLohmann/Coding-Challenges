
def FizzBuzz(n: int) -> str:
    '''
    Write a C program that prints the numbers 1 to 100. For multiples of three print the string “Fizz” instead of the number.
    For multiples of five print the string “Buzz” instead of the number.
    For multiples of both three and five, print the string FizzBuzz instead of the number.
    '''
    for i in range(1, n + 1):
        s = ''
        if i % 3 == 0:
            s = s + 'fizz'
        if i % 5 == 0:
            s = s + 'buzz'
        if i % 3 != 0 and i % 5 != 0:
            s = str(i)
        yield s

if __name__ == '__main__':
    for k in FizzBuzz(100):
        print(k)
