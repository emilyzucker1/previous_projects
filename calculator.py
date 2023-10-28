def main():

    #gather values from user
    val_1 = float(input("Enter first operand: "))
    val_2 = float(input("Enter second operand: "))

    #display menu
    print("\nCalculator Menu\n" +
          "-" * 15 +
          "\n1. Addition\n" +
          "2. Subtraction\n" +
          "3. Multiplication\n" +
          "4. Division\n")

    #allow user to select a choice
    choice = int(input("Which operation do you want to perform? "))

    #perform operation based on selection
    if choice == 1:
        final_val = val_1 + val_2
    elif choice == 2:
        final_val = val_1 - val_2
    elif choice == 3:
        final_val = val_1 * val_2
    elif choice == 4:
        final_val = val_1 / val_2
    else:
        #invalid choice so relay error message and quit program
        print("\nError: Invalid selection! Terminating program.")
        quit()

    #display final result
    print(f'\nThe result of the operation is {final_val}. Goodbye!')

main()
