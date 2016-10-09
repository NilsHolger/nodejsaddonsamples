var addon = require('./build/Release/addon');

//console.log(addon.pass_number(10)); //52
//console.log(addon.pass_number()); //undefined
//console.log(addon.pass_number("10")); //undefined

//console.log(addon.pass_integer(20)); //62
//console.log(addon.pass_integer()); //undefined
//console.log(addon.pass_integer(0.5)); //undefined

//console.log(addon.pass_boolean(true)); //false
//console.log(addon.pass_boolean(false)); //true
//console.log(addon.pass_boolean()); //undefined
//console.log(addon.pass_boolean("true")); //undefined
//console.log(addon.pass_boolean(1)); //undefined
//console.log(addon.pass_boolean(0)); //undefined

//console.log(addon.pass_string("you sexy string")); //gnirts yxes ouy
//console.log(addon.pass_string()); //undefined
//console.log(addon.pass_string(null)); //undefined
//console.log(addon.pass_string(undefined)); //undefined

//console.log(addon.pass_object({x: 2, y: 2}).sum); //4
//console.log(addon.pass_object({x: 3, y: 3}).product); //9
//console.log(addon.pass_object({x: 4, y: 4}).subtraction); //0
//console.log(addon.pass_object({x: 5, y: 5}).division); // 1

var a = [1,2,3];
a.not_index = 'Hello World'
console.log(addon.pass_array(a)); //[2, 'Hello World', 4]
