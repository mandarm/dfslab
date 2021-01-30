front = 0
rear = 0
size = 5
Q = [ 0 for i in range(size) ]

def enqueue(L, x) :
    global rear
    if (rear + 1) % size == front : # full
        print("Queue is full")
    else :
        L[rear] = x
        rear = (rear + 1) % size

def dequeue(L) :
    global front, rear, size
    if front == rear : # empty
        print("Queue is empty")
    else :
        x = L[front]
        front = (front + 1) % size
        return x

def length(L) :
    if front <= rear :
        return rear - front
    else :
        return size - (front - rear)

def display(L) :
    if front <= rear :
        print(L[front:rear])
    else :
        print(L[front:] + L[:rear])
