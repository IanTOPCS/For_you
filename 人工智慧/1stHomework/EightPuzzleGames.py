import heapq
from SuccessorFunction import step, move
from SolvabilityDecision import judge
from ManhattanDistance import manhattan_distance

class DataNode:
    def __init__(self, state, g=0, h=0, action=None, parent=None):
        self.state = state  # Puzzle state representation
        self.g = g  # Cost so far
        self.h = h  # Heuristic cost
        self.f = g + h  # Total cost
        self.action = action  # Action that led to this state
        self.parent = parent  # Parent node

class PriorityQueue:
    def __init__(self):
        self.queue = []
        self.counter = 0
    
    def enqueue(self, node):
        heapq.heappush(self.queue, (node.f, self.counter, node))
        self.counter += 1
    
    def dequeue(self):
        return heapq.heappop(self.queue)[2] if self.queue else None
    
    def is_empty(self):
        return len(self.queue) == 0

def main():
    goal = "012345678"
    pqueue = PriorityQueue()
    
    initial_state = str(input())
    mynode = DataNode(initial_state)
    
    if judge(mynode.state) == "NO":
        print("No solution!!")
        return
    
    if mynode.state == goal:
        print("It is the goal state.")
        return
    
    mynode.g = 0
    mynode.h = manhattan_distance(mynode.state)
    mynode.f = mynode.g + mynode.h
    mynode.parent = None
    pqueue.enqueue(mynode)
    
    final = None
    
    while not pqueue.is_empty():
        mynode = pqueue.dequeue()
        
        if mynode.state == goal:
            final = mynode
            break
        
        for direction in step.keys():
            next_state = move(mynode.state, direction)
            if next_state:
                newnode = DataNode(
                    state=next_state,
                    g=mynode.g + 1,
                    h=manhattan_distance(next_state),
                    action=direction,
                    parent=mynode
                )
                pqueue.enqueue(newnode)
    
    if final is None:
        print("No solution!!")
    else:
        actions = []
        while final:
            if final.action:
                actions.append(f"move 0 to {final.action}")
            final = final.parent
        actions.reverse()
        # print(f"Total: {len(actions)} steps") # debug
        for x in actions:
          print(x)

if __name__ == "__main__":
    main()
