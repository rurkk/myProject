import main
import unittest

class TestCalculator(unittest.TestCase):

    def test_add(self):
        '''Test case function for addition'''
        self.calc = main.Calculator()
        result = self.calc.add(4, 7)
        expected = 11
        self.assertEqual(result, expected)

    def test_sub(self):
        '''Test case function for subtraction'''
        self.calc = main.Calculator()
        result = self.calc.sub(10, 5)
        expected = 5
        self.assertEqual(result, expected)

    def test_mul(self):
        '''Test case function for multiplication'''
        self.calc = main.Calculator()
        result = self.calc.mul(3, 7)
        expected = 21
        self.assertEqual(result, expected)

    def test_div(self):
        '''Test case function for division'''
        self.calc = main.Calculator()
        result = self.calc.div(10, 2)
        expected = 5
        self.assertEqual(result, expected)