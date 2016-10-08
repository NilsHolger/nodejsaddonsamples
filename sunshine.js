const addon = require('./build/Release/addon');

// var obj1 = addon('Angular, Node, V8, libuv');
// var obj2 = addon('are the future. JAVASCRIPT everywhere.');
// var obj3 = addon('For High Performance Computing: C++.')

// console.log(`${obj1.secretmsg} ${obj2.secretmsg}\n${obj3.secretmsg}`);

//var fn = addon(); 
//console.log(fn());  //Linus you were right.Open Source has won.God bless you.

var obj = new addon.MyObject(100);
console.log(obj.timesTwo()); //200
console.log(obj.timesTwo()); //400
console.log(obj.timesTwo()); //800