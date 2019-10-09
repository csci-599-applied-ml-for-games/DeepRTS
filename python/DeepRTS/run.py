import numpy
import pygame

from game.Game import Game

MAP_NAME = '21x21-2v2.json'
NUM_OF_GAMES = 3


def play(g: Game):
    pygame.init()

    # Initial 2 players
    player1 = g.get_players(1)[0]
    player2 = g.get_players(2)[0]

    # Start the game (flag)
    g.start()

    # Run forever
    while True:
        g.tick()  # Update the game clock
        g.update()  # Process the game state
        g.render()  # Draw the game state to graphics
        g.caption()  # Show Window caption
        g.update_state()  # Update states to new model

        g.view()  # View the game state in the pygame window

        events_hack()

        g.capture()

        # If the game is in terminal state
        if g.is_terminal():
            g.stop()
            print("Game over")
            break

        # Perform random action for player 1
        x = numpy.random.randint(3, 20)
        y = numpy.random.randint(3, 20)
        player1.move_to(x, y)

        # Perform random action for player 2
        x = numpy.random.randint(3, 20)
        y = numpy.random.randint(3, 20)
        player2.move_to(x, y)


def events_hack():
    # Hack to render the pygame
    events = pygame.event.get()


def get_random_action():
    return numpy.random.randint(0, 16)


if __name__ == "__main__":
    game = Game(MAP_NAME)
    # game.add_a_player(1)
    # game.add_a_player(2)
    for _ in range(NUM_OF_GAMES):
        play(game)
        game.reset()