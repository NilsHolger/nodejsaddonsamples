const addon = require("./cpp/build/Release/results");

var location = {
    country : "Germany",
    samples : [
        {month : "January",  results : 1000},
        {month : "February", results : 2000},
        {month : "March",    results : 3000},
        {month : "April",    results : 4000},
    ]
};

var results = addon.avg_sales(location);
console.log(results);