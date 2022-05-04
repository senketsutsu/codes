# Propositional logic

Within this assignment your task is to implement two different reasoning algorithms and then employ them in a noble quest of helping a brave warrior to avoid foul Wumpus (or protecting the last living Wumpus by steering away from it a blodlust warrior - your pick). 

## Horn clauses

We'll concentrate on a very limited subset of propositional logic, namely a *conjunction* of *Horn clauses*. A Horn clause is an *implication* such that its *premise* (*left-hand side*) is a *conjunction* of *atoms* (i.e., *propositonal symbols* or *propositional variables*) and its *conclusion* (*right-hand side*) is a single atom.

The following is a Horn clause:
$$ l \land m \to p $$
It is true if its premise is false (i.e., both $l$ and $m$ are false) or both premise and conclusion are true (i.e., all three atoms $l$, $m$ and $p$ are true).

An implication with a single atom in the premise is also a Horn clause (e.g., $p\to q$). Without any issues we may also assume that an implication without *any* atoms in the premise is also a Horn clause. In this, we assume that a disjunction of an empty set is always true and thus an implication with an empty premise is, in fact, an atom specified in its conclusion.

We begin by defining a *knowledge base* (KB), which will store a conjunction of Horn clauses. In the following class `KB`:

* Atoms are represented as whatever objects we want as long as they properly support hashing and equality checking. For example, we can use strings.
* A clause is a pair such that its first element is a list of atomis in the premise, while the second element is a single object representing the conclusion
* `clauses` is a list of clauses.
* `symbols` is a set of symbols (atoms) present in all the clauses in the knowledge base.
* `add` is a convenience method to add a new implication: its arguments correspond to the elements of a clause (as described above).
* `copy` makes a copy of the KB


```python
class KB:
    def __init__(self):
        self.clauses = []
        self.symbols = set()
    
    def add(self, premise, conclusion):
        self.clauses.append((premise, conclusion))        
        self.symbols |= set(premise)
        self.symbols.add(conclusion)
        
    def copy(self):
        result = KB()
        result.clauses.extend(self.clauses)
        result.symbols |= self.symbols
        return result
```

We now construct a KB consisting of the following Horn clauses:

* $p\to q$
* $l \land m \to p$
* $b \land l \to m$
* $a \land p \to l$
* $a \land b \to l$
* $x \to w$
* $a$
* $b$


```python
kb = KB()
kb.add(["p"], "q")
kb.add(["l", "m"], "p")
kb.add(["b", "l"], "m")
kb.add(["a", "p"], "l")
kb.add(["a", "b"], "l")
kb.add(["x"], "w")
kb.add([], "a")
kb.add([], "b")

kb.clauses
```




    [(['p'], 'q'),
     (['l', 'm'], 'p'),
     (['b', 'l'], 'm'),
     (['a', 'p'], 'l'),
     (['a', 'b'], 'l'),
     (['x'], 'w'),
     ([], 'a'),
     ([], 'b')]



Lets see how copying works:


```python
kb2 = kb.copy()
kb2.add(["u"], "w")

print("u->w in kb:", (["u"], "w") in kb.clauses)
print("u->w in kb2:", (["u"], "w") in kb2.clauses)
```

    u->w in kb: False
    u->w in kb2: True
    

## Reasoning

The goal of a *reasoner* is to *infer* whether a given *entailment* can be *derived* (*follows*) from a given knowledge base, i.e., whether the entailment is true every time the knowledge base is true. The following class `Reasoner` defines a bare-bone interface for a reasoner: it is given a knowledge base and there is a single method `query` which should return `True` if `symbol` follows from `kb`, and `False` otherwise.


```python
class Reasoner:
    def __init__(self, kb: KB):
        self.kb = kb
        
    def query(self, symbol) -> bool:
        ...
```

In the following, a `DummyReasoner` is defined. It returns `True` only if the given `symbol` is explicitly asserted in the knowledge base as a Horn rule with an empty premise.


```python
class DummyReasoner(Reasoner):
    def __init__(self, kb: KB):
        super().__init__(kb)
        
    def query(self, symbol):
        for premise, conclusion in self.kb.clauses:
            if conclusion == symbol and len(premise) == 0:
                return True
        return False
    
reasoner = DummyReasoner(kb)
print("a follows from KB", reasoner.query("a"))
print("q follows from KB", reasoner.query("q"))
print("w follows from KB", reasoner.query("w"))
```

    a follows from KB True
    q follows from KB False
    w follows from KB False
    

The `DummyReasoner` is *sound*: if it returns `True`, it means that the symbol follows. It is, however, not *complete*: if it returns `False`, it means that either the symbol doesn't follow or that it is not explicitly asserted in the knowledge base. Compare it with the `SmartReasoner` below.


```python
class SmartReasoner(Reasoner):
    def __init__(self, kb: KB):
        super().__init__(kb)
        
    def query(self, symbol):
        return symbol in self.kb.symbols
    
reasoner = SmartReasoner(kb)
print("a follows from KB", reasoner.query("a"))
print("q follows from KB", reasoner.query("q"))
print("w follows from KB", reasoner.query("w"))
```

    a follows from KB True
    q follows from KB True
    w follows from KB True
    

The `SmartReasoner` avoids the pitfail of *incompleteness*: if a symbol is present anywhere in the knowledge base it claims that it follow from the knowledge base. It is complete: every time it returns `False` it means that the given symbol doesn't follow from the knowledge base. It is also *unsound*: sometimes `True` means that the symbol follows, and sometimes it is a mistake on the resoner's part.

## Task 1: Implement forward chaining reasoner

Recall from the lecture the procedure of forward chaining. We'll use it slightly differently here from how it is presented in the text book: we first materialize all inferences and implement `query` as simple membership checking. In the following code complete the `_infer` procedure implementing the forward chaining algorithm. It should return an iterable containing all symbol that follow from the given knowledge base `self.kb`. In the pseudocode of `PL-FC-ENTAILS?` in the textbook there's a query variable `q` - just omit all expressions referreing to it.


```python
class ForwardChainingReasoner(Reasoner):
    def __init__(self, kb: KB):
        super().__init__(kb)
        self.inferred = set(self._infer())
        
    def query(self, symbol):
        if symbol in self.inferred:
            return(True)
        return(False)
        
    def _infer(self):
        queue = []
        used_tab = {}
        for premise, conclusion in self.kb.clauses:
            used_tab[conclusion] = False
            for i in premise:
                used_tab[i] = False
            if len(premise) == 0:
                queue.append(conclusion)
        
        while queue:
            x = queue.pop(0)
            #pop and mark as used
            used_tab[x] = True
            for premise, conclusion in self.kb.clauses:
                #print(premise)
                if used_tab[conclusion]:
                    continue
                for i in premise:
                    boolen = True
                    if not used_tab[i]:
                        boolen = False
                        break
                #add it's conclusions if premise used 
                if boolen:
                    queue.append(conclusion)
                #print(used_tab)
        final = []
        for x, boolen in used_tab.items():
            if boolen:
                final.append(x)
        #print(final)
        return(final)
```

Lets test it on our toy knowledge base! The answers should be sound and complete (i.e., *a* follows, *q* follows, *w* doesn't follow).


```python
reasoner = ForwardChainingReasoner(kb)
print("a follows from KB", reasoner.query("a"))
print("q follows from KB", reasoner.query("q"))
print("w follows from KB", reasoner.query("w"))
```

    a follows from KB True
    q follows from KB True
    w follows from KB False
    

## Task 2: Implement backward chaining reasoner

Complete the following `BackwardChainingReasoner` class so it implements backward chaining. Keep a cache of symbols for which an answer is already known (both `True` and `False`). Make sure that you avoid infinite loops in the reasoning process (the toy KB contains a possiblity for such a loop).


```python
class BackwardChainingReasoner(Reasoner):
    def __init__(self, kb: KB):
        super().__init__(kb)
        self.queue = []
        self.known = {}
        
    def query(self, symbol) -> bool:
        # to prove q by BC
        self.queue.append(symbol)
        
        # check if q is known already
        if (symbol in self.known) and self.known[symbol]:
            self.queue.remove(symbol)
            return self.known[symbol]
        
        # prove by BC all premises of some rule concluding q
        # also:
        #-check if new subgoal is already on the goal stack
        #-has already been proved true
        #-has already failed
        for premises, conclusion in self.kb.clauses:
            if (symbol in self.known) and self.known[symbol]:
                self.queue.remove(symbol)
                return self.known[symbol]
            
            if conclusion == symbol:
                boolen = True
                for p in premises:
                    if p in self.known:
                        if self.known[p] == False:
                            boolen = False
                            break
                    else:
                        if (p in self.queue) or (self.query(p) == False):
                            boolen = False
                            break
                            
                if boolen == True:
                    self.queue.remove(symbol)
                    self.known[symbol] = True
                    return self.known[symbol]
        # check if q is known now            
        if symbol in self.known:
            self.queue.remove(symbol)
            return self.known[symbol]
        else:
            self.queue.remove(symbol)
            self.known[symbol] = False
            return self.known[symbol]

```

Lets test it on our toy knowledge base! Again, the answers should be sound and complete (i.e., *a* follows, *q* follows, *w* doesn't follow).


```python
reasoner = BackwardChainingReasoner(kb)
print("a follows from KB", reasoner.query("a"))
print(reasoner.known)
print("q follows from KB", reasoner.query("q"))
print(reasoner.known)
print("w follows from KB", reasoner.query("w"))
print(reasoner.known)
```

    a follows from KB True
    {'a': True}
    q follows from KB True
    {'a': True, 'b': True, 'l': True, 'm': True, 'p': True, 'q': True}
    w follows from KB False
    {'a': True, 'b': True, 'l': True, 'm': True, 'p': True, 'q': True, 'x': False, 'w': False}
    

## Hunt the Wumpus/Save the Wumpus!

The Wumpus lives in a $n\times n$ cave and the behaviour of the cave follows these rules:

* An entrance to the cave is always in the bottom-left square. 
* A square may either be *flat* or contain a *pit*. If the warrior walks into a pit, they fall down and die.
* A square is *breezy* if, and only if, there is a pit in one of the directly adjacent squares (i.e., squares sharing one of the edges with the considered square).
* There is *stench* in a square if, and only if, the Wumpus is in one of the  directly adjacent squares.
* There is *glitter* in a square if, and only if, there's *gold* in this square.
* If the warrior walks into a square with a living Wumpus, the Wumpus kills the warrior.
* If the Wumpus dies (e.g., due to stress caused by the presence of the warrior), it emits a woeful *scream*. The scream can be heard anywhere in the cave and the dying Wumpus is its only possible source.
* The Wumpus is sleeping and thus doesn't move from square to square.
* There's exactly one wumpus in the cave. They're *the* Wumpus and don't live in a pit.

The picture below presents a sample Wumpus cave where $n=4$.

![](aima-images/fig7_2.png)

For now, we won't concern ourselves with building a complete agent capable of navigating the cave, killing the Wumpus etc. Instead, we'll concentrate on building a knowledge base for the warrior to equip them with some reasoning capabilities and to allow them to infer new knowledge about the cave from partial observations they obtained. Lets begin with creating the KB `warrior`. In the following we will assume that the squares are identified by their Cartesian coordinates, so the entrance is always at $(0,0)$ and in the sample cave above the pits are located at $(2,0)$ (the bottom pit), $(2, 2)$ (the pit in the middle) and $(3, 3)$ (the pit in the top right corner).


```python
n = 4
warrior = KB()
```

Consider the following sentence: *A square is breezy if, and only if, there is a pit in one of the directly adjacent squares.* For the square $(0, 0)$ we can express it in the propositional logic as $breezy_{0,0} \leftrightarrow (pit_{1,0} \lor pit_{0,1})$.
This, of course, is not a Horn clause and therefore cannot be added to our knowledge base. However, not all is lost! Observe that $p\leftrightarrow q$ is equivalent to $(p\to q) \land (q\to p)$ (in other words: *p if, and only if, q* is equivalent to *if p then q and if q then p*). We can thus rewrite the biconditional as two implications:

1. $(pit_{1,0} \lor pit_{0,1}) \to breezy_{0,0}$
2. $breezy_{0,0} \to (pit_{1,0} \lor pit_{0,1})$

Neither is a Horn clause, but the first one is almost there, as it can be split into two implications:

3. $pit_{1,0} \to breezy_{0,0}$
4. $pit_{0,1} \to breezy_{0,0}$

Now lets look on the other one: $breezy_{0,0} \to (pit_{1,0} \lor pit_{0,1})$. Here, we can apply another trick. Consider reading of this implication: *If a square is breezy, then there is a pit in one of the directly adjacent squares*. We can easily write its contrapositive: *If there isn't a pit in one of the directly adjacent squares, then a square isn't breezy.*. In the propositional logic it becomes: $\lnot(pit_{1,0} \lor pit_{0,1}) \to \lnot breezy_{0,0}$.
Following with the De Morgan's law we arrive at: $\lnot pit_{1,0} \land \lnot pit_{0,1} \to \lnot breezy_{0,0}$ which... still isn't a Horn clause!
But we've got another trick up the sleeve: we will call any square that does not contain a pit a flat square, and any square that is not breezy a windless square.
Thus the implication finaly becomes a Horn clause:

5. $flat_{1,0} \land flat_{0,1} \to windless_{0,0}$

Splendid! But there's still one more thing to handle: currently, a single square can contain a pit and be flat at the same time.
To handle this, we introduce a special symbol *inconsistent* which can be inferred only if two variables that are known to be inverses of each other can be proven to be both true at the same time:

6. $pit_{1,0} \land flat_{1,0} \to inconsistent$
7. $breezy_{1,0} \land windless_{1,0} \to inconsistent$

Anytime $inconsistent$ becomes true, we can be sure that our knowledge base went nuts and we cannot rely on it anymore.

## Task 3: Avoid the pits

Complete the following cell of code and extend the KB `warrior` with the Horn clauses necessary for the warrior to infer about pits and flat squares. Use the following symbols:

* `flatXY` is true if a square at $(X, Y)$ is flat.
* `pitXY`  is true if a square at $(X, Y)$ contains a pit.
* `breezyXY` is true if a square at $(X, Y)$ is breezy.
* `windlessXY` is true if a square at $(X, Y)$ is windless.

Implement consistency checking clauses, as it is possible that the Wumpus has some abilities to confuse the warrior about its surroundings. It is safe to assume that $n<10$ and there's no ambiguity, e.g., between `flat123` denoting a flat square at $(1,23)$ or a flat square at $(12,3)$. Be very carreful when computing the adjacent squares, for example there's no square $(-1, -1)$.


```python
for x in range(n):
    for y in range(n):
               
        # 1. (breezy->neighbouring pit)
        
        base = "breezy" + str(x) + str(y)
        up = "pit" + str(x) + str(y+1)
        down = "pit" + str(x) + str(y-1)
        left = "pit" + str(x-1) + str(y)
        right = "pit" + str(x+1) + str(y)
        cross = []
        
        if x < n-1:
            warrior.add([right], base)
        if x > 0:
            warrior.add([left], base)
        if y < n-1:
            warrior.add([up], base)
        if y > 0:
            warrior.add([down], base)
            
        # 2. (pit->breezy neighbours)
        base = "pit" + str(x) + str(y)
        up = "breezy" + str(x) + str(y+1)
        down = "breezy" + str(x) + str(y-1)
        left = "breezy" + str(x-1) + str(y)
        right = "breezy" + str(x+1) + str(y)
        cross = []
        
        if x < n-1:
            cross.append(right)
        if x > 0:
            cross.append(left)
        if y < n-1:
            cross.append(up)
        if y > 0:
            cross.append(down)
        
        warrior.add(cross, base)
        
        # 5. (windless->flat neighbours)
        base = "windless" + str(x) + str(y)
        up = "flat" + str(x) + str(y+1)
        down = "flat" + str(x) + str(y-1)
        left = "flat" + str(x-1) + str(y)
        right = "flat" + str(x+1) + str(y)
        cross = []
        
        if x < n-1:
            cross.append(right)
        if x > 0:
            cross.append(left)
        if y < n-1:
            cross.append(up)
        if y > 0:
            cross.append(down)
        
        warrior.add(cross, base)
        
        # 5. (flat->neighbouring windless)
        
        base = "flat" + str(x) + str(y)
        up = "windless" + str(x) + str(y+1)
        down = "windless" + str(x) + str(y-1)
        left = "windless" + str(x-1) + str(y)
        right = "windless" + str(x+1) + str(y)
        cross = []
        
        if x < n-1:
            warrior.add([right], base)
        if x > 0:
            warrior.add([left], base)
        if y < n-1:
            warrior.add([up], base)
        if y > 0:
            warrior.add([down], base)
            
        # 6.7.
        warrior.add(["flat" + str(x) + str(y), "pit" + str(x) + str(y)], "inconsistent") 
        warrior.add(["breezy" + str(x) + str(y), "windless" + str(x) + str(y)], "inconsistent") 
        

#print(warrior.clauses)
```

We'll now make a temporary copy of the warrior's knowledge base, assert it with some knowledge about the cave and see if the inferences are correct.


```python
def find_flat_squares(kb):
    reasoner = ForwardChainingReasoner(kb)
    assert not reasoner.query("inconsistent")
    for x in range(n):
        for y in range(n):
            if reasoner.query("flat{}{}".format(x, y)):
                print("I can prove that ({}, {}) is flat".format(x, y))
```


```python
tmp = warrior.copy()
tmp.add([], "windless00")
find_flat_squares(tmp)
```

    I can prove that (0, 1) is flat
    I can prove that (1, 0) is flat
    


```python
tmp.add([], "breezy10")
find_flat_squares(tmp)
```

    I can prove that (0, 1) is flat
    I can prove that (1, 0) is flat
    


```python
tmp.add([], "windless01")

find_flat_squares(tmp)
```

    I can prove that (0, 0) is flat
    I can prove that (0, 1) is flat
    I can prove that (0, 2) is flat
    I can prove that (1, 0) is flat
    I can prove that (1, 1) is flat
    


```python
tmp.add([], "pit02")

find_flat_squares(tmp)
```


    ---------------------------------------------------------------------------

    AssertionError                            Traceback (most recent call last)

    ~\AppData\Local\Temp/ipykernel_22556/2210918995.py in <module>
          1 tmp.add([], "pit02")
          2 
    ----> 3 find_flat_squares(tmp)
    

    ~\AppData\Local\Temp/ipykernel_22556/2408005608.py in find_flat_squares(kb)
          1 def find_flat_squares(kb):
          2     reasoner = ForwardChainingReasoner(kb)
    ----> 3     assert not reasoner.query("inconsistent")
          4     for x in range(n):
          5         for y in range(n):
    

    AssertionError: 


So it seems that the Wumpus actually have some strange abilities and they tried to convince the warrior that there's a pit at $(0, 2)$. If your KB is correct the cell above should've failed with an assertion error, as the KB became inconsistent.

## Task 4: Tracking the Wumpus

Great, the warrior can now infer which fields are flat, but this doesn't guarantee safety of/from the Wumpus. In the following cell extend the kb `warrior` with knowledge about tracking the Wumpus using the stench. Use the following symbols:

* `stenchXY` is true if there's stench in the square $(X, Y)$
* `freshXY` is true if the air in the square $(X, Y)$ is fresh (i.e., thre's no stench)
* `wumpusfreeXY` is true if the Wumpus is not in the square $(X, Y)$
* `wumpusXY` is true if the Wumpus is in the square $(X, Y)$

In the previous task the goal was to find squares that are flat (i.e., to avoid pits). Now, the goal is different: it is to actually find the Wumpus. Observe the following: *For any given square with a stench, if you can prove that the Wumpus is not present in all but one directly adjacent squares, the Wumpus must be present in the last remaining directly adjacent square.*


```python
for x in range(n):
    for y in range(n):
               
        # (breezy->neighbouring pit) -> (stench->wumpus)
        
        base = "stench" + str(x) + str(y)
        left = "wumpus" + str(x-1) + str(y)
        right = "wumpus" + str(x+1) + str(y)
        up = "wumpus" + str(x) + str(y+1)
        down = "wumpus" + str(x) + str(y-1)
        
        
        if x < n-1:
            warrior.add([right], base)
        if x > 0:
            warrior.add([left], base)
        if y < n-1:
            warrior.add([up], base)
        if y > 0:
            warrior.add([down], base)
            
        # (pit->breezy neighbours) -> (wumpus->stench)
        base = "wumpus" + str(x) + str(y)
        left = "stench" + str(x-1) + str(y)
        right = "stench" + str(x+1) + str(y)
        up = "stench" + str(x) + str(y+1)
        down = "stench" + str(x) + str(y-1)
        
        cross = []
        
        if x < n-1:
            cross.append(right)
        if x > 0:
            cross.append(left)
        if y < n-1:
            cross.append(up)
        if y > 0:
            cross.append(down)
        
        warrior.add(cross, base)
        
        # (windless->flat neighbours) -> (fresh->wumpusfree)
        base = "fresh" + str(x) + str(y)
        left = "wumpusfree" + str(x-1) + str(y)
        right = "wumpusfree" + str(x+1) + str(y)
        up = "wumpusfree" + str(x) + str(y+1)
        down = "wumpusfree" + str(x) + str(y-1)
        
        cross = []
        
        if x < n-1:
            cross.append(right)
        if x > 0:
            cross.append(left)
        if y < n-1:
            cross.append(up)
        if y > 0:
            cross.append(down)
        
        warrior.add(cross, base)
        
        # (flat->neighbouring windless) -> (wumpusfree->fresh)
        
        base = "wumpusfree" + str(x) + str(y)
        left = "fresh" + str(x-1) + str(y)
        right = "fresh" + str(x+1) + str(y)
        up = "fresh" + str(x) + str(y+1)
        down = "fresh" + str(x) + str(y-1)
        
        
        if x < n-1:
            warrior.add([right], base)
        if x > 0:
            warrior.add([left], base)
        if y < n-1:
            warrior.add([up], base)
        if y > 0:
            warrior.add([down], base)
            
        # (breezy, windless)->(stench,fresh);(pit,flat)->(wumpus,wumpusfree)
        warrior.add(["stench" + str(x) + str(y), "fresh" + str(x) + str(y)], "inconsistent") 
        warrior.add(["wumpus" + str(x) + str(y), "wumpusfree" + str(x) + str(y)], "inconsistent") 
        
        # For any given square with a stench, if you can prove that the Wumpus is not present in all but one directly adjacent squares, the Wumpus must be present in the last remaining directly adjacent square.
        base = "stench" + str(x) + str(y)
        up = "wumpusfree" + str(x) + str(y+1)
        down = "wumpusfree" + str(x) + str(y-1)
        left = "wumpusfree" + str(x-1) + str(y)
        right = "wumpusfree" + str(x+1) + str(y)
        
        if x < n-1:
            cross = [base]
            if x > 0:
                cross.append(left)
            if y < n-1:
                cross.append(up)
            if y > 0:
                cross.append(down)
            warrior.add(cross, "wumpus" + str(x+1) + str(y))
        if x > 0:
            cross = [base]
            if x < n-1:
                cross.append(right)
            if y < n-1:
                cross.append(up)
            if y > 0:
                cross.append(down)
            warrior.add(cross, "wumpus" + str(x-1) + str(y))
        if y < n-1:
            cross = [base]
            if x < n-1:
                cross.append(right)
            if x > 0:
                cross.append(left)
            if y > 0:
                cross.append(down)
            warrior.add(cross, "wumpus" + str(x) + str(y+1))
        if y > 0:
            cross = [base]
            if x < n-1:
                cross.append(right)
            if x > 0:
                cross.append(left)
            if y < n-1:
                cross.append(up)
            warrior.add(cross, "wumpus" + str(x) + str(y-1))
        
#print(warrior.clauses)
```

Again, let's make a copy of the KB and see if the warrior can perform track the Wumpus.


```python
def track_the_wumpus(kb):
    reasoner = BackwardChainingReasoner(kb) # FIX BACKWARD, TEMPORARILY USE FORWARD
    assert not reasoner.query("inconsistent")
    for x in range(n):
        for y in range(n):
            if reasoner.query("wumpus{}{}".format(x, y)):
                print("I can prove that the wumpus lives at ({}, {})".format(x, y))  
```


```python
tmp = warrior.copy()
tmp.add([], "fresh10")
tmp.add([], "stench01")
track_the_wumpus(tmp)
```


    ---------------------------------------------------------------------------

    AssertionError                            Traceback (most recent call last)

    ~\AppData\Local\Temp/ipykernel_22556/3769672646.py in <module>
          2 tmp.add([], "fresh10")
          3 tmp.add([], "stench01")
    ----> 4 track_the_wumpus(tmp)
    

    ~\AppData\Local\Temp/ipykernel_22556/735862685.py in track_the_wumpus(kb)
          1 def track_the_wumpus(kb):
          2     reasoner = BackwardChainingReasoner(kb) # FIX BACKWARD, TEMPORARILY USE FORWARD
    ----> 3     assert not reasoner.query("inconsistent")
          4     for x in range(n):
          5         for y in range(n):
    

    AssertionError: 


If your KB is correct, these two pieces of information: there is stench at $(0, 1)$ and there is fresh air at $(1, 0)$ should be sufficient to infer where the Wumpus lives. Lets consider another inference.


```python
tmp = warrior.copy()
tmp.add([], "stench12")
tmp.add([], "fresh23")
tmp.add([], "fresh10")
track_the_wumpus(tmp)
```

    I can prove that the wumpus lives at (0, 2)
    I can prove that the wumpus lives at (2, 2)
    

Alas, the Wumpus does take a bath from time to time! If your KB has necessary clauses for inconsistency, the following cell should fail.


```python
tmp = warrior.copy()
tmp.add([], "fresh10")
tmp.add([], "stench01")
tmp.add([], "fresh03")
track_the_wumpus(tmp)
```


    ---------------------------------------------------------------------------

    AssertionError                            Traceback (most recent call last)

    ~\AppData\Local\Temp/ipykernel_22556/1043352761.py in <module>
          3 tmp.add([], "stench01")
          4 tmp.add([], "fresh03")
    ----> 5 track_the_wumpus(tmp)
    

    ~\AppData\Local\Temp/ipykernel_22556/735862685.py in track_the_wumpus(kb)
          1 def track_the_wumpus(kb):
          2     reasoner = BackwardChainingReasoner(kb) # FIX BACKWARD, TEMPORARILY USE FORWARD
    ----> 3     assert not reasoner.query("inconsistent")
          4     for x in range(n):
          5         for y in range(n):
    

    AssertionError: 


## A final remark

Both forward and backward chaining are sound, complete and efficient procedure for Horn rules. Unfortunately, there's a problem with Horn rules in propositional logic: they're a very weak tool, in some cases requiring a lot of patience, ingenuity and computing partial inferences (c.f. Task 3) beforehand.
