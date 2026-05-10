// Test Program 2 for LLVM IR Generation
// Loops and arrays

int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + arr[i];
    }
    return sum;
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    int total = sum_array(numbers, 5);
    
    // Loop with optimization opportunities
    int result = 0;
    for (int i = 0; i < 10; i++) {
        result = result + (2 * 3);  // Constant folding opportunity
    }
    
    return total + result;
}
