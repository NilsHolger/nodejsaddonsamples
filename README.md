# nodejsaddonsamples
Node.js Addon Samples JavaScript C++ node-gyp configure build

Node.js Addons are dynamically linked shared objects written in C/C++ that can be loaded into Node using the require function and used
as if they were an ordinary Node.js module. They are used primarily to provide an interface between JavaScript running in Node.js and 
C/C++ libraries.

The hero components involved here are V8, libuv and internal Node.js libraries.
V8 is the C++ library that Node currently uses to provide the JavaScript implementation. V8 provides the mechanism for creating objects,
calling functions. V8's API is documented mostly in the v8 header file deps/v8/include/v8.h in the Node.js source tree, also availabe
online here https://v8docs.nodesource.com/.
libuv is the C library that implements the Node.js event loop, its worker threads and all asynchronous behaviors of the platform. It also
serves as a cross platform abstraction library, giving easy, POSIX-like access across all major operating systems to many common system
tasks, such as interacting with file systems, sockets, timers and system events. libuv also provides a pthreads like threading abstraction
that can be used to power more sophisticated asynchronous addons that need to move beyond the standard event loop. libuv lives here
http://libuv.org/.
Internal Node.js libraries. Node itself exports a number of C/C++ API's that addons can use, the most important of which is the node::
ObjectWrap class. Node lives here https://nodejs.org/dist/latest-v6.x/docs/api/.
These technologies were built with love and passion. All are Open Source. Moving humanity perpetually forwards.

