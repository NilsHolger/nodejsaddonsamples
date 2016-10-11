const addon = require('./build/Release/addon');

//var result = addon.passnumber(50);
//console.log(result); //150

//var result1 = addon.passnumber(3.141592);
//console.log(result1); //103.141592

//var result2 = addon.passnumber();
//console.log(result2); //0

//var result3 = addon.passnumber("1");
//console.log(result3); //-1

//var result4 = addon.passinteger(100);
//console.log(result4); //100

//var result5 = addon.passinteger(1.01);
//console.log(result5); //1

//var result6 = addon.passboolean(true);
//console.log(result6); //false
//console.log(addon.passboolean(false));//true

//console.log(addon.passstring("reverseit")); //tiesrever

//var obj = { x : 100, y : "string", z : false };
//console.log(addon.passobject(obj)); // x is mutated to 200
//var obj = { x : 10, y : 10};
//console.log(addon.passobjectfactory(obj).sum); //20
//console.log(addon.passobjectfactory(obj).product); //100
//console.log(addon.passobjectfactory(obj).divide); //1
//console.log(addon.passobjectfactory(obj).subtract); //0

var arr = [1,2,3];
console.log(addon.incrementarray(arr)); //101, 102, 103







