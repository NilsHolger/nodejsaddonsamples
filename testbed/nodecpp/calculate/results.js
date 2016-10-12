const addon = require("./cpp/build/Release/results");

var location = {
    country : "Germany",
    samples : [
        {month : "January",   results : 1000},
        {month : "February",  results : 2000},
        {month : "March",     results : 3000},
        {month : "April",     results : 4000},
        {month:  "May",       results : 5000}
    ]
};

// //var random = () => { return Math.round(1000000 * Math.random() * 100) / 100;}

// var random = function(){
//     return Math.round(1000000 * Math.random() * 100) / 100;
// }().toFixed(2);
// //console.log(random());

var countries = ["Germany", "USA", "France", "Italy", "Spain", "Canada", "Australia", "England", "Japan", "South Africa"];
var locations = [];
for (var i = 0; i < 10; i++){
    var loc = {
        country : countries[i],
        samples : [
            {month : "January",  results : 2000},
            {month:  "February", results: 3000},
            {month:  "March",    results: 4000},
            {month:  "April",    result: 5000}
        ]
    }
    locations.push(loc);
}

var results = addon.calculate_results(locations);
console.log(results);
var i = 0;
results.forEach((result) => {
            console.log("Result for Location " + i);
            console.log("---------------------------");
            console.log("\tCountry: " + locations[i].country);
            console.log("\tMean Sales: " + result.mean);
            console.log("\tMedian Sales: " + result.median);
            console.log("\tStandard Dev.: " + result.standard_deviation);
            console.log("\tNumber Samples: " + result.n);
            console.log();
            i++;
});




// const results = addon.avg_sales(location);
// console.log(`Average Results = ${results} €`);

// const data = addon.data_country(location);

// console.log("Mean = " + data.mean);
// console.log("Median = " + data.median);
// console.log("Standard Deviation = " + data.standard_deviation);
// console.log("Count = " + data.n);