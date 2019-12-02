#using friends script
#https://github.com/Petroniuss/GraphAlgorithmsClass/blob/master/Laboratory/Lab_2/tester.py
from dimacs import readSolution
import os
import lab1_a

def test(func):
    ex_1_tests_directory = "graphs"
    ex_1_tests = [os.fsdecode(file) for file in os.listdir(ex_1_tests_directory)]
    ex_1_success = 0

    print("-" * 20 + "TESTS" + "-" * 20)

    for test in ex_1_tests:
        print("Testing...", test)

        test_path = ex_1_tests_directory + "/" + test
        print(test_path)

        solution = readSolution(test_path)
        actual = func(test_path)

        print("solution {0}, actual {1}".format(solution, actual), end = " ")

        if int(actual) == int(solution):
            print(u"\u2713", end="")
            ex_1_success = ex_1_success + 1
        print("\n")

    print("-" * 50)
    print("Finished testing {0}/{1} ".format(ex_1_success, len(ex_1_tests)) + u"\u2713")
    print("-" * 50)

test(lab1_a.solve)