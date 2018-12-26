#include "VirtualMachine.h"

#include <iostream>

using namespace gc;

int main() {
    VirtualMachine vm(9);

    // Below is the example from the handout. Uncomment them when you finished
    // the assignment to test your codes.

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair();
    vm.dup();
	vm.storeFirst();
	vm.loadSecond();
    vm.pushInt(3);
    std::cout << vm;
    vm.add();
    vm.pop();
    std::cout << vm;
    std::cout << "Stack size = " << vm.getStackSize() << '\n';
    std::cout << "Heap size = " << vm.getHeapSize() << '\n';

    // Also, you should at least test the following case, to make sure the
    // garbage collector works as expected

    VirtualMachine vm2(7);
    vm2.pushInt(1);
    vm2.pushInt(2);
    vm2.pushPair();
    vm2.dup();
    vm2.storeFirst();
    vm2.loadFirst();
    vm2.pushInt(3);
	std::cout << vm2;
	std::cout << "Stack size = " << vm2.getStackSize() << '\n';
	std::cout << "Heap size = " << vm2.getHeapSize() << '\n';
    // No OutOfMemoryException should be thrown here
    // vm2's stack should contain 3 elements: two integers, and a pair
}
