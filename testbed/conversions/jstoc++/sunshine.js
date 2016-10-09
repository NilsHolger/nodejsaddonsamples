var addon = require('./build/Release/addon');

// var obj = { x : 5};

// console.log(addon.mutate(obj));

//console.log(addon.passnumber(1)); //101
//console.log(addon.passnumber(3.141592)); //103.141592

//console.log(addon.passnumberwithexceptionhandling()); //0
//console.log(addon.passnumberwithexceptionhandling("you sexy string")); //-1
//console.log(addon.passnumberwithexceptionhandling("1")); //numbers only

//console.log(addon.passboolean()); //enter a value
//console.log(addon.passboolean(1)); //booleans only
//console.log(addon.passboolean(true)); //false

//console.log(addon.passstring()); //enter a value
//console.log(addon.passstring(1)); // strings only
//console.log(addon.passstring("he has a master plan")); //nalp retsam a sah eh


//TODO: array and object

var target = { x : 8};
addon.initialize(target, 100);
//console.log(target);

for (var i = 0; i < 3; i++){
    addon.increment();
    console.log(target); //{ x: 108 } { x: 208} { x : 308 }
}

