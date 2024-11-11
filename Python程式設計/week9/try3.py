import datetime
import time
import threading

def timer_proc(lock):
    while True:
        print(datetime.datetime.now().strftime("%H:%M:%S"),"alive")
        if not lock.locked() : #
            break
        time.sleep(5)

timer_lock = threading.Lock()
timer_lock.acquire()

timer_thread = threading.Thread(target=timer_proc,args=(timer_lock,))
timer_thread.start()

time.sleep(20)

timer_lock.release()
timer_thread.join()