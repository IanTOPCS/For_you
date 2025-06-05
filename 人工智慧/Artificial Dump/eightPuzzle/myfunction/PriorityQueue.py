import heapq

class PriorityQueue:
    def __init__(self):
        self.queue = []
        self.counter = 0  # To maintain FIFO order in case of tie

    def enqueue(self, state, g, h):
        f = g + h
        heapq.heappush(self.queue, (f, self.counter, state))
        self.counter += 1
        print("Insert OK!")

    def dequeue(self):
        if self.queue:
            _, _, state = heapq.heappop(self.queue)
            print(f"Got {state}")
        else:
            print("Queue is empty!!")

if __name__ == "__main__":
  pq = PriorityQueue()
  num = int(input())
  for num in range(num):
      action = str(input())
      if action == "enqueue":
          sor = str(input()).split(' ')
          state, g, h = sor[0], int(sor[1]), int(sor[2])
          pq.enqueue(state, g, h)
      elif action == "dequeue":
          pq.dequeue()
