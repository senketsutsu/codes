# Playing games!

In this assignment your task is to make computer play games. Of course, we limit ourselves to a very limited subset of games: two players, zero sum, perfect information, deterministic games. These properties may require some explanation:

* *Two players* is pretty straightforward: there are exactly two players. Any less is a puzzle (see previous classes), any more is interesting (but out of scope).
* *Zero sum* means that a win of one player is necessarly a loss of the other player. For example, if one player wins the game having 100 points, the other player must have exactly -100 points.
* *Perfect information* means that there are no hidden variables in the game, like some cards kept in secret by players. Both players can see exactly the same thing.
* *Deterministic* means that there is no randomness in the game, no dices, no decks of cards, etc.

Each and every of these assumptions can be relaxed, yielding a more complex variant of the problem of playing games.

## Game

We begin by defining a general class `Game`, equipped with 7 functions:

* `initial_state` returns a representation of an intial state of the game, e.g., an empty board and an information which player plays first. State is opaque to search algorithms, similarly as in the classes on Agents and A*.
* `player` return the id of a player to make a move in the given `state`. Here we consistently use number 1 to represent the first player and 2 to represent the second player, but in general any two distict identifiers would suffice.
* `actions` returns a list of valid moves in the given state. This corresponds to the list of available actions in previous classes.
* `result` returns a new state after performing the given `action` in the given `state`. This is the transition model underpinning the game.
* `is_terminal` returns `True` if the given `state` is a terminal node in the search tree, i.e., either one of the players won or it is a draw. This is a leaf in a search tree and no further actions can be executed.
* `utility` can be called only for a terminal `state` and returns a numeric representation of how good this state is for the given `player`. Because we are considering zero-sum games it is always true that `utility(state, 1) = -utility(state, 2)`
* `print_state` is a helper function to pretty-print the given `state` to the standard output. As the representation is opaque and possibly hard to read for a human, this little function will make our lives much easier further down the line.


```python
class Game:
    @property
    def initial_state(self):
        ...
        return state
    
    def player(self, state):
        ...
        return playerno
        
    def actions(self, state):
        ...
        return actions
        
    def result(self, state, action):
        ...
        return new_state
        
    def is_terminal(self, state):
        ...
        return boolean
        
    def utility(self, state, player):
        ...        
        return number
        
    def print_state(self, state):
        ...        
```

For convenience we define a simple function `opponent` that, given a player id, returns the id of the other player.


```python
def opponent(player):    
    assert player in {1, 2}
    if player == 1:
        return 2
    else:
        return 1
```

## Tic-Tac-Toe

The first game we'll consider is *Tic-Tac-Toe* (*noughts and crosses*) in its bare minimum. For completeness, let me quote [Wikipedia](https://en.wikipedia.org/w/index.php?title=Tic-tac-toe&oldid=986503204) on rules: 

> Tic-tac-toe (American English), noughts and crosses (Commonwealth English), or Xs and Os, is a paper-and-pencil game for two players, X and O, who take turns marking the spaces in a 3×3 grid. The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row is the winner. It is a solved game with a forced draw assuming best play from both players.


```python
class TicTacToe(Game):    
    @property
    def initial_state(self):
        return (1, (0,)*9)
    
    def player(self, state):
        return state[0]
        
    def actions(self, state):
        return [i for i, v in enumerate(state[1]) if v == 0]
        
    def result(self, state, action):
        board = state[1]
        assert board[action] == 0
        assert state[0] in {1, 2}
        board = board[:action] + (state[0],) + board[action+1:]
        next_player = opponent(state[0])        
        return (next_player, board)
        
    def _has_line(self, state, player):
        board = state[1]
        for i in [0, 3, 6]:
            if board[i] == board[i+1] == board[i+2] == player:
                return True
        for i in [0, 1, 2]:
            if board[i] == board[i+3] == board[i+6] == player:
                return True
        if board[0] == board[3+1] == board[2*3+2] == player:
            return True
        if board[2] == board[3+1] == board[2*3] == player:
            return True
        return False
        
    def is_terminal(self, state):
        if all([v != 0 for v in state[1]]):
            return True
        return self._has_line(state, 1) or self._has_line(state, 2)
    
    def utility(self, state, player):
        assert player in {1, 2}
        mine = self._has_line(state, player)
        opponents = self._has_line(state, opponent(player))
        if mine and not opponents:
            return 1
        if not mine and opponents:
            return -1
        return 0    
    
    def print_state(self, state):
        print("Player making move", " OX"[state[0]])
        board = ["_OX"[v] for v in state[1]]
        print(*board[0:3])
        print(*board[3:6])
        print(*board[6:9])
```

The actions are represented by the number of field where to put a mark, using the following map:
```
0|1|2
-----
3|4|5
-----
6|7|8
```

The cell below executes a sequence of actions that leads to a draw.


```python
game = TicTacToe()
state = game.initial_state
game.print_state(state)

for action in [4,0,6,2,1,7,5,3,8]:
    assert action in game.actions(state)
    assert not game.is_terminal(state)
    state = game.result(state, action)
    game.print_state(state)
    
print("Reached terminal state?", game.is_terminal(state))
print("Utility for the 1st player", game.utility(state, 1))
print("Utility for the 2nd player", game.utility(state, 2))
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Player making move X
    _ _ _
    _ O _
    _ _ _
    Player making move O
    X _ _
    _ O _
    _ _ _
    Player making move X
    X _ _
    _ O _
    O _ _
    Player making move O
    X _ X
    _ O _
    O _ _
    Player making move X
    X O X
    _ O _
    O _ _
    Player making move O
    X O X
    _ O _
    O X _
    Player making move X
    X O X
    _ O O
    O X _
    Player making move O
    X O X
    X O O
    O X _
    Player making move X
    X O X
    X O O
    O X O
    Reached terminal state? True
    Utility for the 1st player 0
    Utility for the 2nd player 0
    

Below, 2 plays suboptimally and loses.


```python
game = TicTacToe()
state = game.initial_state
game.print_state(state)

for action in [4,0,6,2,1,8,7]:
    assert action in game.actions(state)
    assert not game.is_terminal(state)
    state = game.result(state, action)
    game.print_state(state)
    
print("Reached terminal state?", game.is_terminal(state))
print("Utility for the 1st player", game.utility(state, 1))
print("Utility for the 2nd player", game.utility(state, 2))
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Player making move X
    _ _ _
    _ O _
    _ _ _
    Player making move O
    X _ _
    _ O _
    _ _ _
    Player making move X
    X _ _
    _ O _
    O _ _
    Player making move O
    X _ X
    _ O _
    O _ _
    Player making move X
    X O X
    _ O _
    O _ _
    Player making move O
    X O X
    _ O _
    O _ X
    Player making move X
    X O X
    _ O _
    O O X
    Reached terminal state? True
    Utility for the 1st player 1
    Utility for the 2nd player -1
    

Finally, in the cell below 1 plays suboptimally and loses.


```python
game = TicTacToe()
state = game.initial_state
game.print_state(state)

for action in [2,4,6,0,7,8]:
    assert action in game.actions(state)
    assert not game.is_terminal(state)
    state = game.result(state, action)
    game.print_state(state)
    
print("Reached terminal state?", game.is_terminal(state))
print("Utility for the 1st player", game.utility(state, 1))
print("Utility for the 2nd player", game.utility(state, 2))
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Player making move X
    _ _ O
    _ _ _
    _ _ _
    Player making move O
    _ _ O
    _ X _
    _ _ _
    Player making move X
    _ _ O
    _ X _
    O _ _
    Player making move O
    X _ O
    _ X _
    O _ _
    Player making move X
    X _ O
    _ X _
    O O _
    Player making move O
    X _ O
    _ X _
    O O X
    Reached terminal state? True
    Utility for the 1st player -1
    Utility for the 2nd player 1
    

## A judge and a dummy

Lets define a common interface for a player: it is a callable (e.g., a function) receiving two arguments: 

1. The definition of a game as an object of the class `Game`
2. A current state in which a move is to be made.

The following function `dummy` follows this interface. It represents a player that always makes the first available move.


```python
def dummy(game, state):
    return game.actions(state)[0]
```

To test players it is convenient to construct a general judge with three parameters:

* `game` A definition of a game of type `Game`.
* `player1` A callable following the interface described above representing the first player.
* `player2` A callable following the interface described above representing the second player.


```python
def judge(game: Game, player1, player2):    
    state = game.initial_state

    while not game.is_terminal(state):
        if game.player(state) == 1:
            action = player1(game, state)
        else:
            action = player2(game, state)        
        game.print_state(state)
        print("Action:", action)
        print()
        state = game.result(state, action)

    game.print_state(state)
    print("Reached terminal state?", game.is_terminal(state))
    u1 = game.utility(state, 1)
    u2 = game.utility(state, 2)
    print("Utility for the 1st player", u1)
    print("Utility for the 2nd player", u2)
    if u1 > u2:
        print("Winner: 1st player")
    elif u1 < u2:
        print("Winner: 2nd player")
    else:
        print("Draw")
```

Lets see how well two dummies compete against each other in the game of Tic-Tac-Toe.


```python
judge(TicTacToe(), dummy, dummy)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 1
    
    Player making move O
    O X _
    _ _ _
    _ _ _
    Action: 2
    
    Player making move X
    O X O
    _ _ _
    _ _ _
    Action: 3
    
    Player making move O
    O X O
    X _ _
    _ _ _
    Action: 4
    
    Player making move X
    O X O
    X O _
    _ _ _
    Action: 5
    
    Player making move O
    O X O
    X O X
    _ _ _
    Action: 6
    
    Player making move X
    O X O
    X O X
    O _ _
    Reached terminal state? True
    Utility for the 1st player 1
    Utility for the 2nd player -1
    Winner: 1st player
    

## Task 1: Minimax algorithm

Complete the following cell with an implementation of the mini-max algorithm. 
The function should follow the interface for a player described above and return the best move to be made in the given `state` under the rules defined by the `game`.


```python
import math

def min_value(game: Game, state, player):
    if game.is_terminal(state):
        return(game.utility(state, player), None)
    v = math.inf
    #move = None
    for a in game.actions(state):
        v2,a2 = max_value(game,game.result(state,a),player)
        if v2 < v:
            v,move = v2, a
    return(v, move)

def max_value(game: Game, state, player):
    if game.is_terminal(state):
        return(game.utility(state, player), None)
    v = -math.inf
    #move = None
    for a in game.actions(state):
        v2,a2 = min_value(game,game.result(state,a),player)
        if v2 > v:
            v,move = v2, a
    return(v, move)
    
def minimax(game: Game, state):
    player = game.player(state)
    value, move = max_value(game, state, player)
    return(move)
    ...
```

Lets test your implementation against dummy and against itself. It should always win with dummy (dummy is deterministic and suboptimal) and it should draw with itself (Tic-Tac-Toe is a solved game and draw is the best outcome for optimal players).
We prefix the calls to `judge` with `%time` to measure time spent in the call. This will be useful to compare the performance of minimax with alpha-beta.


```python
%time judge(TicTacToe(), minimax, dummy)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 1
    
    Player making move O
    O X _
    _ _ _
    _ _ _
    Action: 3
    
    Player making move X
    O X _
    O _ _
    _ _ _
    Action: 2
    
    Player making move O
    O X X
    O _ _
    _ _ _
    Action: 4
    
    Player making move X
    O X X
    O O _
    _ _ _
    Action: 5
    
    Player making move O
    O X X
    O O X
    _ _ _
    Action: 6
    
    Player making move X
    O X X
    O O X
    O _ _
    Reached terminal state? True
    Utility for the 1st player 1
    Utility for the 2nd player -1
    Winner: 1st player
    Wall time: 8.33 s
    


```python
%time judge(TicTacToe(), dummy, minimax)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 4
    
    Player making move O
    O _ _
    _ X _
    _ _ _
    Action: 1
    
    Player making move X
    O O _
    _ X _
    _ _ _
    Action: 2
    
    Player making move O
    O O X
    _ X _
    _ _ _
    Action: 3
    
    Player making move X
    O O X
    O X _
    _ _ _
    Action: 6
    
    Player making move O
    O O X
    O X _
    X _ _
    Reached terminal state? True
    Utility for the 1st player -1
    Utility for the 2nd player 1
    Winner: 2nd player
    Wall time: 1.35 s
    


```python
%time judge(TicTacToe(), minimax, minimax)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 4
    
    Player making move O
    O _ _
    _ X _
    _ _ _
    Action: 1
    
    Player making move X
    O O _
    _ X _
    _ _ _
    Action: 2
    
    Player making move O
    O O X
    _ X _
    _ _ _
    Action: 6
    
    Player making move X
    O O X
    _ X _
    O _ _
    Action: 3
    
    Player making move O
    O O X
    X X _
    O _ _
    Action: 5
    
    Player making move X
    O O X
    X X O
    O _ _
    Action: 7
    
    Player making move O
    O O X
    X X O
    O X _
    Action: 8
    
    Player making move X
    O O X
    X X O
    O X O
    Reached terminal state? True
    Utility for the 1st player 0
    Utility for the 2nd player 0
    Draw
    Wall time: 8.67 s
    

## Task 2: Alpha-beta

Mini-max is an optimal solution, but not the most efficient. Complete the following cell of code implementing the alpha-beta algorithm.
The function should follow the interface for a player described above and return the best move to be made in the given `state` under the rules defined by the `game`.


```python
import math

def min_value(game: Game, state, alpha, beta, player):
    if game.is_terminal(state):
        return(game.utility(state, player), None)
    v = math.inf
    for a in game.actions(state):
        v2,a2 = max_value(game, game.result(state, a), alpha, beta, player)
        if v2 < v:
            v,move = v2, a
            beta = min(beta, v)
        if v <= alpha:
            return(v, move)
    return(v, move)

def max_value(game: Game, state, alpha, beta, player):
    if game.is_terminal(state):
        return(game.utility(state, player), None)
    v = -math.inf
    for a in game.actions(state):
        v2,a2 = min_value(game, game.result(state, a), alpha, beta, player)
        if v2 > v:
            v,move = v2, a
            alpha = max(alpha, v)
        if v >= beta:
            return(v, move)
    return(v, move)
    
def alphabeta(game: Game, state):
    player = game.player(state)
    value, move = max_value(game, state, (-math.inf), math.inf, player)
    return(move)
    ...
```

Again, lets test your implementation against dummy and against itself. It should behave in exactly the same way as minimax, but be faster.


```python
%time judge(TicTacToe(), alphabeta, dummy)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 1
    
    Player making move O
    O X _
    _ _ _
    _ _ _
    Action: 3
    
    Player making move X
    O X _
    O _ _
    _ _ _
    Action: 2
    
    Player making move O
    O X X
    O _ _
    _ _ _
    Action: 4
    
    Player making move X
    O X X
    O O _
    _ _ _
    Action: 5
    
    Player making move O
    O X X
    O O X
    _ _ _
    Action: 6
    
    Player making move X
    O X X
    O O X
    O _ _
    Reached terminal state? True
    Utility for the 1st player 1
    Utility for the 2nd player -1
    Winner: 1st player
    Wall time: 342 ms
    


```python
%time judge(TicTacToe(), dummy, alphabeta)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 4
    
    Player making move O
    O _ _
    _ X _
    _ _ _
    Action: 1
    
    Player making move X
    O O _
    _ X _
    _ _ _
    Action: 2
    
    Player making move O
    O O X
    _ X _
    _ _ _
    Action: 3
    
    Player making move X
    O O X
    O X _
    _ _ _
    Action: 6
    
    Player making move O
    O O X
    O X _
    X _ _
    Reached terminal state? True
    Utility for the 1st player -1
    Utility for the 2nd player 1
    Winner: 2nd player
    Wall time: 75.9 ms
    


```python
%time judge(TicTacToe(), alphabeta, alphabeta)
```

    Player making move O
    _ _ _
    _ _ _
    _ _ _
    Action: 0
    
    Player making move X
    O _ _
    _ _ _
    _ _ _
    Action: 4
    
    Player making move O
    O _ _
    _ X _
    _ _ _
    Action: 1
    
    Player making move X
    O O _
    _ X _
    _ _ _
    Action: 2
    
    Player making move O
    O O X
    _ X _
    _ _ _
    Action: 6
    
    Player making move X
    O O X
    _ X _
    O _ _
    Action: 3
    
    Player making move O
    O O X
    X X _
    O _ _
    Action: 5
    
    Player making move X
    O O X
    X X O
    O _ _
    Action: 7
    
    Player making move O
    O O X
    X X O
    O X _
    Action: 8
    
    Player making move X
    O O X
    X X O
    O X O
    Reached terminal state? True
    Utility for the 1st player 0
    Utility for the 2nd player 0
    Draw
    Wall time: 515 ms
    

## Cats and dogs

The following cell defines the rules for the game *Cats and dogs* AKA *Snort*. See https://www.di.fc.ul.pt/~jpn/gv/catdogs.htm for a complete description of rules.
This implementation is somewhat more flexible: instead of using a board of fixed size, the size of a board is defined by the constructor parameter `n`.


```python
class CatsAndDogs:
    def __init__(self, n):
        self.n = n
    
    @property
    def initial_state(self):
        return (1, ((0,)*self.n,)*self.n)
    
    def player(self, state):
        return state[0]
                
    def _adj(self, x, y):                
        for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            nx = x + dx
            ny = y + dy
            if nx >= 0 and ny >= 0 and nx < self.n and ny < self.n:
                yield (nx, ny)
        
    def actions(self, state):
        board = state[1]
        opp = opponent(self.player(state))
        actions = []
        for x in range(self.n):
            for y in range(self.n):
                if board[x][y] == 0 and all([board[nx][ny] != opp for nx, ny in self._adj(x, y)]):
                    actions.append((x, y))
        return actions
        
    def result(self, state, action):
        x, y = action
        player, board = state
        col = board[x][:y] + (player,) + board[x][y+1:]
        board = board[:x] + (col,) + board[x+1:]
        return (opponent(player), board)
        
    def is_terminal(self, state):
        return len(self.actions(state)) == 0
        
    def utility(self, state, player):
        assert self.is_terminal(state)
        if self.player(state) == player:
            return -1
        else:
            return 1
        
    def print_state(self, state):
        print("Player making move", "_\u25CB\u25CF"[state[0]])
        for row in state[1]:
            print(*["_\u25CB\u25CF"[v] for v in row])        
```

Lets see how well alpha-beta fares on a board of 3x3. 


```python
judge(CatsAndDogs(3), alphabeta, alphabeta)
```

    Player making move ○
    _ _ _
    _ _ _
    _ _ _
    Action: (0, 0)
    
    Player making move ●
    ○ _ _
    _ _ _
    _ _ _
    Action: (0, 2)
    
    Player making move ○
    ○ _ ●
    _ _ _
    _ _ _
    Action: (1, 1)
    
    Player making move ●
    ○ _ ●
    _ ○ _
    _ _ _
    Action: (2, 0)
    
    Player making move ○
    ○ _ ●
    _ ○ _
    ● _ _
    Action: (2, 2)
    
    Player making move ●
    ○ _ ●
    _ ○ _
    ● _ ○
    Reached terminal state? True
    Utility for the 1st player 1
    Utility for the 2nd player -1
    Winner: 1st player
    

You may be patient enough to test it on a board of 4x4.


```python
%time judge(CatsAndDogs(4), alphabeta, alphabeta)
```

    Player making move ○
    _ _ _ _
    _ _ _ _
    _ _ _ _
    _ _ _ _
    Action: (0, 0)
    
    Player making move ●
    ○ _ _ _
    _ _ _ _
    _ _ _ _
    _ _ _ _
    Action: (1, 1)
    
    Player making move ○
    ○ _ _ _
    _ ● _ _
    _ _ _ _
    _ _ _ _
    Action: (0, 2)
    
    Player making move ●
    ○ _ ○ _
    _ ● _ _
    _ _ _ _
    _ _ _ _
    Action: (1, 3)
    
    Player making move ○
    ○ _ ○ _
    _ ● _ ●
    _ _ _ _
    _ _ _ _
    Action: (2, 0)
    
    Player making move ●
    ○ _ ○ _
    _ ● _ ●
    ○ _ _ _
    _ _ _ _
    Action: (2, 2)
    
    Player making move ○
    ○ _ ○ _
    _ ● _ ●
    ○ _ ● _
    _ _ _ _
    Action: (3, 0)
    
    Player making move ●
    ○ _ ○ _
    _ ● _ ●
    ○ _ ● _
    ○ _ _ _
    Action: (2, 3)
    
    Player making move ○
    ○ _ ○ _
    _ ● _ ●
    ○ _ ● ●
    ○ _ _ _
    Action: (3, 1)
    
    Player making move ●
    ○ _ ○ _
    _ ● _ ●
    ○ _ ● ●
    ○ ○ _ _
    Action: (3, 3)
    
    Player making move ○
    ○ _ ○ _
    _ ● _ ●
    ○ _ ● ●
    ○ ○ _ ●
    Reached terminal state? True
    Utility for the 1st player -1
    Utility for the 2nd player 1
    Winner: 2nd player
    Wall time: 1min 33s
    

## Task 3: Alpha-beta with limited depth and heuristic evaluation

Alpha-beta is a complete and optimal algorithm, but still too slow.
In practice it is used as a heuristic algorithm: sometimes searching is terminated before reaching a terminal node and some heuristic evaluation of the reached non-terminal state is returned instead of the utility of a terminal state.
How to evaluate non-terminal states and how to decide when to terminate search is an extremely rich topic.

Complete the cells below:

* Implement the function `evaluate` in `CatsAndDogsWithHeuristic` such that it returns some evaluation of the given `state` from the point of view of the given `player`. The more promising the state for the player, the higher value should be returned.
* Implement the function `__call__` in `HeuristicAlphaBeta` such that it is an implementation of the alpha-beta algorithm, but should the recursion depth reach `self.max_depth` the heuristic evaluation should be returned instead of descending further in the game tree.

Minimax and alpha-beta are game-agnostic and thus for them states are opaque. On the other hand `evaluate` is not game-agnostic, but it is also not (strictly speaking) a part of the rules of a game. Still, it needs to access the internals of the state and in the provided implementation of `CatsAndDogs` the state is a 2-tuple:

1. The id of a player to make a move
2. The representation of a board as a tuple of tuples, forming an `self.n` $\times$ `self.n` array. Each element of this tuple of tuples is either:
   * 0 - an empty cell
   * 1 - a stone of player 1
   * 2 - a stone of player 2


```python
class CatsAndDogsWithHeuristic(CatsAndDogs):
    def evaluate(self, state, player):
        ...
        return number
```


```python
class HeuristicAlphaBeta:
    def __init__(self, max_depth):
        self.max_depth = max_depth
        
    def __call__(self, game, state):
        ...
        return best_move
```

Lets test your implementations in three scenarios on a board of $4\times 4$:

* Alpha-beta at the depth of 3 playing agains alpha-beta at the depth of 5.
* In reverse: Alpha-beta at the depth of 5 playing agains alpha-beta at the depth of 6.
* Alpha-beta at the depth of 6 playing against alpha-beta at the depth of 5.
* Alpha-beta at the depth of 6 playing against optimal alpha-beta.

If your implementation of alpha-beta is good and your heuristic evaluation are good, the player with the deeper depth should win.
Of course in the last case the optimal alpha-beta should win.


```python
judge(CatsAndDogsWithHeuristic(4), HeuristicAlphaBeta(3), HeuristicAlphaBeta(5))
```


```python
judge(CatsAndDogsWithHeuristic(4), HeuristicAlphaBeta(5), HeuristicAlphaBeta(3))
```


```python
judge(CatsAndDogsWithHeuristic(4), HeuristicAlphaBeta(6), HeuristicAlphaBeta(5))
```


```python
judge(CatsAndDogsWithHeuristic(4), HeuristicAlphaBeta(6), alphabeta)
```


```python
judge(CatsAndDogsWithHeuristic(4), HeuristicAlphaBeta(5), HeuristicAlphaBeta(4))
```


```python

```
