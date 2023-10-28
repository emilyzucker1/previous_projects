# import given file for displaying images.
from console_gfx import ConsoleGfx


def image_file():

    # function to get file info from user.

    # initialize test loop.
    test = True
    while test:
        # try/except clause to ensure that user input is actually a string and a real file.
        try:
            # this statement will use the load_file method from the ConsoleGfx class in console_gfx.py
            # and assign the file to a variable to keep track of it and use 'return' to make sure the local
            # variable is accessible in main().
            the_file = ConsoleGfx.load_file(input("Enter name of file to load: "))
            return the_file
        except:
            # if the input is an integer or the name of a file that doesn't exist, this statement will print
            # and the loop will start over until the user inputs valid data.
            print('Sorry, that is not a valid file name. Please try again.')


def menu():

    # function for displaying menu.
    print("\nRLE Menu\n" +
          "-" * 8 +
          "\n0. Exit\n" +
          "1. Load File\n" +
          "2. Load Test Image\n" +
          "3. Read RLE String\n" +
          "4. Read RLE Hex String\n" +
          "5. Read Data Hex String\n" +
          "6. Display Image\n" +
          "7. Display RLE String\n" +
          "8. Display Hex RLE Data\n" +
          "9. Display Hex Flat Data\n")
    # small loop to ensure that the user input is valid.
    # initialize loop variable.
    test = True
    while test:
        # try to gather user input.
        try:
            choice = int(input("Select a Menu Option: "))
            # return the choice if the input is valid.
            return choice
        # if user input is not an integer, the except clause will print an error
        # message and prompt the user to try again.
        except:
            print('That is not a valid option. Please try again.\n')


def color_test():

    # function for displaying the color test.
    print("\nDisplaying Spectrum Image: ")
    # this statement below will call the display_image method from the ConsoleGfx class and will use the
    # test_rainbow attribute also from the ConsoleGfx class. You don't have to make it a print statement
    # because the method itself prints data.
    ConsoleGfx.display_image(ConsoleGfx.test_rainbow)


# method to convert given raw data to a hexadecimal string.
def to_hex_string(data):
    # set the hex_string variable as empty string so that we can add
    # characters to the string.
    hex_string = ''
    # this for loop will read every character in the given data and
    # handle it according to the if/elif statements that follow.
    for num in data:
        # since 0-9 in hexadecimal is just represented as its number,
        # the integer will be added to the hex_string as a string.
        num = int(num)
        if 0 <= num <= 9:
            hex_string += f'{num}'
        # the numbers 10-15 are represented as characters a-f, so they
        # will be converted and added to the string.
        elif num == 10:
            hex_string += 'a'
        elif num == 11:
            hex_string += 'b'
        elif num == 12:
            hex_string += 'c'
        elif num == 13:
            hex_string += 'd'
        elif num == 14:
            hex_string += 'e'
        elif num == 15:
            hex_string += 'f'
    # return the final string.
    return hex_string


# method to determine how many runs of data there are in the raw data
# given.
def count_runs(data):
    # initialize variable. count will track how many runs there are.
    count = 0
    current_num = None
    run_amount = 0
    # for loop to read every number in the given data.
    for num in data:
        # this if statement will determine if the next number in the data
        # is the same as the current number, and if it is, the loop will begin a
        # new iteration and the count variable will not be affected, since there
        # is not a new run of data yet.
        if num == current_num:
            run_amount += 1
            if run_amount == 16:
                count += 1
                run_amount = 0
            continue
        # if the next number in the data is unique, the count variable increases
        # (because there is another run starting) and the current_num variable gets
        # set to the number so that in the next iteration of the loop, the first if
        # statement will be able to detect if the next number is unique or not.
        elif 0 <= num <= 15:
            count += 1
            current_num = num
    # return the final number of runs of data.
    return count


# method to generate RLE representation of given raw data.
def encode_rle(data):
    # initialize variables. rle_list will contain the number of instances
    # of a hex digit (unique_count) and then the digit itself (current_num),
    # for however many digits there are.
    rle_list = []
    unique_count = 0
    # current_num is set to -1 because it needs to be a number that is not 0-15
    # so that the loop doesn't think the initialized variable is a part of the raw
    # data.
    current_num = -1
    # nested method to make the rest of the method a little simpler that updates
    # the rle_list.

    def list_append(hex_count, hex_num):
        rle_list.append(hex_count)
        rle_list.append(hex_num)

    # for loop to read every number in the given data
    for num in data:
        # this if statement keeps track of how many times a unique hexadecimal
        # repeats in a run.
        if num == current_num:
            unique_count += 1
            if unique_count == 15:
                list_append(unique_count, current_num)
                unique_count = 0
                continue
            # if there was another occurrence of the current number, then the loop
            # must reiterate and not proceed to the next if statements.
            continue
        # if the number being read is unique AND not the initialized variable, then the
        # program updates the rle_list to give us the number of times the past decimal
        # was repeated in its run, and the number itself.
        if num != current_num and current_num != -1:
            list_append(unique_count, current_num)
            # unique_count is reinitialized so that it can start counting the
            # new number's amount of instances.
            unique_count = 0
        # if the loop has made it to this statement then the number being read is unique.
        if 0 <= num <= 15:
            # the current_num variable is set to the number being read so that in the
            # next loop, the program will know whether the next number being read
            # is unique (new run), or if it is the same number (same run)
            current_num = num
            unique_count += 1
    # this statement updates the list once the loop is done reading from the raw data,
    # which allows the last unique run to be added.
    list_append(unique_count, current_num)
    # return the final list.
    return rle_list


# returns decompressed size of the RLE data string.
def get_decoded_length(data):

    # initialize variables. rle_data_length keeps track of the length of the string
    rle_data_length = 0
    # for loop to read data. the enumerate() function allows us to store 'index' as the index
    # of the string and num as the value of the character at that index.
    for index, num in enumerate(data):
        # if index % 2 == 0 or index == 0, then the index being read is either the first item in data
        # or is an even index, which means that the value at that index is indicating the number of
        # instances of the hex color code that follows.
        if index % 2 == 0 or index == 0:
            # if this index is an instance indicator, then its value is added to rle_data_length,
            # which is recording the sum of instances of each value.
            rle_data_length += num
        else:
            # if the index is odd, then it is the hex color code, and does not need to be
            # recorded for this function, so the loop is permitted to continue.
            continue
    # return final data length.
    return rle_data_length


# returns the decompressed data set from RLE encoded data.
def decode_rle(data):

    # initialize variables. the empty decoded_data list will store the decoded data.
    decoded_data = []
    # this following statement just ensures that num_instances is defined before the
    # else-clause on line 226.
    num_instances = None
    # for loop to read data. the enumerate() function allows us to store 'index' as the index
    # of the string and num as the value of the character at that index.
    for index, num in enumerate(data):
        # if index == 0 or index % 2 == 0, then the index being read is either the first value in the list or
        # is even and holds a value that indicates the instances of a hex color code that follows. if this is
        # true and the item records the number of instances...
        if index % 2 == 0 or index == 0:
            # it will be stored as this variable
            num_instances = int(num)
        else:
            # if the else clause is executed it is because the loop is on an odd
            # item, which is a hex color code. Therefore, the num is set to the variable
            # encoded_num to keep track of it.
            encoded_num = num
            # then, a nested for loop is used so that the encoded_num can be appended
            # to the decoded_data list as many times as there are instances (num_instances).
            for append in range(num_instances):
                decoded_data.append(encoded_num)
    # return the final list of decoded data.
    return decoded_data


# translates a string in hexadecimal to RLE
def string_to_data(data):

    # initialize variable. encoded_rle_list keeps track of the decoded hexadecimal to RLE values.
    encoded_rle_list = []
    # for loop to read data. the enumerate() function allows us to store 'index' as the index
    # of the string and num as the value of the character at that index.
    for index, num in enumerate(data):
        # test that the character is a digit, it's a boolean method so 'digit' will either be True or False.
        digit = num.isdigit()
        # if index % 2 == 0 or index == 0, then the index being read is either the first in the list or an even
        # index, which means that it is the indicator for the number of instances of the hex color code.
        # if it is also a digit (digit == True), then it will be added straight to the RLE list, and if it isn't
        # a digit (digit == False), the else-clause will translate it.
        if (index % 2 == 0 or index == 0) and digit:
            # here, the number is assigned to num_instances to make more clear that the hex code value
            # that is added to the list is the number of instances of the hex color code that follows.
            num_instances = num
            hex_code = int(num_instances)
        else:
            # translates the hex color code or hex instance indicator to a value.
            if num == 'f' or num == 'F':
                hex_code = 15
            elif num == 'e' or num == 'E':
                hex_code = 14
            elif num == 'd' or num == 'D':
                hex_code = 13
            elif num == 'c' or num == 'C':
                hex_code = 12
            elif num == 'b' or num == 'B':
                hex_code = 11
            elif num == 'a' or num == 'A':
                hex_code = 10
            else:
                hex_code = int(num)
        # at the end of every loop, the hex_code that belongs to the read value will be appended to the list.
        encoded_rle_list.append(hex_code)
    # return list.
    return encoded_rle_list


# method to translate RLE data into a human-readable representation.
def to_rle_string(rle_data):
    # initialize variables. rle_string will hold every 2 items in the data list
    # given, and rle_list holds every instance of rle_string.
    rle_string = ''
    rle_list = []
    # loop to read the data.
    for index, num in enumerate(rle_data):
        # if the index is the first in the list, or any even index, then this
        # number will be representing the run length of the hex code that comes
        # after it.
        if index % 2 == 0 or index == 0:
            # therefore, the rle_string gets this number added to it because
            # it is only the run length of the following hex code.
            rle_string += f'{num}'
        # if the index of the number is odd, then it is a hex code that
        # needs to be encoded.
        else:
            # these blocks will encode the hex value and add it to the rle_string.
            num = int(num)
            if 9 >= num >= 0:
                rle_string += f'{num}'
            elif num == 10:
                rle_string += 'a'
            elif num == 11:
                rle_string += 'b'
            elif num == 12:
                rle_string += 'c'
            elif num == 13:
                rle_string += 'd'
            elif num == 14:
                rle_string += 'e'
            elif num == 15:
                rle_string += 'f'
            # the rle_string at this point will be the hex code proceeded
            # by its run length. It can be added to the list as a unit.
            rle_list.append(rle_string)
            # the rle_string must now be reinitialized so that it can record
            # the next run length and hex code combination
            rle_string = ''
    # the final readable string must be created from the list, so we use
    # the join() function with the semicolon separator, as instructed
    final_string = ':'.join(rle_list)
    # return the final string.
    return final_string


# translates a human-readable RLE string with delimiters to RLE byte data.
def string_to_rle(rle_string):
    # initialize variables. first, the given string data must be converted
    # to a list with the run length and hex code combinations separated into units,
    # this new list is assigned to decode_list. rle_list will keep track of the
    # separated run length and hex codes as byte data. two_digit_number is created
    # to make sure that if the run length is 10 - 15, that the loop won't separate the
    # first digit from the second.
    decode_list = rle_string.split(':')
    rle_list = []
    two_digit_number = ''
    # loop to read each element in decode_list.
    for run_and_hex in decode_list:
        # here we create a variable to keep track of the length of the run and hex unit.
        len_run_and_hex = len(run_and_hex)
        # nested loop to read each item in the run_and_hex unit.
        for item in run_and_hex:
            # test if the current item is a digit.
            is_digit = item.isdigit()
            # if it is a digit, we must then determine if this digit is a
            # two-digit number (10-15) that gives the run length.
            if is_digit:
                # if there are three items in the unit, then the run length
                # is a two-digit number.
                if len_run_and_hex == 3:
                    # because it is a two-digit number, we need to ensure that the program
                    # will record the first and second digits together. so, we keep track
                    # of the digits by adding it to a string.
                    two_digit_number += item
                    # if the two_digit_number string reaches a length of 2,
                    # then that means the two-digit run length has been recorded
                    # and can be appended to the byte data list.
                    if len(two_digit_number) == 2:
                        rle_list.append(two_digit_number)
                        # we reinitialize the variable so that the loop will not continue
                        # to add numbers to the existing string in future iterations.
                        two_digit_number = ''
                        # after the first two digits, lun_run_and_hex must be set to zero so that in the
                        # next iteration, if the hex code value is a digit, we don't accidentally add a
                        # digit to the two_digit_number variable, which would disrupt the read of the next run
                        # length and hex unit.
                        len_run_and_hex = 0
                # if there are not 3 items in the unit, then the run length will be
                # one-digit, and we can just immediately append the digit to the byte data list.
                else:
                    rle_list.append(item)
            # if the item is not a digit and is a letter, it represents the hex code value,
            # and we will append to the byte data list the corresponding value.
            elif item == 'a':
                rle_list.append('10')
            elif item == 'b':
                rle_list.append('11')
            elif item == 'c':
                rle_list.append('12')
            elif item == 'd':
                rle_list.append('13')
            elif item == 'e':
                rle_list.append('14')
            elif item == 'f':
                rle_list.append('15')
    # return the final byte data list.
    return rle_list


def main():

    # main function.

    # initialize user_file variable as an empty string so that in the event that no file has been loaded,
    # the program will display an error message saying that no file has been loaded yet. see elif choice == 6
    # clause for more. current_data will keep track of the current_data.
    user_file = ''
    current_data = ''

    # display welcome message.
    print("Welcome to the RLE image encoder!")

    # display color test.
    color_test()

    # gather user input.
    choice = menu()

    # initialize menu loop.
    proceed = True
    while proceed:

        # if user chooses to quit, use quit() to exit the program.
        if choice == 0:
            quit()

        # if user chooses to load file...
        elif choice == 1:

            # call the image_file function to gather user input and then assign it to the user_file
            # variable so that the program knows which file to display (I'll use user_file as an argument in the
            # display_image method later).
            user_file = image_file()
            # call menu() function again so that loop can continue. This happens within every elif clause.
            choice = menu()

        # if user chooses to load the test file...
        elif choice == 2:

            # the statement below will call the display_image method from the ConsoleGfx class
            # and will use the test_image attribute from ConsoleGfx as the argument.
            user_file = ConsoleGfx.test_image
            print('Test image data loaded.')
            choice = menu()

        # if user chooses to input an RLE string with delimiters...
        elif choice == 3:

            # the current_data variable will be assigned to the RLE byte data for
            # the input RLE string so that if the user wants to display it later,
            # it can be encoded into a different format.
            current_data = string_to_rle(input("Enter an RLE string to be decoded: "))
            choice = menu()

        # if user chooses to input an RLE hex string...
        elif choice == 4:

            # the current_data variable is again assigned to the RLE byte data for the string.
            current_data = string_to_data(input("Enter the hex string holding RLE data: "))
            choice = menu()

        # if user chooses to input flat data...
        elif choice == 5:

            # the current_data variable will hold the data.
            current_data = input("Enter the hex string holding flat data: ")
            choice = menu()

        # if user chooses to display the loaded image....
        elif choice == 6:

            # if/else clause to ensure that there is an actual file to load so that runtime errors are avoided.
            # if user file is still the empty string that was initialized before the loop, then user has not
            # loaded a file and an error message will print and prompt the user to go back to the menu
            # and load a file before trying again.
            if user_file == '':
                print('\nNo file has been loaded yet. Please load a file, then try again.\n')
                choice = menu()
            else:
                # if user_file is anything other than an empty string, then the user has entered a valid file,
                # which has been assigned to the user_file variable. The file's name (being referenced by the variable)
                # can be passed as an argument through the display_image method from the ConsoleGfx class to display
                # the image.
                print('Displaying image...')
                ConsoleGfx.display_image(user_file)
                choice = menu()

        # if the user chooses to display the current data as RLE with delimiters...
        elif choice == 7:

            # we ensure that there is actually data to work with. if the string is empty, it is
            # because no data has been input so the user must go back and input the data.
            if current_data == '':
                print("No data has been input yet. Please input data, then try again.\n")
                choice = menu()
            # if there is data, then it will be translated into an RLE string with delimiters and printed.
            else:
                print(f"RLE representation: {to_rle_string(current_data)}")
                choice = menu()

        # if the user chooses to display the current data as RLE without delimiters...
        elif choice == 8:

            # again, we confirm that there is data to work with.
            if current_data == '':
                print("No data has been input yet. Please input data, then try again.\n")
                choice = menu()
            # if there is data, then it will be converted to a hex string without delimiters.
            else:
                print(f"RLE hex values: {to_hex_string(current_data)}")
                choice = menu()

        # if the user chooses to display the current flat data...
        elif choice == 9:

            # confirm that there is data to display.
            if current_data == '':
                print("No flat data has been input yet. Please input data, then try again.\n")
                choice = menu()
            # if there is flat data then it will print.
            else:
                data = ''.join(decode_rle(current_data))
                print(f"Flat hex values: {data}")
                choice = menu()

        # if user enters an integer other than 0-9, this error message will prompt them to try again
        else:
            # print error message
            print('That is not a valid option. Please try again.\n')
            # initialize small loop to test that user input won't cause runtime error
            test_main = True
            while test_main:
                try:
                    # the choice variable here is assigned something a little different from the other elif clauses,
                    # and this is because we don't want to call menu() and redisplay the whole menu to gather
                    # user's input, we just want them to enter another choice. We do, however, want to perform a
                    # similar check that the menu() function performs.
                    choice = int(input('Select a Menu Option: '))
                    # and once we have choice we have to stop the loop by setting the condition equal to false
                    test_main = False
                except:
                    print('That is not a valid option. Please try again.\n')


if __name__ == '__main__':

    main()
