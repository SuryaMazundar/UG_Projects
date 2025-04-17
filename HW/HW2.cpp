/* Name: Surya Teja Mazundar */

// Adds a new node at the front of the list
void push_front(const int &din) {
	
	// Creates a new node and initializes with din
	node *new_node = new node(din); 
	
	new_node->next = head;

	// Head points to the new nodes
	head = new_node;
	
	// Increments the size of the list
	N++;
}

// Removes the node at the front
void pop_front() {

	if (head != nullptr) {

		// Stores the pointer to the current node of head in temp
		node *temp = head;

		// Proceeds to the next node
		if (head->next) {
			head = head->next;
		} else {
			head = nullptr;
		}
		delete temp;
	}
}

// Acceses the first element without removing it
const int &front() {
	if (head != nullptr) {
		return head->data;
	}
}
