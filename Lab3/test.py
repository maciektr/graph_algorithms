#using friends script
#https://github.com/Petroniuss/GraphAlgorithmsClass/blob/master/Laboratory/Lab_2/tester.py
from dimacs import readSolution
import os
import lab3_2

def test(func, test_directory ):
    
    tests = [os.fsdecode(file) for file in os.listdir(test_directory)]
    success = 0

    print("-" * 20 + "TESTS" + "-" * 20)

    for test in tests:
        if test =='grid100x100':
            continue
        print("Testing...", test)

        test_path = test_directory + "/" + test
        print(test_path)

        solution = readSolution(test_path)
        actual = func(test_path)

        print("solution {0}, actual {1}".format(solution, actual), end = " ")

        if int(actual) == int(solution):
            print(u"\u2713", end="")
            success = success + 1
        print("\n")

    print("-" * 50)
    print("Finished testing {0}/{1} ".format(success, len(tests)) + u"\u2713")
    print("-" * 50)

test(lab3_2.solve, 'graphs')
