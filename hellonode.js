const addon = require("./build/Release/addon");

//console.log(addon.greet()); //Hello Node

//console.log(addon.multiply(10,  10)); //100

addon((message) => {console.log(message);}) //Node and V8 Rock Da House