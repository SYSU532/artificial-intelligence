/*
* GA.js
*/

var canvas = document.getElementById("cav");
var ctx = canvas.getContext("2d");
var posData = new Array();
var pathData = new Array();
canvas.width = 700;
canvas.height = 700;

window.onload = function(){
	initLoc();

}

function initCav(){
	ctx.strokeStyle = "red";
	ctx.lineWidth = 2;
	for(var i=0; i< 130 ; i++){
		ctx.beginPath();
		ctx.moveTo((posData[i][0]), Number(posData[i][1]));
		if(i == 130 - 1){
			ctx.lineTo((posData[0][0]), Number(posData[0][1]));
		}else {
			ctx.lineTo((posData[i+1][0]), Number(posData[i+1][1]));
		}
		ctx.stroke();
	}
}

function initLoc(){
	$.ajax({
		url: "http://localhost:8088/Init-Pos",
		type: "GET",
		beforeSend: function(xhr){
			xhr.setRequestHeader('Access-Control-Allow-Origin', '*');
		},
		success: function(data){
			var splitedArr = data.split("\r\n");
			console.log(splitedArr.length);
			for(var i=0; i<splitedArr.length; i++){
				var temp = splitedArr[i].split(" ");
				posData[i] = new Array();
				posData[i][0] = temp[1];
				posData[i][1] = temp[2];
			}
			initCav();
		}
	});
}

function drawCav(){
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	for(var i=0; i< 130; i++){
		var srcNumber = Number(pathData[i]), dstNumber;
		ctx.beginPath();
		ctx.moveTo((posData[srcNumber][0]), Number(posData[srcNumber][1]));
		if(i == 130 - 1){
			dstNumber = Number(pathData[0]);
		}else {
			dstNumber = Number(pathData[i+1]);
		}
		ctx.lineTo((posData[dstNumber][0]), Number(posData[dstNumber][1]));
		ctx.stroke();
	}

}

function doGet(){
	$.ajax({
		url: "http://localhost:8088/GA-Data",
		type: "GET",
		beforeSend: function(xhr){
			xhr.setRequestHeader('Access-Control-Allow-Origin', '*');
		},
		success: function(data){
			var splitedArr = data.split(" ");
			for(var i=0; i< 130; i++){
				pathData[i] = splitedArr[i];
			}
			console.log(data);
			drawCav();
		}
	});
}

function GetMess(){
	setTimeout(doGet(), 1000);
}

function beginGA(){
	for(var i=0; i<10000; i+=50){
		GetMess();
	}
}