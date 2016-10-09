NodeJS Addons

1. Node is a C++ program. It uses two libraries to provide much of its structure. V8 which is the JavaScript
code runtime, and libuv written in C, which implements the event loop. 
2. V8 is a C++ library. It's the JavaScript world, when the JavaScript code creates variables, the space created
for them is inside the V8 address space - its heap. The memory associated with a JavaScript variable a storage cell
to keep the distinction clear.
3. JavaScript variables are garbage collected. V8 implements a garbage collector. V8 must keep track of howmany
references are pointing to each storage cell. 
4. V8's C++ data types allow your C++ code (addon) to access the very same storage cells that the executing 
JavaScript code can.
5. Storage Cells are only eligible for garbage collection when there are no references to them in the JavaScript code
and no references to them in the C++ code. 

There is a huge difference between C++ code double x and a V8::Number. The double is created on the stack or heap
of the C++ program, that is Node while the v8::Number is a C++ object which contains a reference to a storage cell,
managed entirely by the V8 runtime and of course stored on the C++ program's heap as well.

Isolates
An isolate is an independent instance of the V8 runtime - complete with execution context(control flow), memory
management, garbage collection and so forth. A C++ program can create multiple Isolate objects in order to provide
multiple, parallel, and isolated execution environments for scripts to run. Each Isolate contains its own heap, it's
own memory pool in which storage cells for the variables created by JavaScript execute within. 
An isolate encapsulates an execution environment and heap.
Context
The running of JavaScript requires a global object. V8 represents the global as a V8::Context. A Context object
corresponds to a global object in the Isolate's heap. 

//continue here
