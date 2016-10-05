const addon = require("./build/Release/addon");

//console.log(addon.greet()); //Hello Node

//console.log(addon.multiply(10,  10)); //100

//addon((message) => {console.log(message);}) //Node and V8 Rock Da House

setInterval(function(){
        console.log('another task in JavaScript in progress');
}, 500);

addon.executeTaskAsync(function(data){
    console.log('The data has arrived: ' + data);
    process.exit();
});

console.log('executeTaskAsync has started');