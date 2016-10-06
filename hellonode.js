const Benchmark = require('benchmark');
const addon = require('./build/Release/addon');
var javascript = require('./javascriptpalindrome');
const suite = new Benchmark.Suite;
var str = 'geist ziert leben mut hegt siege beileid trägt belegbare reue neid dient nie nun eint neid die neuerer abgelebt gärt die liebe geist geht umnebelt reizt sieg';



suite
.add('JAVASCRIPT Palindrome', () => javascript.isPalindrome(str))

.add('C++ Palindrome', () => addon.isItaPalindrome(str))

.on('cycle', cycle)
.on('complete', compete)
.run({'async': true})

function cycle(event){
    console.log(event);
};

function compete(a, b){
        //C++ wins on multiple trials
        console.log('FASTEST: ' + this.filter('fastest').map('name'));  //C++ elapsed 5.867
        console.log('SLOWEST: ' + this.filter('slowest').map('name')); //JavaScript elapsed 6.072
}


