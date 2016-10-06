function isPalindrome(str){
    return str === str.split('').reverse().join('');
};

module.exports.isPalindrome = isPalindrome;
