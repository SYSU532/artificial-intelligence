`use strict`

var fs = require('fs');
var path = require('path');
var express = require("express");
var app = express();

const GA = require('./build/Release/GA.node');
const ITER_NUM = 10000;

app.use(express.static(path.join(__dirname, '/Web/')))
app.set('views', path.join(__dirname, '/Web/'));
app.engine('html', require('ejs').__express);
app.set('view engine', 'html');


app.get("/", function(req, res, next){
	res.type('html');
	res.render('index');
});

app.get("/GA-Data", function(req, res, next){
	var result = GA.getBestPath();
	res.end(result);
});

app.get("/Init-Data", function(req, res, next){
	GA.clear();
});

app.get("/Init-Pos", function(req, res, next){
	res.writeHeader(200, {"Content-Type" : "text/plain"});
	fs.readFile('src/cities.txt', function(err, data){
		if(err) throw err;
		res.end(data.toString());
	});
});

app.listen(8088);

console.log("Server running at localhost:8088....");