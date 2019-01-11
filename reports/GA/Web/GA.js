/*
* GA.js
*/

var canvas = document.getElementById("cav");
var ctx = canvas.getContext("2d");
var posData = new Array();
var pathData = new Array();
var startFlag = false;
var time = 0;
var turn = 0;
var timer = null;
var draw_time = 0;

canvas.width = 700;
canvas.height = 700;

window.onload = function(){
	startFlag = false;
	$.get("http://localhost:8088/Init-Data", {}, function(err, data){});
	initLoc();
}

function initCav(){
	ctx.clearRect(0, 0, canvas.width, canvas.height);
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
	draw_time += 1;
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	for(var i=0; i< 130; i++){
		var srcNumber = Number(pathData[i])-1, dstNumber;
		ctx.beginPath();
		ctx.moveTo((posData[srcNumber][0]), Number(posData[srcNumber][1]));
		if(i == 130 - 1){
			dstNumber = Number(pathData[0])-1;
		}else {
			dstNumber = Number(pathData[i+1])-1;
		}
		ctx.lineTo((posData[dstNumber][0]), Number(posData[dstNumber][1]));
		ctx.stroke();
	}

}

function doGet(){
	var temp_turn = turn;
	if(startFlag == false)
		return;
	$.ajax({
		url: "http://localhost:8088/GA-Data",
		type: "GET",
		beforeSend: function(xhr){
			xhr.setRequestHeader('Access-Control-Allow-Origin', '*');
		},
		success: function(data){
			if(startFlag && temp_turn == turn){
				var splitedArr = data.split(" ");
				for(var i=0; i< 130; i++){
					pathData[i] = splitedArr[i];
				}
				document.getElementById("path").innerText = splitedArr[130];
				drawCav();
				console.log(draw_time);
				if(draw_time == 160){
					clearInterval(timer);
				}
			}
		}
	});
}

function GetMess(){
	setTimeout(doGet(), 2000);
}

function beginGA(){
	startFlag = true;
	timer = setInterval(function(){
		time += 0.1;
		document.getElementById("time").innerText = String(time).substring(0, 4) + "s";
	}, 100);
	for(var i=0; i<8000; i+=50){
		if(startFlag == false){
			clearInterval(timer);
			return;
		}
		GetMess(i);
	}
}