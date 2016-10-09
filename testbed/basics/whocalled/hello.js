//hello.js
var addon = require('./build/Release/addon');


var me = {
    greet : addon.greet
}

var who = me.greet();
console.log(who); // { greet: [Function: greet]}