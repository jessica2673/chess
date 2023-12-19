Classic chess game featuring player and 4 computer level options against each other. Built with C++, unique algorithms, and the Observer design pattern along with a graphical display. The game checks and verifies validity of moves based on piece type, checks, checkmates, stalemates, castling, pawn promotion, enpassant, and other aspects of the game.

To play the game, run the "chess-exec" executable. To enter custom setup mode, type "setup" in the command line. Capital letters and lower case letters represent white and black pieces respectively. 
- "+ K a1" places or replaces the piece at a1 with the piece K (i.e., white king in this case) on the square a1 and redisplays the board.
- "- a1" removes any piece from the square a1 and redisplays the board.
- "= colour" makes it colour’s turn to go next.
- "done" exits setup mode.

To start a game, type in "game [white-player] [black-player]", where both player parameters can be "human", "computer[1]", "computer[2]", "computer[3]", or "computer[4]" where larger numbers represent more difficult computer levels.

To make a move once in a game as a human player, use the "move [a1] [a2]" command, where the first parameter takes in the square the piece to be moved is on, and the second parameters takes the square the piece should be moved to.

To make a move as a computer player, use the "move" command and a random move will be made based on the computer level.

To exit the game, either player can use the "resign" command and concede victory to the opponent.
Scores of both teams are recorded and displayed once the players choose not to continue the game.

