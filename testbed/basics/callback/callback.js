var addon = require('./build/Release/addon');

var callme = (msg) => { msg ? console.log(msg) : console.log('I\'ve been called.');}


addon.callthis(callme); //I've been called.
addon.callthiswiththis(callme, "It's nice to be important, but it's more important to be nice.");
//It's nice to be important, but it's more important to be nice.