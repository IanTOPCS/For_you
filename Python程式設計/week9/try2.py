import threading
 
def my_proc(data):
    for _ in range(100000):
        for i in range(len(data)):
          data[i] = data[i] + 1

lock = threading.Lock()
def my_proc2(data, lock):
        with lock:
            for i in range(len(data)//2):
                for _ in range(100000):
                    x       = data[i] + 1      
                    for _ in range(1):
                        pass
                    data[i] = x
                    
        with lock:
            for i in range(len(data)//2,len(data)):
                for _ in range(100000):
                    x       = data[i] + 1      
                    for _ in range(1):
                        pass
                    data[i] = x

for round in range(5):
    print(f'round {round}')
    data = [1,2,3,4]
    
    thread_lst = [threading.Thread(target=my_proc,args=(data,)) for _ in range(25)]

    for t in thread_lst:
        t.start()

    for t in thread_lst:
        t.join()

    print(data)
    
print('-'*20)    


for round in range(5):
    print(f'round {round}')
    data = [1,2,3,4]

    thread_lst = [threading.Thread(target=my_proc2,args=(data, lock)) for _ in range(25)]

    for t in thread_lst:
        t.start()

    for t in thread_lst:
        t.join()

    print(data)