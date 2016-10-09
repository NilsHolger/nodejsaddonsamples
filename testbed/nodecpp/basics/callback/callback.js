const callback = require('./build/Release/addon');

// var callme = () => console.log('I\'ve been called.');

// callback.callthis(callme);

var callme = (msg) => { msg ? console.log(msg) : console.log('I\'ve been called');}


//callback.callthis(callme);
callback.callthis_withthis(callme, 'This is a top secret message');