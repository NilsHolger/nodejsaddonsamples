var addon = require('./build/Release/addon');

var poly = new addon.Polynomial(1, 5, 3);

console.log(poly.roots()); //[-0.6972,-4.3027]

console.log(poly.at(4)); //39

poly.c = 1;

console.log(poly.at(4)); //37

console.log(poly.a + ", " + poly.b + ", " + poly.c); //1, 5, 1
