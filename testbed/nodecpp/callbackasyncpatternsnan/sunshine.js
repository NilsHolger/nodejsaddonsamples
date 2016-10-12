const addon = require('./build/Release/addon');

const user = 'sexy';
const password = 'code';
//login sync
//addon.loginsync(user, password, (result) => {console.log(result);}); //authorized
setInterval(function() {
  console.log('javascript thread is free to work ...');
}, 10);
//login async
addon.loginasync(user, password, (result) => { console.log(result);process.exit();}); //authorized for your eyes only

console.log('loginasync started.');