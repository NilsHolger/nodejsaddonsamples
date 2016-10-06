//now let's implement our javascript exactly the same way we implemented our c++ addon

//initial implementation a fine but costly one liner
// function isPalindrome(str){
//     return str === str.split('').reverse().join('');
// };

function isPalindrome(str){
    var half = Math.round(str.length / 2);
    var start = 0;
    var end = str.length - 1;
    var palindrome = true;
    var SPACE = 32;
    var COMMA = 44;
    var startSpace, endSpace;

    while (half && palindrome){
        startSpace = str.charCodeAt(start) === SPACE || str.charCodeAt(start) === COMMA;
        endSpace = str.charCodeAt(end) === SPACE || str.charCodeAt(end) === COMMA;
        if (str[start] == str[end]){
            start++;
            end--;
    } else if (startSpace || endSpace){
            startSpace && start++;
            endSpace && end--;
    } else {
        palindrome = false;
    }
    half--;
}
    return palindrome;
}



module.exports.isPalindrome = isPalindrome;
