'use strict';
const fs = require('fs');
const path = require('path');
const addon = require('./build/Release/addon');

var png_file = process.argv[2];

var bmp_file = path.basename(png_file, '.png') + ".bmp";

var png_buffer = fs.readFileSync(png_file);

const bmp_buffer = addon.saveBMP(png_buffer, png_buffer.length);
fs.writeFileSync(bmp_file, bmp_buffer);

