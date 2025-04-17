/* Program Name: Instance Counter (HW4)
 * Name: Surya Teja Mazundar
 * Professor: Dr. Jens Gregor
 * Student ID: 000718553
 * Net ID: smazunda
   */

// Counts the number of occurrences of a first entered value in a list.
template <typename Iterator, typename T>
int my_count(Iterator begin, Iterator end, const T& index) {
	// Keeps track of the occurances
    int count = 0;
	// Iterates through the entered range of list 
    for (Iterator element = begin; element != end; ++element) {
        if (*element == index) {
            count++;
        }
    }
	// Returns the total number of occurances
    return count;
}

