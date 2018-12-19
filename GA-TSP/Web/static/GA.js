/*
* GA.js
*/

var canvas = document.getElementById("cav");
var context = canvas.getContext("2d");
var posData = new Array();

window.onload = function(){
	initLoc();
	initCav();
}

function initCav(){
	context.fillStyle = "red";
	console.log(posData.length);
	for(var i=0; i<posData.length; i++){
		ctx.beginPath();
		ctx.arc(Number(posData[i][1]), Number(posData[i][2]), 10, 0, 2*Math.PI);
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
			for(var i=0; i<splitedArr.length; i++){
				var temp = splitedArr[i].split(" ");
				posData[i] = new Array();
				posData[i][0] = temp[1];
				posData[i][1] = temp[2];
			}
		}
	});
}

function doGet(){


}