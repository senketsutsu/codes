# Local search and constraint satisfaction problems

During the previous classes we were concerned with finding a sequence of actions (a plan) to reach one of the goal states from a predefined initial state. In a sense, we were more interested in the *journey* rather than in the *destination* itself: our goal was to transform the initial state to the goal state, not to construct the goal state from scratch. Constraint satisfaction problems (CSP) are different from them: we are not interested in the journey, only in the destination. We are again in a situation where we can recognize a goal state, but we don't care how we get there, the only interesting aspect is finding a state that satisfies all specified constraints. Local search is also different from tree/graph search algorithms like A*: it assumes that all intermediate states are acceptable, but they differ in their quality and the goal is to find the best solution.

## Constraint satisfaction problem

In the previous tasks the state was opaque: an algorithm could execute an action and transform a state to another state, but that was it. It could not depend in its search on the details of a state, because the state representation was different from problem to problem. In CSP this is no longer true: the state always consists of an assignment of values over some domains to variables. This enables an algorithm to interact with the state directly, not only through opaque actions. 

Allowed assignments are limited by constraints in the problem and broadly speaking they can be divided into three groups:

* *Unary constraints* each concerning only a single variable (e.g., $x>0$)
* *Binary constraints* relating two variables to each other (e.g., $x>y$)
* *General constraints* concerning more than two variables at once

In general, the shape of constraints is unrestricted and we are not limited to numeric domains and constraints in the form of inequalities. In principle, one could employ arbitrary boolean functions as constraints.

The following class `CSP` is a very limited representation of such a problem capable only of handling:

* unary constraints defined in terms of Python's operators `==`, `!=`, `<`, `<=`, `>`, `>=` and `in` such that the left-hand side of the operator is a variable and the right-hand side is a constant
* binary constraints defined in terms of Python's operators `==`, `!=`, `<`, `<=`, `>` and `>=` such that both sides are variables.

About its methods:

* The constructor (`__init__`) requires a single argument: a domain shared by all the variables. This is not used by the class itself, but it is exposed as a field `domain` to be used by algorithms solving a CSP modelled this way.
* `addUnaryConstraint` requires three arguments: 
    * `var` - a variable (a string representing ins name, but really, it could be any object);
    * `op` - an operator (one of the following strings: `'=='`, `'!='`, `'<'`, `'<='`, `'>'`, `'>='` and `'in'`)
    * `value` - an element of the domain for all the operators except `in` and a subset of the domain for the `in` operator
* `addBinaryConstraint` also requires three arguments:
    * `var1` - a variable, the left-hand side of the constraint
    * `op` - an operator (one of the following strings: `'=='`, `'!='`, `'<'`, `'<='`, `'>'`, `'>='`)
    * `var2` - a variable, the right-hand side of the constraint
* `verify` gets a single argument: a (partial) solution in the form of a Python's dictionary mapping variables to values and returns a pair of numbers. The first it the number constraints satisfied by the provided solution, the second is the number of unsatisfied constraints.


```python
class CSP:
    def __init__(self, domain):
        self.variables = set()
        self.domain = domain
        self.unary = []
        self.binary = []
    
    def addUnaryConstraint(self, var, op, value):        
        self.unary.append((var, op, value))        
        self.variables.add(var)
        
    def addBinaryConstraint(self, var1, operator, var2):
        c = (var1, operator, var2)
        self.binary.append(c)
        self.variables.add(var1)
        self.variables.add(var2)        
        
    def _verify(self, left, op, right):
        if op[0] == '=':
            return left == right
        if op == '!=':
            return left != right
        if op == '<':
            return left < right
        if op == '<=':
            return left <= right
        if op == '>':
            return left > right
        if op == '>=':
            return left >= right
        if op.lower() == 'in':
            return left in right
        
    def verify(self, solution):
        unary_hit = 0
        unary_miss = 0
        for var, op, value in self.unary:            
            if var in solution and self._verify(solution[var], op, value):
                unary_hit += 1
            else:
                unary_miss += 1
        binary_hit = 0
        binary_miss = 0
        for var1, op, var2 in self.binary:
            if var1 in solution and var2 in solution:
                if self._verify(solution[var1], op, solution[var2]):
                    binary_hit += 1
                    continue            
            binary_miss += 1
        return unary_hit + binary_hit, unary_miss + binary_miss
```

## Making Australia colorful again

Lets model a map coloring problem. In particular, we'll color the following map of Australia. It can be simplified to a graph presented in the right-hand side of the picture below.

![](aima-images/fig_6_1.png)

We begin by creating a new problem in the variable `australia` over the domain consisting of three values: `'R'` statnding for the color red, `'G'` standing for green and `'B'` standing for blue. Of course the particular symbols used are not relevant.


```python
australia = CSP({'R', 'G', 'B'})
```

Any two teritories of Australia sharing a border should be colored using different colours. We thus define 7 binary constraints.


```python
australia.addBinaryConstraint('WA', '!=', 'NT')
australia.addBinaryConstraint('WA', '!=', 'SA')
australia.addBinaryConstraint('NT', '!=', 'SA')
australia.addBinaryConstraint('NT', '!=', 'Q')
australia.addBinaryConstraint('SA', '!=', 'Q')
australia.addBinaryConstraint('SA', '!=', 'NSW')
australia.addBinaryConstraint('SA', '!=', 'V')
```

Lets now verify a solution such that *Western Australia* is red and the rest is unspecified.


```python
australia.verify({'WA': 'R'})
```




    (0, 7)



As expected it didn't work: there are still 7 unfulfiled constraints. So lets extend the solution.


```python
australia.verify({'WA': 'R', 'Q': 'R', 'V': 'R', 'NT': 'B', 'NSW': 'B', 'SA': 'G'})
```




    (7, 0)



Splendid, now everything works as it should: all 7 constraints are satisfied! The problem is, Tasmania still has no color assigned. To address this, we add unary constraints requiring that each of the 7 teritories has a color assigned.


```python
for teritory in ['WA', 'SA', 'Q', 'NT', 'NSW', 'V', 'T']:
    australia.addUnaryConstraint(teritory, 'in', {'R', 'G', 'B'})
```

Lets verify the incomplete solution again:


```python
australia.verify({'WA': 'R', 'Q': 'R', 'V': 'R', 'NT': 'B', 'NSW': 'B', 'SA': 'G'})
```




    (13, 1)



Now one constraint remains unsatisfied. Lets extend the solution.


```python
australia.verify({'WA': 'R', 'Q': 'R', 'V': 'R', 'NT': 'B', 'NSW': 'B', 'SA': 'G', 'T': 'B'})
```




    (14, 0)



## Task 1: CSP as search

Complete the following class `CSSearchProblem` casting a CSP (given in the field `self.csp`) as a generic search problem. It is very similar to the tasks you solved during the previous classes:

* `initial_state` should return an intial state of the search (e.g., a state such that no variable has any value assigned though you may consider other possibilities, such as filling it with a random assignment instead)
* `available_actions` should return a list of avilable actions in the given state, each action should correspond to assigning a value to a variable
* `do_action` generates a new state by adding/changing the assignment specified in the given action
* `value` is about the only new thing: this should be some measure of the quality of the given state (solution), the higher value the better.

Please bear in mind the following: **This is NOT how you should solve CSP problems in real life.** You SHOULD use an off-the-shelf solver or at the very least implement specialized algorithms for CSP, which were discussed in details during the lecture. It is, nevertheless, an interesting exercise to cast one kind of a problem as another kind and see what emerges. Sometimes such an exercises can lead to a genuinely valuable solution.


```python
import copy
class CSSearchProblem:
    def __init__(self, csp):
        self.csp = csp
    
    @property
    def initial_state(self):
        return ({})
        
    def available_actions(self, state):
        ...
        # copy all actions
        action = list(copy.deepcopy(self.csp.domain))
        #print(action)
        # copy all variables
        options = copy.deepcopy(self.csp.variables)
        # create an empty table
        actions = {}
        # iterate over all variables
        for i in options:
            # add copy of all actions
            actions.update({i : list(copy.deepcopy(action))})
            #print(actions[i])
            # del those actions that are not good
            for j in range( len( actions[i] )):
                for var, op, value in self.csp.unary:
                    if var == actions[i]:
                        if not( self.csp._verify( actions[i][j], op, value )):
                            del actions[i][j]
        return actions
        
    def do_action(self, state, action):
        ...
        new_state = copy.deepcopy(state)
        dkey = state.keys()
        
        x, y = action
        
        new_state[x] = y
            
        return new_state
    
    def value(self, state) -> float:
        hit, miss = self.csp.verify(state)
        return ( hit/(hit+miss) )
```

## Task 2: Implement hill climbing to solve search problems

Complete the following cell of code with an implemention of the hill climbing algorithm.
The algorithm starts in the initial state of the given search problem `problem` and loops forever.
During each repetition of the loop it "looks around" and tests all the states achievable through actions available in the current state.
If none of them is better than the current state (i.e., the algorithm reached a peak or a plateau according to the `value` function), it breaks the loop and returns the reached state.
Otherwise, it goes to the best of these neighbouring states and computes the next repetition of the loop.


```python
import copy
import random
def hill_climbing(problem: CSSearchProblem):
    #current_state = copy.deepcopy(problem.initial_state())
    current_state = {}
    actions = problem.available_actions(current_state)
    new_state = copy.deepcopy(current_state)
    temp={}
    while True:
        # loop on all options 
        # loop on keys
        for var1 in actions.keys():
            # loop on actions
            for var2 in actions[var1]:
                # do the action
                temp = problem.do_action(current_state, (var1, var2))
                # check if its better
                if problem.value(temp) > problem.value(new_state):
                    new_state = copy.deepcopy(temp)
        if problem.value(current_state) == problem.value(new_state):
            print(problem.csp.verify(new_state))
            return(new_state)
        current_state = copy.deepcopy(new_state)
            
    
    ...
```

Lets test your implementation by solving the problem of coloring Australia!


```python
solution = hill_climbing(CSSearchProblem(australia))
solution
```

    (14, 0)
    




    {'SA': 'G', 'NSW': 'R', 'Q': 'R', 'NT': 'B', 'WA': 'R', 'V': 'R', 'T': 'G'}



Is the obtained solution correct and complete? (It should be and the following assertion should not fail.)


```python
assert australia.verify(solution) == (14, 0)
```

## Sudoku!

Coloring Australia is really a bit boring. Lets deal with something more exciting: SUDOKU! I assume you know the rules, but if you don't, go look them up, spend some time solving a few puzzles and familiarize yourself with the puzzle.
The cell below defines a string `puzzle` which represents a Sudoku puzzle from the picture below. A digit in `puzzle` corresponds to a digit in the puzzle, while an underscore `_` corresponds to a blank cell in the puzzle. For your convenience there's also variable `solution` containing the correct solution to this particular puzzle.

![](aima-images/fig_6_4.png)


```python
puzzle = '''
__3_2_6__
9__3_5__1
__18_64__
__81_29__
7_______8
__67_82__
__26_95__
8__2_3__9
__5_1_3__
'''
```


```python
solution = '''
483921657
967345821
251876493
548132976
729564138
136798245
372689514
814253769
695417382
'''
```

### Task 3: Sudoku as CSP

Using the string `puzzle` defined above write in the cell below code that will add all the necessary constraints to the CSP represented by the variable `sudoku`. 


```python
sudoku = CSP({1, 2, 3, 4, 5, 6, 7, 8, 9})

# the names of each element is 0, 1, 2 ... 80 (we go as rows)
# small example
# 0 1 2
# 3 4 5
# 6 7 8

for i in range(81):
    sudoku.addUnaryConstraint(str(i), 'in', {1, 2, 3, 4, 5, 6, 7, 8, 9})
    
    # different in the squares
    for j in range(((i%9)//3)*3,((i%9)//3)*3+3):
        for k in range(3):
            if j+(9*k)!=i:
                sudoku.addUnaryConstraint(str(i), '!=', str(puzzle[j+(9*k)]))
                #sudoku.addBinaryConstraint(str(i), '!=', str(j+(9*k)))
                
    # different in the lines
    for j in range(9):
        if j!=i%9:
            sudoku.addUnaryConstraint(str(i), '!=', str(puzzle[i//9 + j]))
            #sudoku.addBinaryConstraint(str(i), '!=', str(i//9 + j))
            
    # different in columns
    for j in range(9):
        if j!=i//9:
            sudoku.addUnaryConstraint(str(i), '!=', str(puzzle[i%9 + 9*j]))
            #sudoku.addBinaryConstraint(str(i), '!=', str(i%9 + 9*j))

```


```python
len(sudoku.unary)
```




    2079



## Task 4: Solving sudoku by hill climbing

Complete the cell below by using the `CSSearchProblem` class you defined above and hill climbing to find a solution to the sudoku puzzle. Answer the questions below.


```python
# your code here
```

**Is the solution correct and complete or does it violate some constraints? If it does, which constraints are violated? Would a human solving this puzzle make that kind of mistakes?**

*Your answer goes here*

## Genetic algorithms

Another popular search/optimization approaches are genetic/evolutionary algorithms.
The basic notion in a genetic algorithm is an *individual*, which encodes a solution to the problem at hand.
The details of the encoding may vary greatly, but the most common approach is to construct a sequence of symbols (bits, possibly more complex symbols) of a constant length.
Continuing with the biological analogies, the encoding represents a genotype, whereas the encoded solution represents a phenotype.
It is rather important to ensure that most (if not all) such sequences (genotypes) represent valid solutions (phenotypes).

Each of the individuals is assigned some numeric value called *fitness*, which is a gain-type measure (i.e., the higher the better) and describes how well the individual copes in the given environment. It is, again, an analogy to the process of evolution.

Finally, two operators are usually defined:

* Mutation, which randomly changes a single gene in an individual.
* Reproduction, which given two parents combines their genetic material to create a child. If the individuals are represented as sequences, the most common approach is to find a random cross-over point and glue the part before the cross-over point from one parent with the part after the cross-over point from the other parent.

A group of individuals forms a *population* and the genetic algorithm generates new populations of the same size from the old ones by using the two described operators.
Some form of the *survival of the fittest* is implemented, e.g., by making a probability of parenting a child by an individual proportional to its fitness, or by creating more children than the desired population size and then removing these with the lowest fitness.

The following class `GeneticOperators` is an abstraction necessary to decouple representation from the algorithm itself.

* `random_individual` is responsible for constructing randomly a new individual
* `mutate` given an `individual` is supposed to perform a mutation and return a new, mutated individual
* `reproduce` given two parents `parent1` and `parent2` should return a child of theirs
* `fitness` should return a float number representing the fitness of the given `individual`


```python
class GeneticOperators:
    def random_individual(self):
        ...
        
    def mutate(self, individual):
        ...
        return mutated_individual
    
    def reproduce(self, parent1, parent2):
        ...
        return child
    
    def fitness(self, individual) -> float:
        ...
        return result
```

### Taks 5: Wrapping CSP into genetic operators

Complete the following class `CSPGO`, providing necessary operators to cast a CSP problem representd as an object of the class `CSP` to a representation suitable for a genetic algorithm.
Apart from the four functions from `GeneticOperators`, implement a function `phenotype` which, given an individual, returns a solution suitable for passing to the `verify` method of the `CSP` object.


```python
class CSPGO(GeneticOperators):
    def __init__(self, csp):
        self.csp = csp
        # add here any initialization code you may need
        
    def random_individual(self):
        ...
        
    def mutate(self, individual):
        ...
        return mutated_individual
    
    def reproduce(self, parent1, parent2):
        ...
        return child
    
    def fitness(self, individual) -> float:
        ...
        return result
    
    def phenotype(self, individual):
        ...
        return csp_solution
```

If your solution is correct a random individual should have a corresponding phenotype that can be then passed to the CSP.


```python
australiaGO = CSPGO(australia)
australia.verify(australiaGO.phenotype(australiaGO.random_individual()))
```

So should a mutated random individual


```python
australia.verify(australiaGO.phenotype(australiaGO.mutate(australiaGO.random_individual())))
```

And a child of two random individuals


```python
parent1 = australiaGO.random_individual()
parent2 = australiaGO.random_individual()
child = australiaGO.reproduce(parent1, parent2)

australia.verify(australiaGO.phenotype(child))
```

Of course it is perfectly acceptable that within these solutions some (or all) the constraints are unsatisfied.

## Task 6: Implement a genetic algorithm

A genetic algorithm works as follows:

1. Generate a random population of a given size `n`
2. Repeat the following `g` times:
    1. Repeat `n` times:
       1. Select at random two individuals from the population. The probability of selection should be proportional to their fitness (so individuals with higher fitness are selected more often).
       2. Create a child of these two individuals
       3. With a small probability `p` mutate the child
       4. Add the child to a new population
    2. Replace the old population with the new population
3. Return the best individual encountered in any of the `g` populations generated in the previous step

The last task! Complete the following function `ga` with an implementation of a genetic algorithm, given the following parameters:

* `operators` An object of the type `GeneticOperators`
* `g` The number of populations to generate
* `n` The size of a single population
* `p` The probability of mutation

**Hint**: sampling proportionally to the fitness is simple. For example, you can apply the following naive method (but you could do it faster using binary search).
1. Sum all the fitnesses.
2. Generate a random float from the range 0 to 1.
3. Iterate over individuals summing their fitnesses again. The moment the sum divided by total exceeds the random float, you found your random individual.


```python
def ga(operators: GeneticOperators, n: int, g: int, p: float):
    ...
```

Lets test it on the considered CSPs.


```python
individual = ga(australiaGO, 100, 10, 0.1)
australia.verify(australiaGO.phenotype(individual))
```


```python
sudokuGO = CSPGO(sudoku)
individual = ga(sudokuGO, 100, 10, 0.1)
sudoku.verify(sudokuGO.phenotype(individual))
```


```python
individual = ga(sudokuGO, 500, 100, 0.2)
sudoku.verify(sudokuGO.phenotype(individual))
```


