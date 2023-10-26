from typing import List

ops = {
        '+': int.__add__,
        '-': int.__sub__,
        '*': int.__mul__,
        '/': lambda operand_1, operand_2:
                int.__floordiv__(abs(operand_1), abs(operand_2)) * (1 if ((operand_1 < 0) == (operand_2 < 0)) else -1)
    }

class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        stack = []
        for token in tokens:
            if token.isdigit() or (token[0] == '-' and token[1:].isdigit()):
                stack.append(int(token))
            else:
                operand_2 = stack.pop()
                operand_1 = stack.pop()
                # print(f'({operand_1} {token} {operand_2}), ', end='')
                stack.append(ops[token](operand_1, operand_2))
            # print(f'stack {stack}')
        return stack[0]
        