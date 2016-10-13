"use strict"; 

const worker = require("streaming-worker");
const path = require("path");

var addon_path = path.join(__dirname, "build/Release/addon");
const factorizer = worker(addon_path, {n: 10000000001});

factorizer.from.on('decompose factor', (factor) =>{console.log("Factor:  " + factor);});
factorizer.from.on('error', (error) => {console.log(error);});