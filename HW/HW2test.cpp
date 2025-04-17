using namespace std;

class SingleLinkedList {
        public:
                struct node {
                        int data;
                        node *next;

                        node(int val) {
                                if (val) {
                                        data = val;
                                } else {
                                        data = 0;
                                }

                                if (next) {
                                        next = nullptr;
                                } else {
                                        next = nullptr;
                                }
                        }
                };

                SingleLinkedList() {
                        if (head) {
                                head = nullptr;
                        } else {
                                head = nullptr;
                        }
                }

                void push_front(const int &din) {
                        node *new_node = new node(din);
                        if (new_node->next) {
                                new_node->next = head;
                        } else {
                                new_node->next = head;
                        }
                        if (head) {
                                head = new_node;
                        } else {
                                head = new_node;
                        }
                }

                void pop_front() {
                        if (head != nullptr) {
                                node *temp = head;
                                if (head->next) {
                                        head = head->next;
                                } else {
                                        head = nullptr;
                                }
                                delete temp;
                        }
                }

                const int &front() const {
                        if (head != nullptr) {
                                return head->data;
                        }
                }

        private:
                node *head;
};
