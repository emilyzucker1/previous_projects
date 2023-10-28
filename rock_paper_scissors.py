import random


def menu():
    print("\nMenu: \n" +
          "-" * 20 +
          "\n1. Play a new game\n" +
          "2. Show statistics\n" +
          "3. Quit")
    test = True
    while test:
        try:
            option = int(input("Select an option: "))
            test = False
        except ValueError:
            print("Oops! That's not a valid option." +
                  " Please try again.\n")
    return option


def player():
    check = True
    player_choice = input("Rock, Paper, or Scissors? ")
    while check:
        if player_choice == 'Rock' or player_choice == 'rock' or player_choice == 'ROCK':
            player_value = 1
            break
        elif player_choice == 'Paper' or player_choice == 'paper' or player_choice == 'PAPER':
            player_value = 2
            break
        elif player_choice == 'Scissors' or player_choice == 'scissors' or player_choice == 'SCISSORS':
            player_value = 3
            break
        else:
            print("\nOops! Looks like you didn't choose Rock, Paper" +
                  " or Scissors. Please try again.\n")
            player_choice = input("Rock, Paper, or Scissors? ")
    return player_value


def computer():
    computer_value = random.randint(1, 3)
    if computer_value == 1:
        print('\nComputer chose Rock.')
    elif computer_value == 2:
        print('\nComputer chose Paper.')
    elif computer_value == 3:
        print('\nComputer chose Scissors.')
    return computer_value


def play_game():
    verdict = ''
    user = player()
    machine = computer()
    if user == machine:
        verdict = 'Tie!'
    elif user == 1 and machine == 2:
        verdict = 'Computer Wins!'
    elif user == 1 and machine == 3:
        verdict = 'You Win!'
    elif user == 2 and machine == 1:
        verdict = 'You Win!'
    elif user == 2 and machine == 3:
        verdict = 'Computer Wins!'
    elif user == 3 and machine == 1:
        verdict = 'Computer Wins!'
    elif user == 3 and machine == 2:
        verdict = 'You Win!'
    return verdict


def main():
    num_games_played = 0
    num_wins = 0
    num_loses = 0
    num_ties = 0
    option = menu()
    proceed = True
    while proceed:
        if option == 1:
            verdict = play_game()
            if verdict == 'Tie!':
                num_ties += 1
            elif verdict == 'You Win!':
                num_wins += 1
            elif verdict == 'Computer Wins!':
                num_loses += 1
            num_games_played += 1
            print(verdict)
            option = menu()
        elif option == 2:
            percent_wins = (num_wins / num_games_played) * 100
            print("\nShowing statistics...\n\n" +
                  f"Number of Wins: {num_wins}\n" +
                  f"Number of Loses: {num_loses}\n" +
                  f"Number of Ties: {num_ties}\n" +
                  f"Percent Wins: {percent_wins}\n")
            option = menu()
        elif option == 3:
            quit()
        elif option > 3 or option < 1:
            print("\nOops! That's not a valid choice." +
                  " Please try again.")
            option = menu()

main()

