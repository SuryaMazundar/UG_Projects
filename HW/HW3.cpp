private:
  // Pointer to the dynamically allocated array
  int* data;
  int arraySize;
  int topIndex;

public:
  stack() {
  arraySize = 10;

  // Assigned to -1 to state that the stack is empty
  topIndex = -1;
  
  data = new int[arraySize];
  }
	
   // Deallocates memory
  ~stack() {
    delete[] data;
  }
  
  // Checks if stack is empty
  bool empty() const {
    return topIndex == -1;
  }

  // Since topIndex is the last element, this will tell the size
  int size() const {
    return topIndex + 1;
  }

  // Appends the allocated memory at the end
  void push(int value) {
    data[++topIndex] = value;
  }

  // If empty, returns current value and decrements topIndex
  int pop() {
    return data[topIndex--];
  }

  // Returns without changing topIndex
  int top() const {
    return data[topIndex];
  }
