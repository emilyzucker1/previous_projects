

def menu():

    # menu program to help with redundancy in main()

    print("\nDecoding Menu\n" +
          "-" * 13 +
          "\n1. Decode hexadecimal\n" +
          "2. Decode binary\n" +
          "3. Convert binary to hexadecimal\n" +
          "4. Quit\n")
    # gathers user input and returns it to main()
    choice = int(input("Please enter an option: "))
    return choice


def hex_char_decode(digit):

    # decodes a single hex digit and returns its value

    # for digits 1-9, the hex value is just 1-9
    if digit == '0':
        value = 0
        return value
    elif digit == '1':
        value = 1
        return value
    elif digit == '2':
        value = 2
        return value
    elif digit == '3':
        value = 3
        return value
    elif digit == '4':
        value = 4
        return value
    elif digit == '5':
        value = 5
        return value
    elif digit == '6':
        value = 6
        return value
    elif digit == '7':
        value = 7
        return value
    elif digit == '8':
        value = 8
        return value
    elif digit == '9':
        value = 9
        return value
    # for digits 10-15 the hex digit is the corresponding character of the alphabet
    elif digit == 'a' or digit == 'A':
        value = 10
        return value
    elif digit == 'b' or digit == 'B':
        value = 11
        return value
    elif digit == 'c' or digit == 'C':
        value = 12
        return value
    elif digit == 'd' or digit == 'D':
        value = 13
        return value
    elif digit == 'e' or digit == 'E':
        value = 14
        return value
    elif digit == 'f' or digit == 'F':
        value = 15
        return value
    elif digit == 'x':
        value = 0
        return value



def hex_string_decode(hex_string):

    # decodes an entire hexadecimal string and returns its value

    # initialize variables
    total_value = 0
    # the count variable will keep track of how many hex digits are in the
    # string, that way we know what the exponent for the 16 has to be
    count = len(hex_string)

    # for loop to read each digit
    for digit in hex_string:

        # the way that hex works is it takes the value of the hex digit
        # and multiplies it by 16 to the power of something.
        # the exponent is determined by how many digits of hex there are
        # so '0x4321' has 4 digits, which means that the values will be multiplied by
        # 16^0 (because 1 needs to be counted), 16^1, ^2, ^3, but it ascends up the string.
        # so its (4 * 16^3) + (3 * 16^2)....
        value = hex_char_decode(digit) * (16 ** (count - 1))
        if value == 0:
            # the prefixes of 0x have to be ignored, but they contributed to the
            # length of the string, so whenever we see a 0 or x, the count will decrease.
            count -= 1
            continue
        else:
            # then for every following digit, the count decreases so that the 16 gets a lower
            # exponent
            count -= 1
            total_value += value

    return total_value

def binary_string_decode(binary):

    # the int function is built in to convert binary to a value, and you use 2 for the base parameter
    binary_value = int(binary, 2)
    return binary_value


def binary_to_hex(binary):

    # decodes a binary string, re-encodes it as hexadecimal and returns hex string

    # initialize the variables
    binary_string = ''
    hex_string = ''
    count = 0

    # for loop to read the string
    for value in binary:
        # the binary_string variable records each digit read from the string
        binary_string += value
        # the count variable keeps track of how many of those digits we're currently at
        count += 1
        # once the loop has reached 4 digits (which is how manh binary digits makes up a hex code)...
        if count == 4:
            # several if/ elif statements read which 4 binary digits we currently have,
            # and translates it to a hex digit.
            if binary_string == '1111':
                # the hex_string variable records all the translated hex digits.
                hex_string += 'F'
            elif binary_string == '1110':
                hex_string += 'E'
            elif binary_string == '1101':
                hex_string += 'D'
            elif binary_string == '1100':
                hex_string += 'C'
            elif binary_string == '1011':
                hex_string += 'B'
            elif binary_string == '1010':
                hex_string += 'A'
            elif binary_string == '1001':
                hex_string += '9'
            elif binary_string == '1000':
                hex_string += '8'
            elif binary_string == '0111':
                hex_string += '7'
            elif binary_string == '0110':
                hex_string += '6'
            elif binary_string == '0101':
                hex_string += '5'
            elif binary_string == '0100':
                hex_string += '4'
            elif binary_string == '0011':
                hex_string += '3'
            elif binary_string == '0010':
                hex_string += '2'
            elif binary_string == '0001':
                hex_string += '1'
            elif binary_string == '0000':
                hex_string += '0'
            # once we've gathered our hex digit from the 4 recorded binary digits, we need to reset
            # count so we can keep reading binary digits until we reach the next 4.
            count = 0
            # additionally, the binary string has to be reset to empty so that we record only
            # the next 4 digits and are no longer looking at the previous 4 digits.
            binary_string = ''
    # once the whole binary string has been read and recorded, we return the final string of hex digits.
    return hex_string




def main():

    # gather user choice
    choice = menu()

    # loop to keep the menu running
    proceed = True
    while proceed:

        if choice == 1:

            # this choice decodes hex data to a value.
            # first we gather the data.
            data_string = input("Please enter the numeric string to convert: ")
            # then the input is passed through the hex_string_decode method, and assigned to a variable.
            converted_string = hex_string_decode(data_string)
            # then we pass this variable through the print function.
            print(f'Result: {converted_string}')
            # gather user;s next menu choice
            choice = menu()

        elif choice == 2:

            # this choice decodes binary to a value.
            # father user data.
            data_string = input("Please enter the numeric string to convert: ")
            # pass data through binary_string_decode method and assign to variable.
            converted_string = binary_string_decode(data_string)
            # pass variable to print function.
            print(f'Result: {converted_string}')
            # gather user's next choice
            choice = menu()

        elif choice == 3:

            # this choice decodes binary to hex.
            # gather user input
            data_string = input("Please enter the numeric string to convert: ")
            # pass input through binary_to_hex and assign to converted_string
            converted_string = binary_to_hex(data_string)
            # pass variable through print
            print(f'Result: {converted_string}')
            # gather user's next menu choice
            choice = menu()

        elif choice == 4:
            # this choice exits the program
            print("Goodbye!")
            quit()


# use this statement so that unit testing can be performed.
if __name__ == "__main__":

    main()
