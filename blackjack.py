import p1_random as p1
rng = p1.P1Random()


def menu():
    # menu function to avoid redundancy
    print("1. Get another card\n" +
          "2. Hold hand\n" +
          "3. Print statistics\n" +
          "4. Exit\n")


def option():
    test = True
    while test:
        try:
            choice = int(input("Choose an option: "))
            test = False
        except EOFError:
            print('\nInvalid input!\n' +
                  'Please enter an integer value between 1 and 4.\n')
            menu()
    return choice


def generate_card():
    # function to generate card

    # generate number from imported module
    card_num = rng.next_int(13) + 1

    # determine card based on the number and assign value
    if card_num == 1:
        card = 'ACE'
    if 10 >= card_num >= 2:
        card = card_num
    if card_num == 11:
        card = 'JACK'
        card_num = 10
    if card_num == 12:
        card = 'QUEEN'
        card_num = 10
    if card_num == 13:
        card = 'KING'
        card_num = 10

    # explain to user what the card is
    print(f'\nYour card is a {card}!')

    # return card_num to add its value to user's hand
    return card_num


def dealer_play():
    # function to generate hand for dealer

    # initialize hand
    dealer_hand = 0

    # generate number from imported module
    dealer_hand += rng.next_int(11) + 16

    return dealer_hand


def main():

    # initialize variables
    player_hand = 0
    game_number = 1
    restart_loop = 0
    num_wins = 0
    num_loses = 0
    num_tie = 0

    # initialize main game loop
    proceed = True

    # main blackjack loop to control entire game
    while proceed:

        # start the game
        # restart_loop controls whether a new title has to print
        # if the game's statistics were not shown or the user chose a valid option,
        # then the start of the loop is a new game and the title prints.
        if restart_loop == 0:
            print(f"\nSTART GAME #{game_number}")
            # generate player's first hand
            player_hand = generate_card()
            # tell player what their current hand is
            print(f'Your hand is: {player_hand}\n')

            # display menu and get user input on how game should proceed
            menu()
            choice = option()

        else:
            # if the game's statistics were shown or the user chose an invalid option,
            # there is no new game and the player's hand continues as normal.
            restart_loop = 0
            # assigning zero to restart_loop resets the variable so that it won't keep increasing

        # continue player's hand if they chose 1
        while choice == 1:

            # generate another card for the hand
            player_hand += generate_card()
            print(f'Your hand is: {player_hand}\n')

            # determine if player has gone bust
            if player_hand > 21:
                print('You exceeded 21! You lose.')
                num_loses += 1
                game_number += 1
                break
            # determine if the player automatically wins
            if player_hand == 21:
                print('BLACKJACK! You win!')
                num_wins += 1
                game_number += 1
                break

            # have user select next option
            menu()
            choice = option()

        # proceed to dealer's hand if they chose 2
        while choice == 2:

            # generate dealer hand
            dealer_hand = dealer_play()
            print(f"\nDealer's hand: {dealer_hand}")
            print(f"Your hand is: {player_hand}\n")

            # determine winner
            if dealer_hand < player_hand:
                print('You win!')
                num_wins += 1
                game_number += 1
                break
            if dealer_hand == player_hand:
                print("It's a tie! No one wins!")
                num_tie += 1
                game_number += 1
                break
            if dealer_hand > player_hand and dealer_hand <= 21:
                print("Dealer wins!")
                num_loses += 1
                game_number += 1
                break
            if dealer_hand > player_hand and dealer_hand > 21:
                print("You win!")
                num_wins += 1
                game_number += 1
                break

        # if user selects choice 3
        while choice == 3:

            # calculate percentage of wins
            # display statistics
            percent_win = (num_wins / (game_number - 1)) * 100
            print(f"\nNumber of Player wins: {num_wins}\n" +
                  f"Number of Dealer wins: {num_loses}\n" +
                  f"Number of tie games: {num_tie}\n" +
                  f"Total # of games played is: {game_number - 1}\n" +
                  f"Percentage of Player wins: {percent_win: .1f}%\n")

            restart_loop += 1

            # have user select next option
            menu()
            choice = option()

        # terminate program if user chooses 4
        if choice == 4:
            quit()

        # if user chooses anything other than 1 - 4
        while choice < 1 or choice > 4:
            print('\nInvalid input!\n' +
                  'Please enter an integer value between 1 and 4.\n')

            restart_loop += 1

            # display menu to choose valid option
            menu()
            choice = option()



main()
