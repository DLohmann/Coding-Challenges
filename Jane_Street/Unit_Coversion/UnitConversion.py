
edges = {
    'm->ft'    : 3.28,
    'ft->in'   : 12,
    'hr->min'  : 60,
    'min->sec' : 60,
    'ft->m'    : 1.0 / 3.28,
    'in->ft'   : 1.0 / 12.0,
    'min->hr'  : 1.0 / 60.0,
    'sec->min' : 1.0 / 60.0
    }

units = {'m', 'ft', 'in', 'hr', 'min', 'sec'}

def convert(amount: float, from_unit: str, to_unit: str):
    if (from_unit == to_unit):
        return amount
    if (f'{from_unit}->{to_unit}' in edges):
        return amount * edges[f'{from_unit}->{to_unit}']
    explored = {from_unit}
    path = [from_unit]
    while (path[-1] != to_unit):
        print(f'path: {path}')

        if all(((f'{path[-1]}->{unit}' not in edges) or (unit in explored)) for unit in units):
            if (path[-1] == from_unit):
                return 'no solution'
            print(f'retreating from {path[-1]}')
            path.pop()
            continue
        print('still unexplored')

        for unit in units:
            if unit in explored:
                continue
            if (f'{path[-1]}->{unit}' in edges):
                print(f'exploring {unit}')
                explored.add(unit)
                path.append(unit)
                break

    print('at end!')
    multiplier = amount
    for i in range(len(path) - 1):
        multiplier *= edges[f'{path[i]}->{path[i + 1]}']
    return multiplier

# print(convert(2.0, 'in', 'in'))
# print(convert(2.0, 'm', 'ft'))
# print(convert(2.0, 'm', 'in'))

import unittest

class TestUnitConversion(unittest.TestCase):
    def test_same_unit(self):
        self.assertEqual(convert(100.0, 'buttload', 'buttload'), 100.0)
    
    def test_direct_conversion(self):
        self.assertEqual(convert(12.0, 'in', 'ft'), 1.0)
    
    def test_indirect_conversion(self):
        self.assertAlmostEqual(convert(1600.0, 'm', 'ft'), 5280.0, delta = 100.0)

    def test_no_conversion(self):
        self.assertEqual(convert(100, 'sec', 'in'), 'no solution')
    
    if __name__ == '__main__':
        unittest.main()
