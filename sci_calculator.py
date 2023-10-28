import math

# menu function to display menu and reduce redundancy
def menu(result):
    print(f"\nCurrent Result: {result}\n" +
          "\nCalculator Menu\n" +
          "-" * 15 +
          "\n0. Exit Program\n" +
          "1. Addition\n" +
          "2. Subtraction\n" +
          "3. Multiplication\n" +
          "4. Division\n" +
          "5. Exponentiation\n" +
          "6. Logarithm\n" +
          "7. Display Average")
    choice = int(input("Enter Menu Selection: "))
    return choice

# function to get operands to reduce redundancy in main
def get_ops():

    first = (input("Enter first operand: "))
    second =(input("Enter second operand: "))

    # if else statement to determine if the result of the previous equation should
    # be used in the new equation
    if first == "RESULT":
        if second == "RESULT":
            return result, result
        else:
            second = float(second)
            return result, second
    else:
        first = float(first)
        if second == "RESULT":
            return first, result
        else:
            second = float(second)
            return first, second


# functions to define all equations
def addition(x, y):
    answer = x + y
    return answer


def subtraction(x, y):
    answer = x - y
    return answer


def multiplication(x, y):
    answer = x * y
    return answer


def divide(x, y):
    answer = x / y
    return answer


def exponential(x, y):
    answer = x ** y
    return answer


def logarithm(x, y):
    answer = math.log(y, x)
    return answer


def average(sum_calc, number):
    avg = sum_calc / number
    return avg


def main():

    # initialize variables
    global result
    result = 0.0
    sum_of_calcs = 0.0
    num_of_calcs = 0

    # allow user to select initial choice
    choice = menu(result)

    # start loop
    proceed = True
    while proceed:

        # quit if the user chooses 0
        if choice == 0:
            print("Thanks for using this calculator. Goodbye!")
            quit()

        # perform addition if user chooses 1
        elif choice == 1:
            # set first and second operand variables based on what get_ops(function) returns
            first_op, second_op = get_ops()
            # assign result to what the function returns
            result = addition(first_op, second_op)
            # keep track of the sum of all the calculations
            sum_of_calcs += result
            # keep track of the number of calculations
            num_of_calcs += 1
            # have user select new choice
            choice = menu(result)

        # perform subtraction if user chooses 2
        elif choice == 2:
            first_op, second_op = get_ops()
            result = subtraction(first_op, second_op)
            sum_of_calcs += result
            num_of_calcs += 1
            choice = menu(result)

        # perform multiplication if user chooses 3
        elif choice == 3:
            first_op, second_op = get_ops()
            result = multiplication(first_op, second_op)
            sum_of_calcs += result
            num_of_calcs += 1
            choice = menu(result)

        # perform division if user chooses 4
        elif choice == 4:
            first_op, second_op = get_ops()
            result = divide(first_op, second_op)
            sum_of_calcs += result
            num_of_calcs += 1
            choice = menu(result)

        # perform exponent if user chooses 5
        elif choice == 5:
            first_op, second_op = get_ops()
            result = exponential(first_op, second_op)
            sum_of_calcs += result
            num_of_calcs += 1
            choice = menu(result)

        # perform logarithm if user chooses 6
        elif choice == 6:
            first_op, second_op = get_ops()
            result = logarithm(first_op, second_op)
            sum_of_calcs += result
            num_of_calcs += 1
            choice = menu(result)

        # calculate average of calculations if user chooses 7
        elif choice == 7:

            # if there have been no calculations give error
            if num_of_calcs == 0:
                print('Error: No calculations yet to average!\n')
                choice = int(input("Enter Menu Selection: "))

            # calculate the average and print results
            else:
                avg = average(sum_of_calcs, num_of_calcs)
                print(f"\nSum of calculations: {sum_of_calcs: .2f}\n" +
                    f"Number of calculations: {num_of_calcs}\n" +
                    f"Average of calculations: {avg: .2f}\n")
                choice = int(input("Enter Menu Selection: "))

        # check validity of input
        elif choice < 0 or choice > 7:
            print("\nError: Invalid selection!\n")
            choice = int(input("Enter Menu Selection: "))


main()






